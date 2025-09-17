#include <memory>
#include <vector>

#include <common/PointT.hpp>
#include <geomAlgo/LawConstant.hpp>
#include <geometry/Geom3BSplineCurve.hpp>
#include <geometry/Geom3BSplineSurface.hpp>
#include <geometry/Geom3Circle.hpp>
#include <geometry/Geom3Ellipse.hpp>
#include <nurbs/NURBSAPIBlend.hpp>
#include <nurbs/NURBSAPIBuildCurve.hpp>
#include <nurbs/NURBSAPICircularSweep.hpp>
#include <nurbs/NURBSAPISweep.hpp>
#include<step/STEPTool.hpp>
#include <modeling/MakeFace.hpp>
#include<common/Constants.hpp>
#include <modeling/MakeShapeTool.hpp>

using namespace AMCAX;

void TestPipe()
{
	// build a complex pipe
	// build section curves
	std::shared_ptr<AMCAX::Geom3Ellipse> gellipse = std::make_shared<AMCAX::Geom3Ellipse>(AMCAX::Frame3(), 0.7, 0.5);
	gellipse->Translate(AMCAX::Vector3(3.0, 0.0, 0.0));

	std::vector<AMCAX::Point3> sectionPoles;
	sectionPoles.push_back(AMCAX::Point3(0.5, 0.5, 1.5));
	sectionPoles.push_back(AMCAX::Point3(0.5, -0.25, 1.5));
	sectionPoles.push_back(AMCAX::Point3(0.5, -0.75, 2.0));
	sectionPoles.push_back(AMCAX::Point3(0.5, -0.25, 2.5));
	sectionPoles.push_back(AMCAX::Point3(0.5, 0.5, 2.5));
	sectionPoles.push_back(AMCAX::Point3(0.5, 0.0, 2.0));
	std::shared_ptr<AMCAX::Geom3BSplineCurve> endingProfileCurve = AMCAX::NURBSAPIBuildCurve::BuildCurve(sectionPoles, 3, true);

	// build guide curves
	std::vector<AMCAX::Point3> guidePoles;
	guidePoles.push_back(AMCAX::Point3(3.0, 0.5, 0.0));
	guidePoles.push_back(AMCAX::Point3(3.0, 0.5, 2.0));
	guidePoles.push_back(AMCAX::Point3(0.5, 0.5, 2.0));
	std::shared_ptr<AMCAX::Geom3BSplineCurve> guide = AMCAX::NURBSAPIBuildCurve::BuildCurve(guidePoles, 2, false);

	// sweeping to build surface
	std::vector<std::pair<int, double>> guideCorrParams;
	std::vector<AMCAX::NURBSCurveSection> profiles;
	profiles.push_back(AMCAX::NURBSCurveSection(gellipse));
	profiles.push_back(AMCAX::NURBSCurveSection(endingProfileCurve));
	auto sweptSurfaces = AMCAX::NURBSAPISweep::SweepOneRail(profiles, guide, 0.0, guideCorrParams, false, true);
	std::shared_ptr<AMCAX::Geom3BSplineSurface> complexPipe = sweptSurfaces.front();

	// build a circle section pipe
	// build the pipe center curve
	std::vector<AMCAX::Point3> centerCurvePoles;
	centerCurvePoles.push_back(AMCAX::Point3(-3.0, 0.0, 0.0));
	centerCurvePoles.push_back(AMCAX::Point3(-3.0, 0.0, 2.0));
	centerCurvePoles.push_back(AMCAX::Point3(-1.0, 0.0, 2.0));
	std::shared_ptr<AMCAX::Geom3BSplineCurve> centerCurve = AMCAX::NURBSAPIBuildCurve::BuildCurve(centerCurvePoles, 2, false);

	// set the center curve as the spine
	std::shared_ptr<AMCAX::Geom3BSplineCurve> spine = centerCurve;
	double spineLeftBound = spine->FirstParameter();
	double spineRightBound = spine->LastParameter();

	// set the radius
	AMCAX::LawConstant radiusLaw;
	radiusLaw.Set(0.5, 0.0, 1.0);

	// sweep to make the circle section pipe
	auto [status, circlePipe] = AMCAX::NURBSAPICircularSweep::SweepWithCenterAndRadius(centerCurve, radiusLaw, spine, spineLeftBound, spineRightBound);
	if (status != AMCAX::NURBSSweepStatus::Success || !circlePipe)
	{
		return;
	}

	// set the parameters
	std::vector<double> parameters1 = { 1.0, 1.0 };
	std::vector<double> parameters2 = { 1.0, 1.0 };
	std::vector<double> tol = { 0.001, 0.1 * AMCAX::Constants::pi / 180.0, 0.05 };
	std::shared_ptr<AMCAX::Geom3BSplineSurface> blendSurface = AMCAX::NURBSAPIBlend::BlendSurfaces(circlePipe, false, false, AMCAX::ContinuityType::G2, parameters1, complexPipe, false, false, AMCAX::ContinuityType::G2, parameters2, true, true, tol);

	// write
	AMCAX::TopoShape C = MakeFace(blendSurface, 0.0);
	AMCAX::TopoShape L = MakeFace(sweptSurfaces[0], 0.0);
	AMCAX::TopoShape R = MakeFace(circlePipe, 0.0);

	std::list< AMCAX::TopoShape > shapes;
	shapes.push_back(L);
	shapes.push_back(C);
	shapes.push_back(R);
	AMCAX::TopoShape  result = AMCAX::MakeShapeTool::SewShape(shapes, AMCAX::Precision::Confusion());
	AMCAX::STEP::STEPTool::Write(result, "output.step");
}

int main()
{
	TestPipe();
}