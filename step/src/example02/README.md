# STEP File read and write example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example shows the basic usage of Mesh Reader. The details are as follows:

	1. Read the file using Read() under AMCAX::STEP::STEPMeshReader<TriSoupTraits>
	
	2. Obtain the STEPMeshProduct node using GetProducts() under AMCAX::STEP::STEPMeshReader<TriSoupTraits>
	
	3. Implement in-place transformation of the incoming shapes using ApplyTrsfInplace() under AMCAX::STEP::STEPTool
	
	4. Convert the TopoShape object to a Mesh object using ToMesh() under AMCAX::STEP::STEPMeshReader<TriSoupTraits>
	
	5. Call the func function to recursively traverse the child elements of each element and add the mesh information in meshdata to the meshes vector
	
	6. Declare an io_options object using AMCAX::Meshing::Mesh::IOOptions
	
	7. Declare points1 and result_points objects using AMCAX::Meshing::Mesh::TriSoupTraits_Coord::Points
	
	8. Declare triangles1 and result_triangles objects using AMCAX::Meshing::Mesh::TriSoupTraits_Coord::Triangles
	
	9. Declare an stl_writer object using AMCAX::Meshing::Mesh::STLWriter<AMCAX::Meshing::Mesh::TriSoupTraits_Coord>
	
	10. Declare a trianglestmp object using AMCAX::Meshing::Mesh::TriSoupTraits_Coord::Triangles
	
	11. Create a tritmp object for adjusting vertex indices
	
	12. Write the mesh to an STL file using write() under AMCAX::Meshing::Mesh::STLWriter<AMCAX::Meshing::Mesh::TriSoupTraits_Coord>


<div align = center><img src="https://s2.loli.net/2024/06/12/RjXdmbpAn7UKN1x.png" width="500" height="400">