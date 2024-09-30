# Build a curved pipe

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

#### The example implementation builds the curved track pipe1. The specific implementation is as follows:
## 1. Build a sweep path

	1. Create a 2D circle using the AMCAX::MakeGeom2Circle class.

	2. Use the AMCAX::GccLine2Tangent class to construct a line tangent to a 2D circle.

	3. Use AMCAX::GeometryTool::To3d class converts a 2 d curve to a 3 d curve.

	4. Create the arc using the AMCAX::MakeArcOfCircle class.

	5. Create a line segment using the AMCAX::MakeSegment class.

	6. Use the AMCAX::MakeEdge class to create edges from curves.

	7. Create paths from edges using the AMCAX::MakeWire class.

## 2. Create the outline

	1. Create the outline using the AMCAX::MakeGeom3Circle class.


## 3. Create a 2D offset line

	1. Use the AMCAX::CopyShape class to copy the outline formed in the previous step.

	2. Create a 2D offset curve using the AMCAX::MakeOffset class.

## 4. Create a scanning surface

	1. Use the AMCAX::MakeFace class to generate surfaces as outline shapes.

	2. Construct the scanned entity using the AMCAX::MakePipe class.

## 5. Meshing

	1. Using AMCAX::MakeShapeTool::EnsureNormalConsistency () to check and adjust the shape of normal, to ensure the consistency of shape mesh normals.

	2. Use AMCAX::STLTool::WriteShape class will topology graphics pipe1 generated a STL file called part5.

<div align = center><img src="https://s2.loli.net/2024/09/30/vprfRF7euVBSDxN.png" width="300" height="300">