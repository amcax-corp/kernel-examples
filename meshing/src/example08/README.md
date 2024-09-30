# Mesh Cutting Algorithm

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example shows the basic usage of the grid cutting algorithm. The details are as follows:

	1. create obj_reader and obj_writer objects for reading and writing OBJ files.
	
	2. define the path of the input file in_filename
	
	3. define the paths out_cut_filename and out_para_filename for the output file, which represent the paths of the cut mesh file and the parameterised mesh file respectively.
	
	4. use read() under OBJReader to read the OBJ file and store the read data in io_options.
	
	5. use AMCAX::Meshing::TriMeshCut::GreedyCut<TriSoupTraits_Coord> to create the object mesh_cut, passing in i_points and i_triangles
	
	6. use cut() under AMCAX::Meshing::TriMeshCut::GreedyCut<TriSoupTraits> to cut the mesh, the cut vertices and triangles are stored in cut_points and cut_triangles.
	
	7. use write() under OBJWriter to write the cut mesh to an OBJ file.
	
	8. use clear() under OBJWriter to clear the data
	
	9. use AMCAX::Meshing::Parameterization::BijectivePara<TriSoupTraits_Coord> to create the object para, passing in the cut vertex and triangle data, and an empty para_points container
	
	10. use parameterization() under AMCAX::Meshing::Parameterization::BijectivePara<TriSoupTraits_Coord> to perform the parameterisation.
	
	11. use write() under OBJWriter to write the parameterised mesh to an OBJ file.

The cut and parameterised results are as follows (Note: The results are not the same after each execution of the cut.)

<div align = center><img src="https://s2.loli.net/2024/07/30/phWa9Itz4QyFmL3.png" width="500" height="400">


<div align = center><img src="https://s2.loli.net/2024/07/30/hKe5auQdSDpYrRC.png" width="500" height="400">

