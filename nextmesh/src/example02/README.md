# 2D Boundary Layer Detailed JSON Example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example demonstrates the detailed configuration method for a 2D boundary layer using mesh partitioning. It imports BREP format files, passes mesh partitioning control parameters through a JSON file, and automatically generates the mesh. The specific implementation is as follows:

	1. Use AMCAX::NextMesh::NMAPIModel::InitLogger() to configure the log format.
	
	2. Use AMCAX::NextMesh::NMAPIModel::ImportModel() to import TopoShape.
	
	3. Use AMCAX::NextMesh::NMAPIModel::GenerateMesh() to generate a mesh based on the JSON string (mesh generation control parameters).
	
	4. Use AMCAX::NextMesh::NMAPIModel::GetMesh() to obtain the generated mesh API.
	
	5. Use AMCAX::NextMesh::NMAPIModel::CreatePhysicalSet() to define a set of faces.
	
	6. Use AMCAX::NextMesh::NMAPIModel::GetEntitiesInPhysicalSet() to retrieve the entities within a specified physical set.
	
	7. Use AMCAX::NextMesh::NMAPIModel::GetPhysicalSets() to retrieve all physical sets in the specified dimension.
	
	8. Use AMCAX::NextMesh::NMMesh::Write() to output the mesh file.


The generated mesh model is shown in the figure:

<div align = center><img src="https://s2.loli.net/2025/02/26/mbN37X8CuGHwSDz.png" width="400" height="300"></div>