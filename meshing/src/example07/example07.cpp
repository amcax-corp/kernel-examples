// mesh IO header
#include "mesh/io/OBJReader.hpp"
#include "mesh/io/OBJWriter.hpp"
// mesh parameterization header
#include "meshModeling/MeshParameterization.hpp"
// some utils functions
#include "example07.h"

using namespace AMCAX::Meshing;
using namespace AMCAX::Meshing::Mesh;
using namespace AMCAX::Meshing::Parameterization;

void Parameterization_Bijective()
{

    IOOptions io_options;
    io_options.vertex_has_point = true;

    OBJReader<TriSoupTraits_Coord> obj_reader;
    OBJWriter<TriSoupTraits_Coord> obj_writer;
    // read mesh
    obj_reader.read("./data/parameterization_data/cow.obj", io_options);
    // define parameterization object
    AMCAX::Meshing::Parameterization::BijectivePara<TriSoupTraits_Coord> para(
        obj_reader.m_points, obj_reader.m_triangles, obj_writer.m_points);
    // execute algorithm
    para.parameterization();
    // write mesh
    obj_writer.m_triangles = std::move(obj_reader.m_triangles);
    std::string out_filename = "./res_parameterization.obj";
    obj_writer.write(out_filename, io_options, 10);
}

int main()
{
    Parameterization_Bijective();
    return 0;
}