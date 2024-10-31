#include <meshModeling/TriMesh_IncrementalRemeshing.hpp>
#include <mesh/io/IOOptions.hpp>
#include <mesh/io/OBJReader.hpp>
#include <mesh/io/OBJWriter.hpp>
#include "example06.h"

using namespace  AMCAX::Meshing::Mesh;
using namespace  AMCAX::Meshing::Remeshing;
using TriSoupTraits = AMCAX::Meshing::Mesh::TriSoupTraits_Coord;
void incremental_remesh_test()
{
    std::string inputfilename = "./data/remesh_data/filename_1.obj";

    IOOptions io_options;
    io_options.vertex_has_point = true;

    TriSoupTraits::Points    input_points, output_points;
    TriSoupTraits::Triangles input_triangles, output_triangles;

    OBJReader<TriSoupTraits> reader;

    reader.read(inputfilename, io_options);
    input_points = std::move(reader.m_points);
    input_triangles = std::move(reader.m_triangles);

    TriMesh_IncrementalRemeshing<TriSoupTraits> remesher;
    TriMesh_IncrementalRemeshing<TriSoupTraits>::Params params;
    output_points = input_points;
    output_triangles = input_triangles;

    params.featurePreserved = true;
    params.isAdaptive = true;
    params.iterNum = 10;
    params.Max_error = 0.0005;
    params.targetEdgeLength = 0.1;
    params.tolAngle = 30. / 180. * M_PI;

    remesher.setReferenceMesh(input_points, input_triangles);
    remesher.setVariableMesh(output_points, output_triangles);
    remesher.remesh(params);
    std::string outputfilename =
        "./data/" + std::to_string(params.iterNum) + ".obj";
    OBJWriter<TriSoupTraits> writer;
    writer.m_points = std::move(output_points);
    writer.m_triangles = std::move(output_triangles);
    writer.write(outputfilename, io_options, 15);
}

int main()
{
    incremental_remesh_test();
    return 0;
}