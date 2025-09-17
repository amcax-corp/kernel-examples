# Block-Structured Mesh Example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example provides the basic usage of block-structured meshes. First, import the geometric file for which a structured mesh needs to be generated, then initialize and edit mesh blocks based on the geometric model, and finally discretize the mesh to realize structured mesh generation based on the geometric model. The specific implementation steps are as follows:

	1. Configure the log format using InitLogger() under AMCAX::NextMesh::NMAPIModel
	
	2. Read the model from the file using Read() under AMCAX::OCCTIO::OCCTTool
	
	3. Import the TopoShape using ImportModel() under AMCAX::NextMesh::NMAPIModel
	
	4. Obtain all entities under the specified dimension using GetEntities() under AMCAX::NextMesh::NMAPIModel
	
	5. Get the mesh block handle using GetNMBlock() under AMCAX::NextMesh::NMAPIModel
	
	6. Perform O-type splitting on the specified hexahedral block using OSplit() under AMCAX::NextMesh::NMBlock
	
	7. Associate the mesh face with the geometric face using AssociateFace() under AMCAX::NextMesh::NMBlock
	
	8. Match the shape of the source edge to the optimal shape of the target edge using MatchEdgeToEdge() under AMCAX::NextMesh::NMBlock
	
	9. Set the edge distribution using SetEdgesDistribution() under AMCAX::NextMesh::NMBlock
	
	10. Discretize all blocks to generate a 3D mesh using SetEdgesDistribution() under AMCAX::NextMesh::NMBlock
	
	11. Smooth the 3D block mesh using SmoothBlocks() under AMCAX::NextMesh::NMBlock7

