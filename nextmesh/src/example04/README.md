# Mesh Quality Example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example demonstrates how to calculate mesh quality. The specific implementation steps are as follows:

	1. Configure the log format using InitLogger() from AMCAX::NextMesh::NMAPIModel.

	2. Import a TopoShape using ImportModel() from AMCAX::NextMesh::NMAPIModel.

	3. Retrieve all entities of a specified dimension using GetEntities() from AMCAX::NextMesh::NMAPIModel.

	4. Generate a mesh using GenerateMesh() from AMCAX::NextMesh::NMAPIModel with JSON-formatted mesh generation control parameters.

	5. Obtain the number of elements in an entity using EntityGetElementCount() from AMCAX::NextMesh::NMMesh.

	6. Retrieve a specific element by its index within an entity using EntityGetElementByIndex() from AMCAX::NextMesh::NMMesh.

	7. Determine the element type using ElementGetType() from AMCAX::NextMesh::NMMesh.

	8. Calculate mesh quality using ComputeQuality() from AMCAX::NextMesh::NMMesh.