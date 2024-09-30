# AMCAXMeshing Mesh Algorithm Example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example demonstrates incremental remeshing. The specific implementation is as follows:

	
	1. use OBJReader<TriSoupTraits> to create an obj_reader object
	
	2. use read() under OBJReader<TriSoupTraits> to read the OBJ file
	
	3. use TriMesh_IncrementalRemeshing<TriSoupTraits> to create a remesher object
	
	4. create a params object with TriMesh_IncrementalRemeshing<TriSoupTraits>::Params
	
	5. use setReferenceMesh() under TriMesh_IncrementalRemeshing<TriSoupTraits> to add a triangle mesh as an input
	
	6. use setVariableMesh() under TriMesh_IncrementalRemeshing<TriSoupTraits> to set the triangle mesh as the output target

	7. use remesh() under TriMesh_IncrementalRemeshing<TriSoupTraits> to isotropically remeshing the input mesh

	8. use OBJWriter<TriSoupTraits> to create a writer object
	
	9. Use write() under OBJWriter<TriSoupTraits> to write the mesh to the obj file
	
	

<div align = center><img src="https://s2.loli.net/2024/09/29/NoZXSl68EBn45Ac.png" width="500" height="300">

