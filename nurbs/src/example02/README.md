# NURBS modeling example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example shows some of the main modeling capabilities in the AMCAX NURBS module. The specific implementation is as follows:

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
	
	10. Convert the TopoShape object to a STEP file using AMCAX::STEP::StepWriter
	
	11. Write the header of the STEP file to the stream using Init() under AMCAX::STEP::StepWriter
	
	12. Convert Geom3BSplineSurface to TopoShape using MakeFace() under AMCAX::MakeFace
	
	13. Write the data portion of the STEP file using WriteShape() under AMCAX::STEP::StepWriter
	
	14. Use Done() under AMCAX::STEP::StepWriter to write the end of the STEP file and close the output file


<div align = center><img src="https://s2.loli.net/2024/06/11/lvyrE4oDGNc8ZFa.png" width="600" height="300">