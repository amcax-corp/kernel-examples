# Mesh Generation Example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This tutorial outlines the basic usage of mesh generation. It involves the process of importing STEP format files and automatic generation of the volumetric mesh, which is controlled by parameters specified by a JSON file. The implementation is as follows:

	1. Use InitLogger() under AMCAX::NextMesh::NMAPIModel to set the log format
	
	2. Use ImportModel() under AMCAX::NextMesh::NMAPIModel to import the cad file and create a new NMAPIModel object
	
	3. Use GenerateMesh() under AMCAX::NextMesh::NMAPIModel to mesh generation controlled by the parameters in the json
	
	4. Use GetMesh() under AMCAX::NextMesh::NMAPIModel to get the generated mesh
	
	5. Use GetEntities() under AMCAX::NextMesh::NMAPIModel to get all entities in the dimension-dim
	
	6. use GetEntityElementTypes() under AMCAX::NextMesh::NMMesh to Get all the element-types contained in the entity-ent
	
	7. use GetNodesByElementType() under AMCAX::NextMesh::NMMesh to get the sequence of nodes of the elements with cType type contained in the entity
	
	8. use GetParentAdjacentEntities() under AMCAX::NextMesh::NMAPIModel to get the entity sequence in dim+1 dimension containing the entity
	
	9. use GetChildAdjacentEntities() under AMCAX::NextMesh::NMAPIModel to get the entity sequence in dim-1 dimension containing the entity ent
	
	10. use GetBBox() under AMCAX::NextMesh::NMAPIModel to get the boundingbox for the whole model
	
	11. Use GetAllNodes() under AMCAX::NextMesh::NMMesh to get all mesh nodes
		
	12. use CreatePhysicalSet() under AMCAX::NextMesh::NMAPIModel to Set the face groups
	
	13. Use GetEntitiesInPhysicalSet() under AMCAX::NextMesh::NMAPIModel to get the entities in the specified mesh group
	
	14. Use GetPhysicalSets() under AMCAX::NextMesh::NMAPIModel to get all the sets of faces in the specified dimension
	
	15. Use Write() under AMCAX::NextMesh::NMMesh to export the mesh file


The generated mesh model is shown in the figure:

	1. JSON Example (corresponding import files are 1.stp and 1.json)

<div align = center><img src="https://s2.loli.net/2024/08/21/fgE13hGHXuNz29m.png" width="400" height="300"></div>

	2. JSON Example - Planar Boundary Layer (corresponding import files are 2.step and 2.json)

<div align = center><img src="https://s2.loli.net/2024/09/29/lamGrEMwyuhPvg8.png" width="300" height="250"></div>

	3. JSON Example - Spatial Boundary Layer (corresponding import files are 3.step and 3.json)

<div align = center><img src="https://s2.loli.net/2024/09/29/hc1jrQLRWPH6s8J.png" width="300" height="250"></div>