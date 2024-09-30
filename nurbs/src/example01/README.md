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
	
	13. Convert the TopoShape object to a STEP file using AMCAX::STEP::StepWriter
	
	14. Write the header of the STEP file to the stream using Init() under AMCAX::STEP::StepWriter
	
	15. Convert Geom3BSplineSurface to TopoShape using MakeFace() under AMCAX::MakeFace
	
	16. Write the data portion of the STEP file using WriteShape() under AMCAX::STEP::StepWriter
	
	17. Use Done() under AMCAX::STEP::StepWriter to write the end of the STEP file and close the output file



<div align = center><img src="https://s2.loli.net/2024/06/11/12LFs57qNradIBT.png" width="600" height="300">