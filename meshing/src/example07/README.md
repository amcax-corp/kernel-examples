# Mesh parameterisation algorithm

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example shows the basic usage of the grid parameterisation algorithm. The details are as follows:

	1. create obj_reader and obj_writer objects for reading and writing OBJ files.
	
	2. use read() under OBJReader to read OBJ files and store the read data in io_options.
	
	3. use AMCAX::Meshing::Parameterisation::BijectivePara<TriSoupTraits_Coord> to create object para
	
	4. use parameterization() under AMCAX::Meshing::Parameterization::BijectivePara<TriSoupTraits_Coord> to parameterise the mesh
	
	5. use write() under OBJWriter to write the parameterised mesh to an OBJ file

Parameterisation result:

<div align = center><img src="https://s2.loli.net/2024/07/30/mjFYrbToCVD6BLc.png" width="500" height="400">




