# Polygonal mesh subdivision modeling example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### The sample implementation stretches the edge left by the deleted surface around to generate a new top surface, performing the stretching operation first, and then applying a scaling transform to move the newly generated edge to the specified position. The specific implementation is as follows:


## 1. Namespace


	1. using namespace AMCAX

	2. using namespace SubD

## 2. Build the underside

#### to construct a plane
	1. Use the MeshMakeRectangle to construct a flat rectangle

## 3. Stretch surface and transform

#### stretch the middle face to form a peak

	1. Use MeshExtrude::ExtrudeFace to extrude the edges in a flat rectangle

	2. Define an object of type Transformation3, trsfMove, using Transformation3

	3. Use SetTranslation method under TransformationT for translation transformation

	4. Define a new Transformation3 object, trsfRot, using Transformation3

	5. Perform rotation transformation using the SetRotation method in TransformationT

## 4. Remove the top surface

	1. Run MeshReduce::DeleteFaces to delete the top surface

## 5. Stretch edges and transform

	1. Use MeshCheck::IsEdgeBoundary check whether the current edge is boundary edge 

	2. Use MeshTool::EdgeVertexIndexs obtain boundary edge two vertices in the index

	3. Stretch the border edge using MeshExtrude::ExtrudeEdge

	4. Define a MeshTransform object trsfE using MeshTransform

	5. Define a Transformation3 object trsfScale using Transformation3

	6. Use SetScale method under TransformationT for scaling transformation

## 6. Perform segmentation

	1. Use MeshSubdivideHE::CatmullClark subdivision mesh


## 7. Save grid

	1. Write the grid to the example4 file using PolyMeshIO::WriteMesh

<div align = center><img src="https://img2.imgtp.com/2024/05/28/p8kLp6hO.png" width="300" height="300">