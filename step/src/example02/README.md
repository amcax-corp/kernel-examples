# STEP File read and write example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example shows the basic usage of Mesh Reader. The details are as follows:

	1. Use using AMCAX::STEP::StepMeshReader < AMCAX:: Meshing::Mesh::TriSoupTraits_Coord > create objects reader
	
	2. Use using AMCAX::STEP::StepMeshReader < AMCAX::Meshing::Mesh::TriSoupTraits_Coord > under the Read () Read the STEP file
	
	3. Use using AMCAX::STEP::StepMeshReader < AMCAX::Meshing::Mesh::TriSoupTraits_Coord > GetShapes under () to obtain a list of StepMeshData tree pointer
	
	4. Call the function _ApplyTrsfInplace, which transforms the incoming shape in place and stores the result in trsfStack
	
	5. Use using AMCAX::STEP::StepMeshReader < AMCAX::Meshing::Mesh::TriSoupTraits_Coord > ToMesh under () converts TopoShape object to a Mesh object
	
	6. Call the func function, recursively iterate through the child elements of each element, and add the grid information from StepMeshData to the outermost meshes vector
	
	7. Use AMCAX::Meshing::Mesh::IOOptions declare a io_options object
	
	8. Use Points to specify points1 and result_points
	
	9. Use Triangles to declare the triangles1, result_triangles object
	
	10. Use AMCAX::Meshing::Mesh::STLWriter < AMCAX::Meshing::Mesh::TriSoupTraits_Coord > statement a stl_writer object
	
	11. Declare a trianglestmp object using Triangles
	
	12. A triangle object, tritmp, is created to adjust the index of the vertices
	
	13. Use AMCAX::Meshing::Mesh::STLWriter < AMCAX::Meshing::Mesh::TriSoupTraits_Coord > under the write () to write grid into the STL file


<div align = center><img src="https://s2.loli.net/2024/06/12/RjXdmbpAn7UKN1x.png" width="500" height="400">