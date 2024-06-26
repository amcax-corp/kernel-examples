﻿#include <geometry/Geom2Circle.hpp>
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

int main()
{
    //Build a sweep path
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
    
    AMCAX::MakeGeom3Circle makecircle(AMCAX::Point3(-26.3, 0.0, 78.5), AMCAX::Direction3(1.0, 0.0, 0.0), 10.0);
    AMCAX::MakeEdge makeedge(makecircle.Value());
    AMCAX::TopoWire profile1 = AMCAX::MakeWire(makeedge.Edge());

    AMCAX::TopoShape pipe1 = AMCAX::MakePipe(spine, AMCAX::MakeFace(profile1));
   

    // Meshing
    AMCAX::BRepMeshIncrementalMesh mesher(pipe1, 0.005, true);
    if (mesher.IsDone())
    {
        AMCAX::MakeShapeTool::EnsureNormalConsistency(pipe1);
    }

    AMCAX::STLTool::WriteShape(pipe1, "part5.stl");

}