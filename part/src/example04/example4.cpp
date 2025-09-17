#include <fillet/MakeFillet2d.hpp>
#include <common/IndexSet.hpp>
#include <topology/TopoExplorerTool.hpp>
#include <topology/TopoCast.hpp>
#include <topology/TopoShape.hpp>
#include <topology/TopoWire.hpp>
#include <topology/TopoFace.hpp>
#include <modeling/MakeFace.hpp>
#include <modeling/MakePolygon.hpp>
#include <common/VectorT.hpp>
#include <modeling/MakePrism.hpp>
#include <fillet/MakeChamfer.hpp>
#include <topology/TopoExplorer.hpp>
#include <common/Precision.hpp>
#include <topology/TopoTool.hpp>
#include <geometry/AdaptorGeom3Surface.hpp>
#include <topomesh/BRepMeshIncrementalMesh.hpp>
#include <modeling/MakeShapeTool.hpp>
#include <io/STLTool.hpp>
#include <topology/TopoVertex.hpp>
#include<common/Constants.hpp>
int main()
{//Create a rounded hexagonal prism
    AMCAX::Point3 p1(-80.0, 0.0, 56.0);
    AMCAX::MakePolygon makePolygon;
    int n = 6;
    for (int i = 0; i < n; ++i)
    {
        double t = AMCAX::Constants::pi * 2.0 * i / n;
        makePolygon.Add(p1.Translated(AMCAX::Vector3(0.0, std::cos(t), std::sin(t)) * 50.0));
    }
    makePolygon.Close();
    AMCAX::TopoWire w = makePolygon;
    AMCAX::TopoFace f = AMCAX::MakeFace(w, true);

    //Construct a rounded hexagon
    AMCAX::MakeFillet2d makeFillet2d(f);
    AMCAX::IndexSet<AMCAX::TopoShape> vertices;
    AMCAX::TopoExplorerTool::MapShapes(f, AMCAX::ShapeType::Vertex, vertices);
    for (int i = 0; i < vertices.size(); ++i)
    {
        makeFillet2d.AddFillet(AMCAX::TopoCast::Vertex(vertices[i]), 5.0);
    }
    AMCAX::TopoShape face2 = makeFillet2d.Shape();

    //Stretch rounded hexagons to create prisms
    AMCAX::TopoShape hexagonPrism = AMCAX::MakePrism(face2, AMCAX::Vector3(14.0, 0.0, 0.0));

    //Apply 3D chamfer
    AMCAX::MakeChamfer makeChamfer(hexagonPrism);
    for (AMCAX::TopoExplorer ex(hexagonPrism, AMCAX::ShapeType::Edge); ex.More(); ex.Next())
    {
        const AMCAX::TopoEdge& edge = AMCAX::TopoCast::Edge(ex.Current());
        AMCAX::TopoVertex vFirst, vLast;
        AMCAX::TopoExplorerTool::Vertices(edge, vFirst, vLast);
        AMCAX::Point3 pFirst = AMCAX::TopoTool::Point(vFirst);
        AMCAX::Point3 pLast = AMCAX::TopoTool::Point(vLast);
        if (std::fabs(pFirst[0] - pLast[0]) < AMCAX::Precision::Confusion())
        {
            makeChamfer.Add(0.5, edge);
        }
    }
    AMCAX::TopoShape hex = makeChamfer.Shape();

    // Meshing
    AMCAX::BRepMeshIncrementalMesh mesher(hex, 0.005, true);
    if (mesher.IsDone())
    {
        AMCAX::MakeShapeTool::EnsureNormalConsistency(hex);
    }

    AMCAX::STLTool::WriteShape(hex, "part4.stl");

}