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
#include <topomesh/BRepMeshIncrementalMesh.hpp>
#include <modeling/MakeShapeTool.hpp>
#include <io/STLTool.hpp>
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

    // Meshing
    AMCAX::BRepMeshIncrementalMesh mesher(hexagonPrism, 0.005, true);
    if (mesher.IsDone())
    {
        AMCAX::MakeShapeTool::EnsureNormalConsistency(hexagonPrism);
    }

    AMCAX::STLTool::WriteShape(hexagonPrism, "part3.stl");
}