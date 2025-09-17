#include "mesh/io/OBJReader.hpp"
#include "mesh/io/OBJWriter.hpp"
#include "meshModeling/MeshParameterization.hpp"
#include "meshModeling/TriMeshCut.hpp"

using namespace AMCAX::Meshing;
using namespace AMCAX::Meshing::Mesh;
using namespace AMCAX::Meshing::Parameterization;
// Define points and triangles from traits
using Points = typename TriSoupTraits_Coord::Points;
using Triangles = typename TriSoupTraits_Coord::Triangles;

// Function for parameterization with mesh cut
void Parameterization_With_MeshCut()
{
    IOOptions io_options;
    io_options.vertex_has_point = true;

    OBJReader<TriSoupTraits_Coord> obj_reader;
    OBJWriter<TriSoupTraits_Coord> obj_writer;

    std::string in_filename = "./data/bunny25k.obj";
    std::string out_cut_filename = "bunny_cut.obj";
    std::string out_para_filename = "bunny_parameterization.obj";

    // Read the object file
    obj_reader.read(in_filename, io_options);

    Points    i_points = std::move(obj_reader.m_points);
    Triangles i_triangles = std::move(obj_reader.m_triangles);

    // Perform mesh cut
    AMCAX::Meshing::TriMeshCut::GreedyCut<TriSoupTraits_Coord> mesh_cut(i_points, i_triangles, /*verbose*/ true);

    Points    cut_points;
    Triangles cut_triangles;

    mesh_cut.cut(cut_points, cut_triangles);

    // Write the cut mesh to a new file
    obj_writer.m_points = cut_points;
    obj_writer.m_triangles = cut_triangles;
    obj_writer.write(out_cut_filename, io_options, 10);
    obj_writer.clear();

    Points para_points;

    // Perform bijective parameterization on the cut mesh
    AMCAX::Meshing::Parameterization::BijectivePara<TriSoupTraits_Coord> para(cut_points, cut_triangles, para_points, /*verbose*/ true);
    para.parameterization();

    // Write the parameterized cut mesh to a new file
    obj_writer.m_points = std::move(para_points);
    obj_writer.m_triangles = std::move(cut_triangles);
    obj_writer.write(out_para_filename, io_options, 10);
}

int main()
{
    Parameterization_With_MeshCut();
}