# Composite Face Example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example demonstrates how to create composite faces. The specific implementation steps are as follows:

	1. Configure the log format using InitLogger() under AMCAX::NextMesh::NMAPIModel
	
	2. Read the model from the file using Read() under AMCAX::OCCTIO::OCCTTool
	
	3. Import the TopoShape using ImportModel() under AMCAX::NextMesh::NMAPIModel
	
	4. Obtain all entities under the specified dimension using GetEntity() under AMCAX::NextMesh::NMAPIModel
	
	5. Generate composite faces using AddCompositeEntity() under AMCAX::NextMesh::NMAPIModel
	
	6.Generate a mesh based on the JSON string (mesh generation control parameters) using GenerateMesh() under AMCAX::NextMesh::NMAPIModel
	
	7. Get the mesh handle using GetMesh() under AMCAX::NextMesh::NMAPIModel
	
	8.Output the mesh file using Write() under AMCAX::NextMesh::NMMesh

<div align = center><img src="https://s2.loli.net/2025/09/10/3tRHbrqCiyZMOUQ.png" width="400" height="300"></div>