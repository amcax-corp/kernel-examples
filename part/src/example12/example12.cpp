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
#include <topology/TopoVertex.hpp>
#include <geometry/Geom2Circle.hpp>
#include <geometry/MakeGeom2Circle.hpp>
#include <geometry/MakeGeom3Circle.hpp>
#include <common/CartesianCoordinateSystem.hpp>
#include <geomAlgo/GccLine2Tangent.hpp>
#include <geometry/GeometryTool.hpp>
#include <geomAlgo/GccEntity.hpp>
#include <geometry/AdaptorGeom2Curve.hpp>
#include <math/CurveCalculation.hpp>
#include <geometry/Geom3TrimmedCurve.hpp>
#include <geometry/MakeArcOfCircle.hpp>
#include <geometry/MakeSegment.hpp>
#include <topology/TopoEdge.hpp>
#include <modeling/MakeEdge.hpp>
#include <modeling/MakeWire.hpp>
#include <topology/TopoCast.hpp>
#include <modeling/MakeFace.hpp>
#include <topomesh/BRepMeshIncrementalMesh.hpp>
#include <modeling/MakeShapeTool.hpp>
#include <io/STLTool.hpp>
#include <modeling/CopyShape.hpp>
#include <offset/MakeOffset.hpp>
#include <offset/MakePipe.hpp>
#include <geomAlgo/GccQualifiedCurve.hpp>
#include <modeling/TransformShape.hpp>
#include <boolean/BoolBRepFuse.hpp>
#include <boolean/BoolBRepCut.hpp>
#include <modeling/MakeCylinder.hpp>
#include <fillet/MakeFillet.hpp>
int main()
{
    // Make a polygon
    AMCAX::Point3 p1(-80.0, 0.0, 56.0);
    AMCAX::MakePolygon makePolygon;
    int n = 6;
    for (int i = 0; i < n; ++i)
    {
        double t = M_PI * 2.0 * i / n;
        makePolygon.Add(p1.Translated(AMCAX::Vector3(0.0, std::cos(t), std::sin(t)) * 50.0));
    }
    makePolygon.Close();
    AMCAX::TopoWire w = makePolygon;
    AMCAX::TopoFace f = AMCAX::MakeFace(w, true);

    // 2D fillet
    AMCAX::MakeFillet2d makeFillet2d(f);
    AMCAX::IndexSet<AMCAX::TopoShape> vertices;
    AMCAX::TopoExplorerTool::MapShapes(f, AMCAX::ShapeType::Vertex, vertices);
    for (int i = 0; i < vertices.size(); ++i)
    {
        makeFillet2d.AddFillet(AMCAX::TopoCast::Vertex(vertices[i]), 5.0);
    }
    AMCAX::TopoShape face2 = makeFillet2d.Shape();

    // Extrusion
    AMCAX::TopoShape hexagonPrism = AMCAX::MakePrism(face2, AMCAX::Vector3(14.0, 0.0, 0.0));

    // 3D Chamfer
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

    // Spine of pipe
    AMCAX::Point2 center1(-26.3, 58.5);
    AMCAX::Point2 center2(-63.8, 76.0);
    std::shared_ptr<AMCAX::Geom2Circle> circle2d1 = AMCAX::MakeGeom2Circle(AMCAX::Axis2(center1, AMCAX::CartesianCoordinateSystem::DY2()), 20.0);
    std::shared_ptr<AMCAX::Geom2Circle> circle2d2 = AMCAX::MakeGeom2Circle(AMCAX::Axis2(center2, -AMCAX::CartesianCoordinateSystem::DY2()), 20.0);
    AMCAX::GccLine2Tangent gcc(AMCAX::GccEntity::Enclosing(AMCAX::AdaptorGeom2Curve(circle2d1)), AMCAX::GccEntity::Outside(AMCAX::AdaptorGeom2Curve(circle2d2)), 0.0);
    if (!gcc.IsDone() || gcc.NSolutions() != 1)
    {
        throw AMCAX::ConstructionError();
    }
    double parSol1, parArg1, parSol2, parArg2;
    AMCAX::Point2 pointSol1, pointSol2;
    gcc.Tangency1(0, parSol1, parArg1, pointSol1);
    gcc.Tangency2(0, parSol2, parArg2, pointSol2);
    AMCAX::Line2 tangentLine = gcc.Solution(0);

    AMCAX::Frame3 localframe(AMCAX::CartesianCoordinateSystem::Origin(), -AMCAX::CartesianCoordinateSystem::DY(), AMCAX::CartesianCoordinateSystem::DX());
    std::shared_ptr<AMCAX::Geom3Curve> c13d = AMCAX::GeometryTool::To3d(localframe, circle2d1);
    std::shared_ptr<AMCAX::Geom3Curve> c23d = AMCAX::GeometryTool::To3d(localframe, circle2d2);
    AMCAX::Line3 line = AMCAX::CurveCalculation::To3d(localframe, tangentLine);
    std::shared_ptr<AMCAX::Geom3TrimmedCurve> arc1 = AMCAX::MakeArcOfCircle(std::static_pointer_cast<AMCAX::Geom3Circle>(c13d)->Circle(), 0.0, parArg1, true);
    std::shared_ptr<AMCAX::Geom3TrimmedCurve> arc2 = AMCAX::MakeArcOfCircle(std::static_pointer_cast<AMCAX::Geom3Circle>(c23d)->Circle(), 0.0, parArg2, true);
    std::shared_ptr<AMCAX::Geom3TrimmedCurve> seg0 = AMCAX::MakeSegment(arc1->Value(0.0), arc1->Value(0.0).Translated(AMCAX::Vector3(26.3, 0.0, 0.0)));
    std::shared_ptr<AMCAX::Geom3TrimmedCurve> seg1 = AMCAX::MakeSegment(line, parSol1, parSol2);
    std::shared_ptr<AMCAX::Geom3TrimmedCurve> seg2 = AMCAX::MakeSegment(arc2->Value(0.0), arc2->Value(0.0).Translated(AMCAX::Vector3(-16.2, 0.0, 0.0)));
    AMCAX::TopoEdge e0 = AMCAX::MakeEdge(seg0);
    AMCAX::TopoEdge e1 = AMCAX::MakeEdge(arc1);
    AMCAX::TopoEdge e2 = AMCAX::MakeEdge(seg1);
    AMCAX::TopoEdge e3 = AMCAX::MakeEdge(arc2);
    AMCAX::TopoEdge e4 = AMCAX::MakeEdge(seg2);
    AMCAX::MakeWire makewire;
    makewire.Add({ e0, e1, e2, e3, e4 });
    AMCAX::TopoWire spine = makewire.Wire();

    // Profile of pipe
    AMCAX::MakeGeom3Circle makecircle(AMCAX::Point3(-26.3, 0.0, 78.5), AMCAX::Direction3(1.0, 0.0, 0.0), 10.0);
    AMCAX::MakeEdge makeedge(makecircle.Value());
    AMCAX::TopoWire profile1 = AMCAX::MakeWire(makeedge.Edge());
    

    // Make 2D offset
    AMCAX::TopoWire profile2 = AMCAX::TopoCast::Wire(AMCAX::CopyShape(profile1));
    AMCAX::MakeOffset offset(profile2);
    offset.Perform(6.0);
    if (offset.IsDone())
    {
        profile2 = AMCAX::TopoCast::Wire(offset.Shape());
    }

    // Make pipe
    AMCAX::TopoShape pipe1 = AMCAX::MakePipe(spine, AMCAX::MakeFace(profile1));
    AMCAX::TopoShape pipe2 = AMCAX::MakePipe(spine, AMCAX::MakeFace(profile2));

    // Make a cylinder
    AMCAX::TopoShape middleCylinder = AMCAX::MakeCylinder(AMCAX::Frame3(AMCAX::Point3(0.0, 0.0, 0.0), AMCAX::CartesianCoordinateSystem::DZ()), 31.0, 114.0);

    // 3D fillet
    AMCAX::MakeFillet fillet(middleCylinder);
    for (AMCAX::TopoExplorer ex(middleCylinder, AMCAX::ShapeType::Edge); ex.More(); ex.Next())
    {
        const auto& edge = AMCAX::TopoCast::Edge(ex.Current());
        if (AMCAX::TopoTool::IsClosed(edge))
        {
            fillet.Add(1.0, edge);
        }
    }
    middleCylinder = fillet.Shape();

    // Mirror tranformation
    AMCAX::Transformation3 tr;
    tr.SetMirror(AMCAX::Axis3(AMCAX::Point3(0.0, 0.0, 56.0), AMCAX::CartesianCoordinateSystem::DY()));
    AMCAX::TopoShape pipe3 = AMCAX::TransformShape(pipe1, tr, true);
    AMCAX::TopoShape pipe4 = AMCAX::TransformShape(pipe2, tr, true);
    AMCAX::TopoShape hex2 = AMCAX::TransformShape(hex, tr, true);

    // Boolean
    AMCAX::TopoShape result = AMCAX::BoolBRepFuse(middleCylinder, pipe2);
    result = AMCAX::BoolBRepFuse(result, pipe4);
    result = AMCAX::BoolBRepFuse(result, hex);
    result = AMCAX::BoolBRepFuse(result, hex2);
    result = AMCAX::BoolBRepCut(result, pipe1);
    result = AMCAX::BoolBRepCut(result, pipe3);

    // Make a hole
    AMCAX::TopoShape hole = AMCAX::MakeCylinder(AMCAX::Frame3(AMCAX::Point3(0.0, 0.0, 0.0), AMCAX::CartesianCoordinateSystem::DZ()), 25.0, 114.0);
    result = AMCAX::BoolBRepCut(result, hole);

    // Meshing
    AMCAX::BRepMeshIncrementalMesh mesher(result, 0.005, true);
    if (mesher.IsDone())
    {
        AMCAX::MakeShapeTool::EnsureNormalConsistency(result);
    }

    // Export to a STL file
    AMCAX::STLTool::WriteShape(result, "partSample.stl");

}