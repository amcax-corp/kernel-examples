# AMCAXMeshing Grid algorithm example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example shows the mesh repair algorithm. The specific implementation is as follows:



	1. Define an algorithm progress callback function named pro_fn using FastQEM<TriSoupTraits_Coord>::ProFn

	2. Create an obj_reader object using OBJReader<TriSoupTraits_Coord>

	3. Use STLReader<TriSoupTraits_Coord> to create an stl_reader object

	4. Create an obj_writer object using OBJWriter<TriSoupTraits_Coord>

	5. Use the STLWriter<TriSoupTraits_Coord> command to create an stl_writer object

	6. read the stl file using read() under STLReader<TriSoupTraits_Coord>

	7. Use repair() under TriMeshRepair<TriSoupTraits_Coord> to repair the grid

	8. write the grid to the stl file using write() under STLWriter<TriSoupTraits_Coord>

	9. write the grid to the obj file using write() under OBJWriter<TriSoupTraits_Coord>



<div align = center><img src="https://s2.loli.net/2024/09/30/Rad3QoCSHWlgNFD.png" width="300" height="300">