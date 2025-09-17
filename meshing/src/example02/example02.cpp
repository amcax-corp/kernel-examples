#include "mesh/io/OBJReader.hpp"
#include "mesh/io/OBJWriter.hpp"
#include "mesh/io/STLReader.hpp"
#include "mesh/io/STLWriter.hpp"
#include "meshModeling/MeshBoolean.hpp"
#include "meshModeling/TriMeshRepair.hpp"

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

void read_mesh(const std::string& filename, Points& points, Triangles& triangles, IOOptions& io_options
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

void write_mesh(const std::string& filename, const Points& points, const Triangles& triangles, IOOptions& io_options)
{
    OBJWriter writer;
    writer.m_points = std::move(points);
    writer.m_triangles = std::move(triangles);
    writer.write(filename, io_options, 10);
};

void MeshBoolean_MeshBoolean()
{
    // Define IO
    IOOptions io_options;
    io_options.vertex_has_point = true;

    Points    points1, points2, result_points;
    Triangles triangles1, triangles2, result_triangles;

    // read mesh
    read_mesh("./data/bunny25k.obj", points1, triangles1, io_options);
    read_mesh("./data/cow.obj", points2, triangles2, io_options);

    MeshBoolean boolean(true);
    // set input meshes
    boolean.addTriMeshAsInput(points1, triangles1);
    boolean.addTriMeshAsInput(points2, triangles2);
    // set output mesh
    std::vector<std::pair<MeshBoolean::iPoints, MeshBoolean::iTriangles>> result_meshes;
    result_meshes.emplace_back(result_points, result_triangles);
    boolean.setTriMeshAsOutput(result_meshes);

    // run arrangements and labeling.
    // the results will be temporarily cached, until be cleared or destroyed.
    boolean.computeLabels();

    // after arrangements and labeling done, we can
    // apply differenct boolean operations faster.
    // (NOTE: must call computeLabels before boolean operation)
    {
        boolean.Union();
        std::cout << "Union results: " << result_meshes.size() << " meshes" << std::endl;
        for (size_t i = 0; i < result_meshes.size(); ++i) {
            std::string filename = "AMCAXMeshing_Union_" + std::to_string(i) + ".obj";
            write_mesh(filename.c_str(), result_meshes[i].first, result_meshes[i].second, io_options);
        }
    }

    {
        boolean.Intersection();
        std::cout << "Intersection results: " << result_meshes.size() << " meshes" << std::endl;
        for (size_t i = 0; i < result_meshes.size(); ++i) {
            std::string filename = "AMCAXMeshing_Intersection_" + std::to_string(i) + ".obj";
            write_mesh(filename.c_str(), result_meshes[i].first, result_meshes[i].second, io_options);
        }
    }

    {
        boolean.Xor();
        std::cout << "Xor results: " << result_meshes.size() << " meshes" << std::endl;
        for (size_t i = 0; i < result_meshes.size(); ++i) {
            std::string filename = "AMCAXMeshing_Xor" + std::to_string(i) + ".obj";
            write_mesh(filename.c_str(), result_meshes[i].first, result_meshes[i].second, io_options);
        }
    }

    {
        boolean.Subtraction();
        std::cout << "Subtraction results: " << result_meshes.size() << " meshes" << std::endl;
        for (size_t i = 0; i < result_meshes.size(); ++i) {
            std::string filename = "AMCAXMeshing_Subtraction_" + std::to_string(i) + ".obj";
            write_mesh(filename.c_str(), result_meshes[i].first, result_meshes[i].second, io_options);
        }
    }
}

int main() {
    MeshBoolean_MeshBoolean();
}