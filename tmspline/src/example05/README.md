# T Grid spline modeling example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### The example implementation thickens the shape to create an entity. The specific implementation is as follows:


## 1. Namespace

	1. using namespace AMCAX

	2. using namespace TMS

## 2. Build the underside

	1. Construct a flat rectangle using TMSplineMakeRectangle

	2. Use the BuildSpline method under TMSplineMakeRectangle to build the spline curve

## 3. Stretch surface and transform

	1. Use TMSplineExtrude to define a TMSplineExtrude type object extrude

	2. Use ExtrudeFaces under TMSplineExtrude to squeeze from the opposite side

	3. Define an object of type Transformation3, trsfMove, using Transformation3

	4. Use SetTranslation under TransformationT for translation transformation

	5. Define a new Transformation3 object, trsfRot, using Transformation3

	6. Rotate using SetRotation under TransformationT

## 4. Remove the top surface

	1. Use TMSplineReduce to define a TMSplineReduce object reduce

	2. Use DeleteFaces in TMSplineReduce to delete the top surface

## 5. Stretch edges and transform

	1. Use TMSplineCheck::IsEdgeBoundary to determine whether edge boundary edge

	2. Use TMSplineTool::EdgeVertexIndexs get vertex index
	
	3. Using TMSplineTool::ControlPosition get a vertex position

	4. Stretch the edges using ExtrudeEdges

	5. Define an object of type Transformation3, trsfScale, using Transformation3

	6. Use SetScale under TransformationT to scale

## 6. Perform the thickening operation

	1. Use TMSplineThicken to define an object mkThick of type TMSplineThicken

	2. Use ThickenTMSpline under TMSplineThicken to thicken the shape

## 7. Grid

	1. Use TMSplineMeshing to define a TMSplineMeshing object tspMesh

	2. Use the UpdateDrawMesh in TMSplineMeshing for meshing


## 8. Save the grid

	1. Use TMSplineMeshingIO to define an object meshIO of TMSplineMeshingIO type

	2. Use GetDrawMesh under TMSplineMeshing to get meshing results

	3. Use ExportToOBJ under TMSplineMeshingIO to export the meshing results as part5 OBJ file

<div align = center><img src="https://s2.loli.net/2024/09/30/zPfUN6bl7r4aqXY.png" width="300" height="300">