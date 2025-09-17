#include "mesh/io/OBJReader.hpp"
#include "mesh/io/OBJWriter.hpp"
#include "meshModeling/TriSoup_FastQEM.hpp"
#include "meshModeling/TriSoup_ButterFlySubdivision.hpp"

using namespace AMCAX::Meshing;
using namespace AMCAX::Meshing::Mesh;
using namespace AMCAX::Meshing::Subdivision;
using namespace AMCAX::Meshing::Remeshing;

void Subdivision_TriSoup_ButterFly()
{
    IOOptions io_options;
    io_options.vertex_has_point = true;

    OBJReader<TriSoupTraits_Coord> obj_reader;
    OBJWriter<TriSoupTraits_Coord> obj_writer;

    obj_reader.read("./data/kelan.obj", io_options);
    for (double ratio : {2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12.})
    {
        TriSoup_ButterFlySubdivision<TriSoupTraits_Coord, true> subdivider(obj_reader.m_points, obj_reader.m_triangles);
        Logger::elapse_reset();
        size_t sub_times = size_t(std::ceil(ratio / 4.0) + 0.1);

        for (size_t i = 0; i < sub_times; i++)
            subdivider.subdivide();

        FastQEM<TriSoupTraits_Coord> fast_qem(std::move(subdivider.m_points), std::move(subdivider.m_triangles));

        if (size_t(obj_reader.m_triangles.size() * ratio + fast_qem.m_triangles.size() * 0.01) <
            fast_qem.m_triangles.size())fast_qem.simplify(size_t(obj_reader.m_triangles.size() * ratio), FLT_MAX, 20);

        auto elapsed = Logger::elapsed();

        Logger::info("ButterFly: ratio " + std::to_string(ratio) + ";  time " + std::to_string(elapsed.count()) + " s");

        obj_writer.clear();
        obj_writer.m_points = std::move(fast_qem.m_points);
        obj_writer.m_triangles = std::move(fast_qem.m_triangles);

        std::string out_filename = "TriSoupModifiedButterFly_" + std::to_string(ratio) + ".obj";
        obj_writer.write(out_filename, io_options, 10);
    }
}
int main()
{
    Subdivision_TriSoup_ButterFly();
}