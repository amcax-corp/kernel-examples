#include "mesh/io/OBJReader.hpp"
#include "mesh/io/OBJWriter.hpp"
#include "meshModeling/TriMesh_IncrementalRemeshing.hpp"

#include "example6.h"

using namespace AMCAX::Meshing;
using namespace AMCAX::Meshing::Mesh;
using namespace AMCAX::Meshing::Remeshing;
using TriSoupTraits = TriSoupTraits_Coord;
void Remeshing_Incremental()
{
    OUTPUT_DIRECTORY(Remeshing, Incremental);

    IOOptions io_options;
    io_options.vertex_has_point = true;

    OBJReader<TriSoupTraits>      obj_reader;
    OBJWriter<TriSoupTraits>      obj_writer;
    TriMesh_IncrementalRemeshing<TriSoupTraits> inc_remesher;
    std::string                   filename = "32770_sf";

    obj_reader.read("./data/" + filename + ".obj", io_options);
    obj_writer.clear();
    inc_remesher.setReferenceMesh(obj_reader.m_points, obj_reader.m_triangles);
    inc_remesher.setVariableMesh(obj_writer.m_points, obj_writer.m_triangles);

    TriMesh_IncrementalRemeshing<TriSoupTraits>::Params param;
    param.targetEdgeLength = 0.005;
    param.isAdaptive = false;

    inc_remesher.remesh(param);
    std::string out_filename =
        outdir + filename + "_Incremental_.obj";
    obj_writer.write(out_filename, io_options, 10);
}

int main()
{
    Remeshing_Incremental();
    return 0;
}