#include <vector>
#include <iostream>
#include <common/PointT.hpp>
#include <geometry/Geom3BSplineCurve.hpp>
#include <nurbs/NURBSAPIBuildCurve.hpp>
#include <nurbs/NURBSAPICircularSweep.hpp>
#include <step/StepWriter.hpp>
#include <modeling/MakeFace.hpp>
#include <geometry/Geom3BSplineSurface.hpp>
#include <geometry/Geom3Ellipse.hpp>
#include <nurbs/NURBSAPISweep.hpp>


using namespace AMCAX;

void TestPipe()
{
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

	std::vector<AMCAX::Point3> guidePoles;
	guidePoles.push_back(AMCAX::Point3(3.0, 0.5, 0.0));
	guidePoles.push_back(AMCAX::Point3(3.0, 0.5, 2.0));
	guidePoles.push_back(AMCAX::Point3(0.5, 0.5, 2.0));
	std::shared_ptr<AMCAX::Geom3BSplineCurve> guide = AMCAX::NURBSAPIBuildCurve::BuildCurve(guidePoles, 2, false);

	std::vector<std::pair<int, double>> guideCorrParams;
	std::vector<AMCAX::NURBSCurveSection> profiles;
	profiles.push_back(AMCAX::NURBSCurveSection(gellipse));
	profiles.push_back(AMCAX::NURBSCurveSection(endingProfileCurve));
	auto sweptSurfaces = AMCAX::NURBSAPISweep::SweepOneRail(profiles, guide, 0.0, guideCorrParams, false, true);
	std::shared_ptr<AMCAX::Geom3BSplineSurface> complexPipe = sweptSurfaces.front();



	AMCAX::STEP::STEPWriter writer("output.step");
	writer.Init();
	writer.WriteShape(MakeFace(sweptSurfaces[0], 0.0));
	writer.Done();
}
int main()
{
	TestPipe();
}