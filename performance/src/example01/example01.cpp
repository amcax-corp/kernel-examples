#pragma once
#include <chrono>
#include <filesystem>
#include <iostream>
#include <mutex>
#include <omp.h>
#include <optional>
#include <fstream>
#include <sstream>
// clang-format off 
#include <windows.h>
#include <psapi.h>
// clang-format on 

// AMCAX 
#include <boolean/BoolBRepFuse.hpp>
#include <boolean/BoolBRepSplitter.hpp>
#include <common/CartesianCoordinateSystem.hpp>
#include <common/Constants.hpp>
#include <common/IndexSet.hpp>
#include <common/TransformationT.hpp>
#include <intersect/BRepIntCurveSurface.hpp>
#include <math/Plane.hpp>
#include <modeling/CopyShape.hpp>
#include <modeling/MakeBox.hpp>
#include <modeling/MakeFace.hpp>
#include <modeling/MakePolygon.hpp>
#include <modeling/MakePrism.hpp>
#include <modeling/MakeSphere.hpp>
#include <modeling/TransformShape.hpp>
#include <offset/MakeLoft.hpp>
#include <step//STEPTool.hpp>
#include <topology/TopoExplorer.hpp>
#include <topology/TopoExplorerTool.hpp>
#include <topology/TopoWire.hpp>

const double M_PI = AMCAX::Constants::pi;
const double M_PI_2 = M_PI / 2.;
const double M_2_PI = 2. / M_PI;


struct PrismParam
{
    std::vector<std::array<double, 2>> points;
    double depth{ 0 };
    double taper{ 1.0 };
};

struct IntersectionResult
{
    std::array<double, 3> pos{};
    std::array<double, 3> normal{};
    double t = 0.0;
    std::array<double, 2> uv{};
};

struct RayData
{
    // double pos[3]{ 0,0,0 }; 
    // double dir[3]{ 0,0,0 }; 
    std::array<double, 3> pos{};
    std::array<double, 3> dir{};
};

struct ScopedTimer
{
    const char* label;
    std::chrono::steady_clock::time_point t0;
    explicit ScopedTimer(const char* lbl) : label{ lbl }, t0{ std::chrono::steady_clock::now() }
    {
    }
    ~ScopedTimer()
    {
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - t0).count();
        std::cerr << label << ": took " << ms << " ms\n";
    }
};

std::optional<IntersectionResult> FirstHit(const RayData& ray, AMCAX::BRepIntCurveSurface& brep, double tol = AMCAX::Precision::Confusion())
{
    AMCAX::Line3 line(
        AMCAX::Point3(ray.pos[0], ray.pos[1], ray.pos[2]), AMCAX::Direction3(ray.dir[0], ray.dir[1], ray.dir[2]));
    brep.PerformFirstPoint(line, tol);
    if (brep.NPoints() <= 0)
    {
        return std::nullopt;
    }

    const int idx = 0;
    const auto p = brep.Point(idx);
    const auto normal = [&]
        {
            AMCAX::Direction3 n;
            brep.SurfaceNormal(idx, n);
            return n;
        }();

        IntersectionResult r;
        std::copy_n(&p[0], 3, r.pos.begin());
        std::copy_n(&normal[0], 3, r.normal.begin());
        r.t = brep.W(idx);
        r.uv[0] = brep.U(idx);
        r.uv[1] = brep.V(idx);
        return r;
}

void Rotation(const AMCAX::Point3& angle, AMCAX::TopoShape& shape)
{
    AMCAX::Transformation3 aTransform;
    aTransform.SetRotation(AMCAX::CartesianCoordinateSystem::OZ(), angle[2]);
    shape = AMCAX::TransformShape(shape, aTransform);
    aTransform.SetRotation(AMCAX::CartesianCoordinateSystem::OY(), -angle[1]);
    shape = AMCAX::TransformShape(shape, aTransform);
    aTransform.SetRotation(AMCAX::CartesianCoordinateSystem::OX(), -angle[0]);
    shape = AMCAX::TransformShape(shape, aTransform);
}

void Move(const AMCAX::Vector3& move, AMCAX::TopoShape& shape)
{
    AMCAX::Transformation3 aTransform;
    aTransform.SetTranslation(move);
    shape = AMCAX::TransformShape(shape, aTransform);
}

AMCAX::TopoShape TransformCap(const AMCAX::TopoShape& cap, std::array<double, 2> tran)
{
    AMCAX::TopoShape cap2 = AMCAX::CopyShape(cap);
    AMCAX::Vector3 move{ tran[0], tran[1], 0. };
    Move(move, cap2);
    AMCAX::Point3 angle{ 0., 0., 0. };
    Rotation(angle, cap2);
    AMCAX::Point3 angle2{ M_2_PI, 0., M_2_PI };
    Rotation(angle2, cap2);
    /*AMCAX::Vector3 move2{ 1.,1. ,0. };
    Move(move2, cap2);*/
    return cap2;
}

AMCAX::TopoShape TransformPrism(const AMCAX::TopoShape& prism, std::array<double, 2> tran)
{
    AMCAX::TopoShape prism2 = AMCAX::CopyShape(prism);
    AMCAX::Vector3 move{ tran[0], tran[1], 0. };
    Move(move, prism2);
    AMCAX::Point3 angle{ 0., 0., 0. };
    Rotation(angle, prism2);
    AMCAX::Point3 angle2{ M_2_PI, 0., M_2_PI };
    Rotation(angle2, prism2);
    /*AMCAX::Vector3 move2{ 1.,1. ,0. };
    Move(move2, aPrism2);*/
    return prism2;
}

// 几何实例的封装 
class GeometryPrimitive
{
public:
    explicit GeometryPrimitive(const AMCAX::TopoShape& shape) : shape_(shape)
    {
    }

    // 预加载：按线程数为当前实例准备求交器缓存。
    // 每个线程各有一份独立的 BRepIntCurveSurface（breps_[tid]），
    // 这样 Perform/PerformFirstPoint 内部状态的写入互不影响，保证并行安全。 
    void prepareBreps(int threadCount)
    {
        breps_.resize(threadCount);
        for (int i = 0; i < threadCount; ++i)
        {
            breps_[i].Load(shape_, tol_);// 与该实例几何绑定一次；后续重复复用 
        }
    }

    // 通过 omp_get_thread_num() 取得 tid，索引到本线程的求交器副本 
    std::optional<IntersectionResult> IntersectionCalc(const RayData& ray)
    {
        int tid = omp_get_thread_num();
        AMCAX::BRepIntCurveSurface& brep = breps_[tid];
        return FirstHit(ray, brep, tol_);
    }

private:
    AMCAX::TopoShape shape_; // 实例的几何形状（已包含该实例的位姿）
    std::vector<AMCAX::BRepIntCurveSurface> breps_; // 每线程的求交器副本 
    inline static constexpr double tol_ = AMCAX::Precision::Confusion(); // 1e-7
};

// 构造所有实例 
std::vector<std::shared_ptr<GeometryPrimitive>> BuildScene(const AMCAX::TopoShape& capPrototype,
    const std::vector<std::array<double, 2>>& capTrans,
    const AMCAX::TopoShape& prismPrototype,
    const std::vector<std::array<double, 2>>& prismTranslations)
{
    ScopedTimer timer{ __func__ };

    std::vector<std::shared_ptr<GeometryPrimitive>> sceneObjects;
    sceneObjects.reserve(capTrans.size() + prismTranslations.size() * 6 + 1);

    // 球冠实例 
    for (const auto& t : capTrans)
    {
        sceneObjects.emplace_back(std::make_shared<GeometryPrimitive>(TransformCap(capPrototype, t)));
    }

    // 棱柱实例 
    for (int idx = 0; idx < 6; ++idx)
    {
        for (const auto& t : prismTranslations)
        {
            sceneObjects.emplace_back(std::make_shared<GeometryPrimitive>(TransformPrism(prismPrototype, t)));
        }
    }

    // 关键：预建每线程 BRep 副本 
    const int team = omp_get_max_threads();
    std::cout << "BuildScene use threads: " << team << "\n";
    for (auto& obj : sceneObjects)
    {
        obj->prepareBreps(team);
    }

    return sceneObjects;
}

bool ReadRayData(const std::filesystem::path& file, std::vector<RayData>& out)
{
    ScopedTimer timer{ __func__ };

    std::ifstream fin(file, std::ios::binary);
    if (!fin)
    {
        std::cerr << __func__ << ": cannot open '" << file << "'\n";
        return false;
    }

    constexpr std::size_t AVG_BYTES_PER_LINE = 100;
    std::error_code ec;
    if (auto bytes = std::filesystem::file_size(file, ec); !ec)
    {
        out.reserve(out.size() + static_cast<std::size_t>(bytes / AVG_BYTES_PER_LINE));
    }
    RayData tmp{};
    while (fin >> tmp.pos[0] >> tmp.pos[1] >> tmp.pos[2] >> tmp.dir[0] >> tmp.dir[1] >> tmp.dir[2])
    {
        tmp.pos[2] = 0.; // Only for more intersection
        out.emplace_back(tmp);
    }

    if (!fin.eof())
    {
        std::cerr << __func__ << ": parse error near byte " << fin.tellg() << "\n";
        return false;
    }

    return true;
}

bool ReadMoveData(const std::filesystem::path& file, std::vector<std::array<double, 2>>& out)
{
    std::ifstream fin(file, std::ios::binary);
    if (!fin)
    {
        std::cerr << __func__ << ": cannot open '" << file << "'\n";
        return false;
    }

    double x, y;
    while (fin >> x >> y)
    {
        out.emplace_back(std::array<double, 2>{x, y});
    }

    if (!fin.eof())
    {
        std::cerr << __func__ << ": parse error near byte " << fin.tellg() << "\n";
        return false;
    }
    return true;
}

std::optional<AMCAX::TopoShape> BuildSphericalCap(double radius, double height)
{
    if (radius <= 0. || height <= 0. || height >= radius)
    {
        std::cerr << std::string(__func__) << " invalid arguments\n";
        return std::nullopt;
    }
    const double zPos = radius - height;
    const AMCAX::TopoShape sphere = AMCAX::MakeSphere(radius);
    const AMCAX::Plane cutPlane(AMCAX::Point3{ 0., 0., zPos }, AMCAX::Direction3{ 0., 0., 1. }); // XOY平面
    const AMCAX::TopoShape placeFace = AMCAX::MakeFace(cutPlane);
    AMCAX::BoolBRepSplitter splitter;
    splitter.SetArguments({ sphere });
    splitter.SetTools({ placeFace });
    splitter.Build();
    const auto& modifiedFaces = splitter.Modified(placeFace);
    const AMCAX::TopoShape& cutFace = modifiedFaces.front();

    AMCAX::IndexSet<AMCAX::TopoShape> solids;
    AMCAX::TopoExplorerTool::MapShapes(splitter.Shape(), AMCAX::ShapeType::Solid, solids);
    std::vector<AMCAX::TopoShape> results;
    for (const auto* pariPtr : solids)
    {
        const AMCAX::TopoShape& solid = pariPtr->first;
        AMCAX::IndexSet<AMCAX::TopoShape> faces;
        AMCAX::TopoExplorerTool::MapShapes(solid, AMCAX::ShapeType::Face, faces);
        if (std::any_of(faces.begin(), faces.end(), [&](const auto* p) { return p->first.IsEqual(cutFace); }))
        {
            return solid;
        }
    }

    std::cerr << __func__ << ": unexpected 0 or >1 solids\n";
    return std::nullopt;
}

std::optional<AMCAX::TopoShape> BuildPrism(
    double baseWidthX, double spineLengthY, double height, double leftSlopeRad, double rightSlopeRad)
{
    if (baseWidthX <= 0. || spineLengthY <= 0. || height <= 0. || leftSlopeRad <= 0. || rightSlopeRad <= 0. ||
        leftSlopeRad + rightSlopeRad >= M_PI)
    {
        std::cerr << __func__ << ": invalid arguments\n";
        return std::nullopt;
    }
    // 夹角计算 
    const double tan1 = std::tan(leftSlopeRad);
    const double tan2 = std::tan(rightSlopeRad);
    // 若超过几何极限高度则截断 
    const double maxH = (baseWidthX * tan1 * tan2) / (tan1 + tan2); // 推导同旧代码
    if (height > maxH)
    {
        height = maxH;
    }
    // 推导关键坐标 
    const double halfX = 0.5 * baseWidthX;
    const double halfY = 0.5 * spineLengthY; // y 方向长度一半 
    const double topPosDX = height / tan1;   // 顶点相对位移 
    const double topXPos = halfX + topPosDX;
    const double topXNeg = -halfX + topPosDX;
    // 构建截面多边形 
    AMCAX::MakePolygon poly;
    poly.Add(AMCAX::Point3(halfX, -halfY, 0.0));
    poly.Add(AMCAX::Point3(topXPos, -halfY, height));
    poly.Add(AMCAX::Point3(topXNeg, -halfY, height));
    poly.Add(AMCAX::Point3(-halfX, -halfY, 0.0));
    poly.Close();
    const AMCAX::TopoWire wire = poly.Wire();
    const AMCAX::TopoFace face = AMCAX::MakeFace(wire, true);
    // 拉伸成棱柱 
    const AMCAX::TopoShape prism = AMCAX::MakePrism(face, AMCAX::Vector3(0., spineLengthY, 0.));
    return prism;
}

std::optional<AMCAX::TopoShape> BuildBox(double dx, double dy, double dz)
{
    if (dx <= 0.0 || dy <= 0.0 || dz <= 0.0)
    {
        std::cerr << __func__ << ": invalid dimension(s)\n";
        return std::nullopt;
    }
    const double hx = 0.5 * dx;
    const double hy = 0.5 * dy;
    const AMCAX::Point3 pMin{ -hx, -hy, 0. };
    const AMCAX::Point3 pMax{ hx, hy, dz };
    return AMCAX::MakeBox(pMin, pMax).Shape();
}

size_t get_memory_usage()
{
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    return pmc.PeakWorkingSetSize; // 返回峰值工作集大小（以字节为单位）
}

// 并行求交并写文件 
void DumpIntersections(const std::vector<RayData>& rays,
    const std::vector<std::shared_ptr<GeometryPrimitive>>& prims,
    const std::string& outName)
{
    std::ofstream fout(outName, std::ios::binary);
    if (!fout)
    {
        std::cerr << "cannot open " << outName << '\n';
        return;
    }
    else
    {
        fout.setf(std::ios::fixed);
        fout << std::setprecision(8);
    }

    std::atomic<std::size_t> globalCnt{ 0 };
    const int maxThreads = omp_get_max_threads();
    std::vector<long long> calcUsArr(maxThreads);
    std::vector<long long> ioUsArr(maxThreads);

#pragma omp parallel
    {
#pragma omp master //if(omp_get_thread_num() == 0)
        std::cout << "Parallel region thread count = " << omp_get_num_threads() << '\n';
        std::ostringstream localBuf;
        std::size_t localCnt = 0;

        using clock = std::chrono::steady_clock;
        const auto tCalcStart = clock::now();


#pragma omp for schedule(static)
        for (int i = 0; i < static_cast<int>(rays.size()); ++i)
        {
            const RayData& ray = rays[i];
            for (const auto& prim : prims)
            {
                // 若 brep_.PerformFirstPoint 不是线程安全，请把下一行放进 critical 
                if (auto res = prim->IntersectionCalc(ray))
                {
                    const auto& r = *res;
                    localBuf << r.pos[0] << ' ' << r.pos[1] << ' ' << r.pos[2] << ' ' << r.normal[0] << ' '
                        << r.normal[1] << ' ' << r.normal[2] << ' ' << r.t << ' ' << r.uv[0] << ' ' << r.uv[1]
                        << '\n';
                    ++localCnt;
                }
            }
        }
        const auto tCalcEnd = clock::now();
        calcUsArr[omp_get_thread_num()] =
            std::chrono::duration_cast<std::chrono::microseconds>(tCalcEnd - tCalcStart).count();

        const auto tIoStart = clock::now();
#pragma omp critical(file_write)
        fout << localBuf.str();
        const auto tIoEnd = clock::now();
        ioUsArr[omp_get_thread_num()] =
            std::chrono::duration_cast<std::chrono::microseconds>(tIoEnd - tIoStart).count();

        globalCnt.fetch_add(localCnt, std::memory_order_relaxed);
    }// parallel

    long long maxCalcUs = *std::max_element(calcUsArr.begin(), calcUsArr.end());
    long long maxIoUs = *std::max_element(ioUsArr.begin(), ioUsArr.end());
    std::cout << "total hit         = " << globalCnt.load() << '\n'
        << "calc  max   (ms)  = " << maxCalcUs / 1000.0 << '\n'
        << "file  I/O  max(ms)= " << maxIoUs / 1000.0 << '\n'
        << "peak memory (MB)  = " << get_memory_usage() / 1024.0 / 1024.0 << '\n';
}

int main(int argc, char** argv)
{
    int threads = 12;
    if (argc > 1)
        threads = std::clamp(std::stoi(argv[1]), 1, omp_get_num_procs());
    omp_set_dynamic(0); // 不允许 OpenMP 动态减线程
    omp_set_num_threads(threads);

    // 读取光线 / 变换数据 
    std::string dataDir = "./data/";
    std::vector<RayData> rayDataSet;
    if (!ReadRayData(dataDir + "raydata.txt", rayDataSet))
    {
        return EXIT_FAILURE;
    }
    std::cout << "loaded " << rayDataSet.size() << " rayData" << std::endl;

    std::vector<std::array<double, 2>> capTrans;
    if (!ReadMoveData(dataDir + "capTranslations.txt", capTrans))
    {
        return EXIT_FAILURE;
    }
    std::cout << "loaded " << capTrans.size() << " capTranslations" << std::endl;

    std::vector<std::array<double, 2>> prismTrans;
    if (!ReadMoveData(dataDir + "prismTranslations.txt", prismTrans))
    {
        return EXIT_FAILURE;
    }
    std::cout << "loaded " << prismTrans.size() << " prismTranslations" << std::endl;

    // 构造原型 cap, prism, box 
    const double radius = 0.04;
    const double height = 0.01;
    auto capOpt = BuildSphericalCap(radius, height);
    if (!capOpt)
    {
        std::cerr << "Failed to build spherical cap!\n";
        return EXIT_FAILURE;
    }
    const AMCAX::TopoShape& capProto = capOpt.value();

    auto prismOpt = BuildPrism(
        /*xWidth*/ 0.05,
        /*yWidth*/ 2.99,
        /*height*/ 0.10,
        /*leftSlopeRad  */ 45. * M_PI / 180.,
        /*rightSlopeRad  */ 45. * M_PI / 180.);
    if (!prismOpt)
    {
        std::cerr << "Failed to build prism!\n";
        return EXIT_FAILURE;
    }
    AMCAX::TopoShape prismProto = prismOpt.value();

    // 生成所有实例 
    auto sceneObjects = BuildScene(capProto, capTrans, prismProto, prismTrans);

    // 并行求交并写文件 
    DumpIntersections(rayDataSet, sceneObjects, dataDir + "result.txt");

    return EXIT_SUCCESS;
}
