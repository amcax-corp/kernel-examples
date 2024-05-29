# AMCAXMeshing Grid algorithm example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example shows incremental re-meshing. The specific implementation is as follows:



	1. Create an obj_reader object using OBJReader<TriSoupTraits>

	2. Create an obj_writer object using OBJWriter<TriSoupTraits>

	3. Define an inc_remesher object using TriMesh_Incremental_Remeshing

	4. read OBJ files using read() under OBJReader<TriSoupTraits>

	5. Use setReferenceMesh() under TriMesh_Incremental_Remeshing to take the triangular grid as input

	6. Use setVariableMesh() under TriMesh_Incremental_Remeshing to take the triangular mesh as output

	7. Define a param object using TriMesh_Incremental_Remeshing::Params

	8. Use TriMesh_Incremental_Remeshing::Params to control the parameters of the heavy grid

	9. Re-meshing the grid using remesh() under TriMesh_Incremental_Remeshing

	10. write the mesh to the obj file using write() under OBJWriter<TriSoupTraits>



<div align = center><img src="https://img2.imgtp.com/2024/05/27/np3W9m2j.png" width="300" height="300">