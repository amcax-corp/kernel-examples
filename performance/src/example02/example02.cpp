#pragma once
#include <chrono>
#include <filesystem>
#include <iostream>
#include <mutex>
#include <omp.h>
#include <optional>
// clang-format off 
#include <windows.h>
#include <psapi.h>
// clang-format on 
#include <unordered_map>
#include <vector>
#include <array>
#include <algorithm>
#include <fstream>
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
#include <topology/TopoExplorer.hpp>
#include <topology/TopoExplorerTool.hpp>
#include <topology/TopoWire.hpp>

using SteadyClock = std::chrono::steady_clock;
using Microseconds = std::chrono::microseconds;

const double M_PI = AMCAX::Constants::pi;
const double M_PI_2 = M_PI / 2.;
const double M_2_PI = 2. / M_PI;

// 每个实例只保留：形状索引 + 世界坐标下的变换 
struct InstanceData
{
    int shapeIndex;
    AMCAX::Transformation3 trsf;
};

// 全局：去重后的“唯一几何形状”列表 
static std::vector<AMCAX::TopoShape> g_uniqueShapes;

// 全局：每个几何 + 每线程 的求交器缓存 
static std::vector<std::vector<AMCAX::BRepIntCurveSurface>> g_shapeBreps;

// 场景实例列表 
static std::vector<InstanceData> g_instances;

struct RayData
{
    std::array<double, 3> pos{};
    std::array<double, 3> dir{};
};

// 将射线的起点和方向都按给定变换 trsf 变换到新坐标系 
// 将射线变换到新坐标系（起点按 Point 变换，方向按 Direction 变换） 
inline void TransformRay(RayData& ray, const AMCAX::Transformation3& trsf)
{
    // 1) 变换起点 
    AMCAX::Point3 p(ray.pos[0], ray.pos[1], ray.pos[2]);
    p.Transform(trsf);
    ray.pos[0] = p.X();
    ray.pos[1] = p.Y();
    ray.pos[2] = p.Z();

    // 2) 变换方向（AMCAX::Direction3::Transform 会忽略平移，仅做旋转/缩放） 
    AMCAX::Direction3 d(ray.dir[0], ray.dir[1], ray.dir[2]);
    d.Transform(trsf);
    ray.dir[0] = d.X();
    ray.dir[1] = d.Y();
    ray.dir[2] = d.Z();
}

// 根据射线 parametric 形式 P = P0 + t·D，计算 t 处的空间点 

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

// 替代 TransformCap/TransformPrism 的做法：仅构建位姿 

// 仅生成位姿（先 Z 旋转，再 -Y、-X，最后平移），不改基础几何 
static AMCAX::Transformation3 MakeTransformXYZ(double tx, double ty, double rx, double ry, double rz)
{
    AMCAX::Transformation3 Rz;
    Rz.SetRotation(AMCAX::CartesianCoordinateSystem::OZ(), rz);
    AMCAX::Transformation3 Ry;
    Ry.SetRotation(AMCAX::CartesianCoordinateSystem::OY(), -ry);
    AMCAX::Transformation3 Rx;
    Rx.SetRotation(AMCAX::CartesianCoordinateSystem::OX(), -rx);
    AMCAX::Transformation3 M;
    M.SetTranslation(AMCAX::Vector3{ tx, ty, 0. });
    return M * Rz * Ry * Rx;
}

// 收集实例：注册唯一几何（cap/prism 各 1 次），并生成对应位姿列表 
void CollectInstances(const AMCAX::TopoShape& capProto,
    const std::vector<std::array<double, 2>>& capTrans,
    const AMCAX::TopoShape& prismProto,
    const std::vector<std::array<double, 2>>& prismTrans)
{
    g_uniqueShapes.clear();
    g_instances.clear();

    // 注册两个“唯一几何” 
    int capIdx = (int)g_uniqueShapes.size();
    g_uniqueShapes.push_back(capProto);
    int prismIdx = (int)g_uniqueShapes.size();
    g_uniqueShapes.push_back(prismProto);

    for (auto& t : capTrans)
    {
        //g_instances.push_back({capIdx, MakeTransform(t[0], t[1], /*angleZ=*/0.0)}); 
        AMCAX::Transformation3 T = MakeTransformXYZ(/*tx*/ t[0], /*ty*/ t[1],
            /*rx*/ M_2_PI, /*ry*/ 0.0, /*rz*/ M_2_PI);
        g_instances.push_back({ capIdx, T });
    }
    for (int r = 0; r < 6; ++r)
    {
        for (auto& t : prismTrans)
        {
            //g_instances.push_back({prismIdx, MakeTransform(t[0], t[1], /*angleZ=*/0.0)}); 
            AMCAX::Transformation3 T = MakeTransformXYZ(t[0], t[1],
                /*rx*/ M_2_PI, /*ry*/ 0.0, /*rz*/ M_2_PI);
            g_instances.push_back({ prismIdx, T });
        }
    }
    std::cout << "CollectInstances g_instances.size: " << g_instances.size() << "\n";
}

// ==== 准备缓存：为每个“唯一几何”加载 T 份求交器 ==== 
// 为每个"唯一几何"按线程数加载 BRep 求交器缓存（每线程一份，线程安全） 
void PrepareBRepCache(int threadCount, double tol_)
{
    int S = (int)g_uniqueShapes.size();
    g_shapeBreps.resize(S);

#pragma omp parallel for schedule(dynamic, 1)
    for (int s = 0; s < S; ++s)
    {
        // 每个几何分配 threadCount 份 
        g_shapeBreps[s].resize(threadCount);
        for (int t = 0; t < threadCount; ++t)
        {
            g_shapeBreps[s][t].Load(g_uniqueShapes[s], tol_);
        }
    }
}

// 读取射线文件（文本：x y z dx dy dz），按行解析；将 z 置 0 以增加命中 
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

// 读取平移表（每行：tx ty） 
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

// 构造球冠（球体被平面切割所得），返回 solid；失败返回 nullopt 
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

// 构造棱柱：按截面多边形沿 +Y 拉伸；合法性检查后返回形状 
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

// 查询进程峰值工作集（字节） 
size_t get_memory_usage()
{
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    return pmc.PeakWorkingSetSize; // 返回峰值工作集大小（以字节为单位）
}

// 口径：对每个 (ray, instance)，若存在前向(u>=0)交点，则选最小u的一次写出一行 
// 并行求交 + 每线程临时文件落盘：对每个 (ray, instance) 取第一解并写出 
bool IntersectAndDump(
    const std::vector<RayData>& rays, const std::string& outPath, std::uint64_t* totalHitsOut = nullptr)
{
    const int T = omp_get_max_threads();

    // 每线程临时文件，避免锁竞争 
    std::vector<std::string> partPaths(T);
    for (int t = 0; t < T; ++t)
        partPaths[t] = outPath + ".t" + std::to_string(t) + ".tmp";

    // 每线程用时（微秒） 
    std::vector<std::uint64_t> calcUsArr(T, 0);
    std::vector<std::uint64_t> ioUsArr(T, 0);

    std::atomic<std::uint64_t> totalHits{ 0 };

    auto tPar0 = SteadyClock::now();

#pragma omp parallel
    {
        const int tid = omp_get_thread_num();

        std::ofstream fout(partPaths[tid], std::ios::binary);
        if (!fout)
        {
            std::cerr << "cannot open " << partPaths[tid] << "\n";
        }
        else
        {
            fout.setf(std::ios::fixed);
            fout << std::setprecision(8);
        }

#pragma omp master
        std::cout << "Parallel region thread count = " << omp_get_num_threads() << '\n';

        std::uint64_t calc_us = 0;
        std::uint64_t io_us = 0;

#pragma omp for schedule(dynamic, 128)
        for (int i = 0; i < (int)rays.size(); ++i)
        {
            const RayData& ray = rays[i];

            for (const auto& inst : g_instances)
            {
                // ===== calc 计时开始 ===== 
                auto c0 = SteadyClock::now();

                // world → local （建议把 inv 预存到 InstanceData：inst.inv） 
                RayData localRay = ray;
                AMCAX::Transformation3 inv = inst.trsf.Inverted();
                TransformRay(localRay, inv);

                AMCAX::Line3 line(AMCAX::Point3(localRay.pos[0], localRay.pos[1], localRay.pos[2]),
                    AMCAX::Direction3(localRay.dir[0], localRay.dir[1], localRay.dir[2]));

                auto& intCS = g_shapeBreps[inst.shapeIndex][tid];   // 每几何×每线程缓存
                intCS.PerformFirstPoint(line, AMCAX::Precision::Confusion());
                if (intCS.NPoints() == 0 || !fout)
                    continue;

                const int kBest = 0; // 就用第一个解
                const double uBest = intCS.W(0);

                auto c1 = SteadyClock::now();
                calc_us += (std::uint64_t)std::chrono::duration_cast<Microseconds>(c1 - c0).count();
                // ===== calc 计时结束 ===== 

                if (kBest < 0 || !fout)
                    continue;

                // ===== file I/O 计时开始 ===== 
                auto w0 = SteadyClock::now();

                // local → world 
                const auto& lp = intCS.Point(kBest);
                AMCAX::Direction3 ln;
                intCS.SurfaceNormal(kBest, ln);

                AMCAX::Point3 wp(lp.X(), lp.Y(), lp.Z());
                wp.Transform(inst.trsf);
                AMCAX::Vector3 wn(ln.X(), ln.Y(), ln.Z());
                wn.Transform(inst.trsf);
                // wn.Normalize(); // 可选 

                // 写一行：x y z nx ny nz t u v 
                fout << wp.X() << ' ' << wp.Y() << ' ' << wp.Z() << ' ' << wn.X() << ' ' << wn.Y() << ' ' << wn.Z()
                    << ' ' << uBest << ' ' << intCS.U(kBest) << ' ' << intCS.V(kBest) << '\n';

                totalHits.fetch_add(1, std::memory_order_relaxed);

                auto w1 = SteadyClock::now();
                io_us += (std::uint64_t)std::chrono::duration_cast<Microseconds>(w1 - w0).count();
                // ===== file I/O 计时结束 ===== 
            }
        }

        // 回写每线程用时 
        calcUsArr[tid] = calc_us;
        ioUsArr[tid] = io_us;
    } // parallel

    auto tPar1 = SteadyClock::now();

    // 合并每线程文件（单线程），可单独统计 merge I/O 
    auto tMerge0 = SteadyClock::now();
    {
        std::ofstream out(outPath, std::ios::binary);
        if (!out)
        {
            std::cerr << "cannot open " << outPath << "\n";
            return false;
        }

        std::vector<char> buf(1 << 20); // 1MB 缓冲 
        for (const auto& part : partPaths)
        {
            std::ifstream in(part, std::ios::binary);
            if (!in)
                continue;
            while (in)
            {
                in.read(buf.data(), buf.size());
                out.write(buf.data(), in.gcount());
            }
            in.close();
            std::error_code ec;
            std::filesystem::remove(part, ec);
        }
    }
    auto tMerge1 = SteadyClock::now();

    // 统计：每线程累计 -> 取最大 
    const auto calcMaxUs = *std::max_element(calcUsArr.begin(), calcUsArr.end());
    const auto ioMaxUs = *std::max_element(ioUsArr.begin(), ioUsArr.end());

    const double calcMaxMs = calcMaxUs / 1000.0;
    const double ioMaxMs = ioMaxUs / 1000.0;
    const double parallelMs = std::chrono::duration<double, std::milli>(tPar1 - tPar0).count();
    const double mergeIOMs = std::chrono::duration<double, std::milli>(tMerge1 - tMerge0).count();

    if (totalHitsOut)
        *totalHitsOut = totalHits.load();
    std::cout << "total hit         = " << totalHits.load() << '\n';

    std::cout << "calc  max   (ms)= " << calcMaxMs << '\n'
        << "file  I/O  max(ms)= " << ioMaxMs << '\n'
        << "parallel total (ms)= " << parallelMs << '\n'
        << "merge I/O     (ms)= " << mergeIOMs << '\n'
        << "peak memory (MB)  = " << get_memory_usage() / 1024.0 / 1024.0 << '\n';

    return true;
}

// 程序入口：加载数据 → 构造几何 → 生成实例 → 加载缓存 → 并行求交和输出 
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

    // 2. 收集 & 去重 
    CollectInstances(capProto, capTrans, prismProto, prismTrans);

    // 3. 为每种形状加载求交器 
    PrepareBRepCache(threads, AMCAX::Precision::Confusion());

    // 4. 并行求交, 输出结果 
    IntersectAndDump(rayDataSet, dataDir + "result2.txt");

    return EXIT_SUCCESS;
}