# Geometric Cleaning and Repair Example Two

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example demonstrates the basic usage of geometric editing. A STEP file is imported, and geometric editing operations are performed on the model using the GeomE API to repair it. The specific steps are as follows:

	1. Use AMCAX::TopoExplorerTool::MapShapes() to get the detected edges.

	2. Use AMCAX::GeomE::DetectTool::GetEdgeType() to determine the type of the edge.

	3. Use AMCAX::GeomE::DetectTool::DetectFreeBoundaries() to detect the free boundaries associated with the edge.

	4. Use AMCAX::GeomE::FaceEditor::FillHole() to fill holes in the selected free boundary.

	5. Use AMCAX::TopoExplorerTool::MapShapes() to get the edge set.

	6. Use AMCAX::GeomE::FaceEditor::BuildCoons() to construct a Coons surface from the edge set.

	7. Use AMCAX::TopoExplorerTool::MapShapes() to get the edge set.

	8. Use AMCAX::GeomE::FaceEditor::BuildPlane() to construct a plane from the edge set.

	9. Use AMCAX::TopoExplorerTool::MapShapes() to get the edge set.

	10. Use AMCAX::TopoExplorerTool::MapShapes() to get the existing faces.

	11. Use AMCAX::GeomE::FaceEditor::BuildFaceFromSurface() to create a new face from the edge set based on the existing surface.

	12. Use AMCAX::MakeVertex::MakeVertex() to create a vertex.

	13. Use AMCAX::GeomE::FaceEditor::VerticesProjectFace() to project points onto a face.

	14. Use AMCAX::OCCTIO::OCCTTool::Write() to output the result.

The output result is as follows:

<div align = center><img src="https://s2.loli.net/2024/12/31/NnMQrTok6DCdPzZ.png" width="400" height="300"></div>