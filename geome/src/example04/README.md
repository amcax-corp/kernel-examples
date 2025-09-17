# Helicopter Model Repair and Enhancement Example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

#### This example demonstrates the basic usage of geometric editing to repair a helicopter model. The specific implementation is as follows:

	Face Fusion:
	
	1. Use AMCAX::TopoExplorerTool::MapShapes() to obtain model faces and edges
	
	2. Use AMCAX::GeomE::FaceEditor::DeleteFace() to delete faces
	
	3. Use AMCAX::GeomE::FaceEditor::BuildFaceFromSurface() to construct new faces
	
	4. Use AMCAX::ShapeFixTool::UpgradeUnifySameDomain() to merge faces and edges
	
	Sew Edge:
	
	1. Use AMCAX::TopoExplorerTool::MapShapes() to obtain model edges
	
	2. Use AMCAX::GeomE::DetectTool::DetectFreeEdges() to detect free edges
	
	3. Use AMCAX::GeomE::EdgeEditor::SewEdges() to stitch two edges together
	
	Hole Patching:
	
	1. Use AMCAX::TopoExplorerTool::MapShapes() to obtain model faces and edges
	
	2. Use AMCAX::GeomE::FaceEditor::BuildFaceFromSurface() to construct new faces
	
	3. Use AMCAX::ShapeFixTool::UpgradeUnifySameDomain() to merge faces and edges
