#include <meshModeling/TriMesh_DefectDetector.hpp>
#include <mesh/io/OBJReader.hpp>
#include <mesh/io/OBJWriter.hpp>
#include <mesh/TriSoup.hpp>

using TriSoupTraits = AMCAX::Meshing::Mesh::TriSoupTraits_Coord;
using VecT = TriSoupTraits::VecT;
using PointT = TriSoupTraits::PointT;
using Points = TriSoupTraits::Points;
using Triangles = TriSoupTraits::Triangles;
using OBJReader = AMCAX::Meshing::Mesh::OBJReader<TriSoupTraits>;
using OBJWriter = AMCAX::Meshing::Mesh::OBJWriter<TriSoupTraits>;
using IOOptions = AMCAX::Meshing::Mesh::IOOptions;

int main()
{
    OBJReader obj_reader;
    OBJWriter obj_writer;

    IOOptions io_options;
    io_options.vertex_has_point = true;

    Points           input_points;
    Triangles        input_triangles;

    obj_reader.read("./data/panda.obj", io_options);
    input_points = std::move(obj_reader.m_points);
    input_triangles = std::move(obj_reader.m_triangles);

    AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits>detector(input_points, input_triangles);

    auto non_manifold_vertices = detector.DetectNonManifoldVertices();
    auto non_manifold_edges = detector.DetectNonManifoldEdges();
    auto non_manifold_edges_for_3DPrint = detector.DetectNonManifoldEdgesFor3DPrint();
    auto free_edges = detector.DetectFreeEdges();
    auto degenerate_faces = detector.DetectDegenerateFaces();
    auto duplicate_faces = detector.DetectDuplicateFaces();
    auto isolated_faces = detector.DetectIsolatedFaces();
    auto duplicate_vertices = detector.DetectDuplicateVertices();
    auto self_intersecting_faces = detector.DetectSelfIntersectingFaces();
    auto component_with_inconsistent_nosistent_normals = detector.DetectFacesWithInconsistentNormals();
}