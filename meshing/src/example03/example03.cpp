#include "meshModeling/MeshArrangements.hpp"
#include "mesh/io/OBJReader.hpp"
#include "mesh/io/OBJWriter.hpp"
#include "mesh/io/STLReader.hpp"
#include "mesh/io/STLWriter.hpp"
#include "meshModeling/TriMeshRepair.hpp"

using namespace AMCAX::Meshing;
using namespace AMCAX::Meshing::Mesh;
using namespace AMCAX::Meshing::MeshTools;

void MeshRepair_MeshRepair()
{
    bool first = true;
    int  stage;
    AMCAX::Meshing::MeshTools::TriMeshRepair<TriSoupTraits_Coord>::ProFn pro_fn =
        [&first, &stage](int _stage, AMCAXMeshing_UNUSED bool& cancel) -> void
        {
            stage = _stage;
            if (!first)
                std::cout << "\r\033[K";
            std::cout << "stage: " << _stage << "/" << AMCAX::Meshing::MeshTools::TriMeshRepair<TriSoupTraits_Coord>::Total;
            first = false;

            // set cancel to true if you want to terminate the algorithm :)
            if (stage == AMCAX::Meshing::MeshTools::TriMeshRepair<
                TriSoupTraits_Coord>::Stage::Total)
                std::cout << std::endl;
        };

    IOOptions io_options;
    io_options.vertex_has_point = true;
    io_options.face_has_normal = true;

    OBJReader<TriSoupTraits_Coord> obj_reader;
    STLReader<TriSoupTraits_Coord> stl_reader;
    OBJWriter<TriSoupTraits_Coord> obj_writer;
    STLWriter<TriSoupTraits_Coord> stl_writer;
    TriSoupTraits_Coord::Points    result_points;
    TriSoupTraits_Coord::Triangles result_triangles;

    stl_reader.read("./data/CamelBox.stl", io_options);
    TriMeshRepair<TriSoupTraits_Coord> repair(stl_reader.m_points, stl_reader.m_triangles);

    repair.repair(true, pro_fn);

    stl_writer.m_points = repair.m_points;
    stl_writer.m_triangles = repair.m_triangles;
    io_options.stl_binary = true;
    stl_writer.write("repaired.stl", io_options, 10);

    obj_writer.m_points = repair.m_points;
    obj_writer.m_triangles = repair.m_triangles;
    obj_writer.write("repaired.obj", io_options, 10);
}

int main() {
    MeshRepair_MeshRepair();
}