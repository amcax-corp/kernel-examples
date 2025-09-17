# NURBS modeling example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example shows some of the main modeling capabilities in the AMCAX NURBS module. The specific implementation is as follows:

### 1. Build the left pipe

	1. Create an ellipse using AMCAX::Geom3Ellipse
	
	2. The ellipse is translated using the Translate() method
	
	3. Define a vector named sectionPoles using std::vector<AMCAX::Point3>
	
	4. Use AMCAX::NURBSAPIBuildCurve::BuildCurve create a b-spline curve
	
	5. Use std::shared_ptr<AMCAX::Geom3BSplineCurve> to define a shared pointer named endingProfileCurve to store the B-spline curve
	
	6. Define a vector named guidePoles using std::vector<AMCAX::Point3>
	
	7. Use AMCAX::NURBSAPIBuildCurve::BuildCurve create a b-spline curve
	
	8. Define a shared pointer called guide to store the B-spline using std::shared_ptr<AMCAX::Geom3BSplineCurve>
	
	9. Define vectors guideCorrParams using std::vector<std::pair<int, double>>
	
	10. Define vector profiles using std::vector<AMCAX::NURBSCurveSection>
	
	11. Use AMCAX::NURBSAPISweep::SweepOneRail execution sweep one side along the spine
	
	12. Obtain the surface and store it in complexPipe

### 2. Construct the right circular section pipe

	1. Define vector centerCurvePoles using std::vector<AMCAX::Point3>
	
	2. Define the pointer centerCurve using std::shared_ptr<AMCAX::Geom3BSplineCurve>
	
	3. Use AMCAX::NURBSAPIBuildCurve::BuildCurve NURBS curve is established
	
	4. Define the spine pointer using std::shared_ptr<AMCAX::Geom3BSplineCurve>
	
	5. Use FirstParameter() and LastParameter() in AMCAX::Geom3BSplineCurve to obtain the parameter range of the spine curve
	
	6. Create an object radiusLaw using AMCAX::LawConstant
	
	7. Use Set() under AMCAX::LawConstant to set parameters
	
	8. Use AMCAX::under NURBSAPICircularSweep SweepWithCenterAndRadius () to define curve by the center and radius of circular contour scanning
	
	9. The result of the scan is stored in circlePipe and a status is returned

### 3. Build an intermediate transition surface

	1. Use std::vector<double> to define vectors parameters1, parameters2, tol
	
	2. Use the STD:：from < AMCAX:：Geom3BSplineSurface > blendSurface definition pointer
	
	3. Construct a mixed surface connecting two surfaces using BlendSurfaces() under AMCAX::NURBSAPIBlend
	
	4. Use AMCAX::ContinuityType to set the continuity type
	
	5. Construct a blendSurface that connects two surfaces using BlendSurfaces() under AMCAX::NURBSAPIBlend

### 4. Generate the step file

	1. Use MakeFace() under AMCAX::MakeFace to convert Geom3BSplineSurface to TopoShape
	
	2. Use SewShape() under AMCAX::MakeShapeTool to merge the three shapes into one
	
	3. Use Write() under AMCAX::STEP::STEPTool to write the shape to a file



<div align = center><img src="https://s2.loli.net/2024/06/28/2LlvhGrIe6pqbsg.png" width="600" height="300">