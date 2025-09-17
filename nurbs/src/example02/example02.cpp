#include <vector>
#include <iostream>
#include <common/PointT.hpp>
#include <geometry/Geom3BSplineCurve.hpp>
#include <nurbs/NURBSAPIBuildCurve.hpp>
#include <nurbs/NURBSAPICircularSweep.hpp>
#include <geomAlgo/LawConstant.hpp>
#include <step/StepWriter.hpp>
#include <modeling/MakeFace.hpp>
#include <geometry/Geom3BSplineSurface.hpp>

using namespace AMCAX;

void TestPipe() {


	std::vector<AMCAX::Point3> centerCurvePoles;
	centerCurvePoles.push_back(AMCAX::Point3(-3.0, 0.0, 0.0));
	centerCurvePoles.push_back(AMCAX::Point3(-3.0, 0.0, 2.0));
	centerCurvePoles.push_back(AMCAX::Point3(-1.0, 0.0, 2.0));
	std::shared_ptr<AMCAX::Geom3BSplineCurve> centerCurve = AMCAX::NURBSAPIBuildCurve::BuildCurve(centerCurvePoles, 2, false);

	std::shared_ptr<AMCAX::Geom3BSplineCurve> spine = centerCurve;
	double spineLeftBound = spine->FirstParameter();
	double spineRightBound = spine->LastParameter();

	AMCAX::LawConstant radiusLaw;
	radiusLaw.Set(0.5, 0.0, 1.0);


	auto [status, circlePipe] = AMCAX::NURBSAPICircularSweep::SweepWithCenterAndRadius(centerCurve, radiusLaw, spine, spineLeftBound, spineRightBound);
	if (status != AMCAX::NURBSSweepStatus::Success || !circlePipe)
	{
		return;
	}


	AMCAX::STEP::STEPWriter writer("output.step");
	writer.Init();
	writer.WriteShape(MakeFace(circlePipe, 0.0));
	writer.Done();
}

int main()
{
	TestPipe();
}