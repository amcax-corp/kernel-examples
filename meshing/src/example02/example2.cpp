#include "mesh/io/OBJReader.hpp"
#include "mesh/io/OBJWriter.hpp"
#include "mesh/io/STLReader.hpp"
#include "mesh/io/STLWriter.hpp"
#include "meshModeling/MeshBoolean.hpp"
#include "meshModeling/TriMeshRepair.hpp"


#include "example2.h"



// geometry kernel, hidden for users, just use it. :D
using EIAC = AMCAX::Meshing::Geometry::EIAC;
// Triangle soup traits defined by Common
using TriSoupTraits = AMCAX::Meshing::Mesh::TriSoupTraits_Coord;

// points and triangles from traits
using Points = typename TriSoupTraits::Points;
using Triangles = typename TriSoupTraits::Triangles;

// Define reader and writer
using OBJReader = AMCAX::Meshing::Mesh::OBJReader<TriSoupTraits>;
using OBJWriter = AMCAX::Meshing::Mesh::OBJWriter<TriSoupTraits>;
using STLReader = AMCAX::Meshing::Mesh::STLReader<TriSoupTraits>;
using STLWriter = AMCAX::Meshing::Mesh::STLWriter<TriSoupTraits>;
using IOOptions = AMCAX::Meshing::Mesh::IOOptions;

// Define boolean
using MeshBoolean = AMCAX::Meshing::Boolean::MeshBoolean<EIAC, TriSoupTraits>;

void read_mesh(const std::string& filename, Points& points,
    Triangles& triangles, IOOptions& io_options
)
{
    if (AMCAX::Meshing::ends_with(filename, ".obj"))
    {
        OBJReader reader;
        reader.read(filename, io_options);

        points = std::move(reader.m_points);
        triangles = std::move(reader.m_triangles);
    }
    else if (AMCAX::Meshing::ends_with(filename, ".stl"))
    {
        STLReader reader;
        reader.read(filename, io_options);

        points = std::move(reader.m_points);
        triangles = std::move(reader.m_triangles);
    }
}

void write_mesh(const std::string& filename, const Points& points,
    const Triangles& triangles, IOOptions& io_options)
{
    OBJWriter writer;
    writer.m_points = std::move(points);
    writer.m_triangles = std::move(triangles);
    writer.write(filename, io_options, 10);
};

void MeshBoolean_MeshBoolean()
{
    OUTPUT_DIRECTORY(Boolean, Boolean);

    // Define IO
    IOOptions io_options;
    io_options.vertex_has_point = true;

    Points    points1, points2, result_points;
    Triangles triangles1, triangles2, result_triangles;

    // read mesh
    read_mesh("./data/boolean_data/bunny25k.obj", points1, triangles1, io_options);
    read_mesh("./data/boolean_data/cow.obj", points2, triangles2, io_options);

    MeshBoolean boolean(true);
    // set input meshes
    boolean.addTriMeshAsInput(points1, triangles1);
    boolean.addTriMeshAsInput(points2, triangles2);
    // set output mesh
    boolean.setTriMeshAsOutput(result_points, result_triangles);

    // run arrangements and labeling.
    // the results will be temporarily cached, until be cleared or destroyed.
    boolean.computeLabels();

    // after arrangements and labeling done, we can
    // apply differenct boolean operations faster.
    // (NOTE: must call computeLabels before boolean operation)
    {
        boolean.Union();
        make_file_writable(outdir + "AMCAXMeshing_Union.obj");
        write_mesh(outdir + "AMCAXMeshing_Union.obj", result_points,
            result_triangles, io_options);
    }

    {
        boolean.Intersection();
        make_file_writable(outdir + "AMCAXMeshing_Intersection.obj");
        write_mesh(outdir + "AMCAXMeshing_Intersection.obj", result_points,
            result_triangles, io_options);
    }

    {
        boolean.Xor();
        make_file_writable(outdir + "AMCAXMeshing_Xor.obj");
        write_mesh(outdir + "AMCAXMeshing_Xor.obj", result_points, result_triangles,
            io_options);
    }

    {
        boolean.Subtraction();
        make_file_writable(outdir + "AMCAXMeshing_Subtraction.obj");
        write_mesh(outdir + "AMCAXMeshing_Subtraction.obj", result_points,
            result_triangles, io_options);
    }
}

int main() {

    MeshBoolean_MeshBoolean();

    return 0;
}