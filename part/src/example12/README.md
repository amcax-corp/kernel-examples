# Entity modeling example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example uses a simplified valve model to demonstrate some of the main modeling capabilities in the AMCAX kernel. The specific implementation is as follows:

## 1. Create polygons

#### Create a hexagon
	1. Create a hexagon using the AMCAX::MakePolygon class.

	2. Construct a face using the AMCAX::MakeFace class.

## 2. Apply 2D rounded corners

#### Construct a rounded hexagon

	1. Use the AMCAX::MakeFillet2d class to apply 2D rounded corners to each vertex of a hexagon to construct a rounded hexagon.

	2. Use AMCAX::BRepMeshIncrementalMesh class for each generated grids in shape.

## 3. Stretch the column

#### creates a hexagonal prism
	1. Use the AMCAX::MakePrism class to stretch the rounded hexagon to create a hexagonal prism.

	2. Use AMCAX::BRepMeshIncrementalMesh class for each generated grids in shape.

## 4. Apply 3D chamfer

#### Construct a 3D chamfered hexagonal prism

	1. Use the AMCAX::MakeChamfer class to apply the 3D chamfer effect to the hexagonal prism.

	2. Use AMCAX::BRepMeshIncrementalMesh class for each generated grids in shape.

# Build a curved pipe

#### Construct two curved pipes, namely pipe1 and pipe2
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

# Build valve

## 1. Create the cylinder

#### Construct a cylinder

	1. Create a cylinder using the AMCAX::MakeCylinder class.


## 2. Apply 3D rounded corners

#### Construct a 3D cylinder with rounded corners


	1. Add a small 3D rounded corner to the cylinder using the AMCAX::MakeFillet class.

## 3. Mirror bending pipe

#### constructs the mirrored pipe3, pipe4, hex

	1. Use the AMCAX::TransformShape class to mirror the pipeline.

## 4. Boolean operation

#### puts all the pieces together through Boolean operations

	1. Perform a Boolean fusion operation using the AMCAX::BoolBRepFuse class to merge the two shapes into one.

	2. Boolean cuts an existing TopoShape object using the AMCAX::BoolBRepCut class.


# Meshing

## 1. Build a grid

	1. Use AMCAX::BRepMeshIncrementalMesh class for each generated grids in shape.

	2. Using AMCAX::MakeShapeTool::EnsureNormalConsistency () to check and adjust the shape of normal, to ensure the consistency of shape mesh normals.


## 2. Export as STL file

	1. Use AMCAX::STLTool::WriteShape class will topology graphics result generated a STL file called partSample.

<div align = center><img src="https://img2.imgtp.com/2024/05/11/GPTWfGiY.png" width="300" height="300">