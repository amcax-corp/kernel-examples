# Fluid Mesh Generation Example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example provides the basic method for using fluid mesh generation, with the specific implementation steps as follows:

	1. Use Read() under AMCAX::STEP::STEPTool to read the STEP file
	
	2. Use InitLogger() under AMCAX::NextMesh::NMAPIModel to configure the log format
	
	3. Use ImportModel() under AMCAX::NextMesh::NMAPIModel to import the model
	
	4. Use GenerateMesh() under AMCAX::NextMesh::NMAPIModel to generate the mesh based on the JSON string (mesh generation control parameters)
	
	5. Use GetMesh() under AMCAX::NextMesh::NMAPIModel to obtain the mesh handle
	
	6. Use Write() under AMCAX::NextMesh::NMMesh to output the mesh file

