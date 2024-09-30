# AMCAXMeshing Grid algorithm example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example shows the mesh ButterFly subdivision algorithm. The specific implementation is as follows:



	1. Create an obj_reader object using OBJReader<TriSoupTraits_Coord>

	2. Create an obj_writer object using the OBJWriter<TriSoupTraits_Coord> command

	3. Define a subdivider object using TriSoup_ButterFlySubdivision<TriSoupTraits_Coord, true>

	4. Use elapse_reset() in Logger to reset the running time

	5. Perform ButterFly segmentation using subdivide() under TriSoup_ButterFlySubdivision<TriSoupTraits_Coord, true>

	6. Define a fast_qem object using FastQEM<TriSoupTraits_Coord>

	7. simplify the grid using simplify() under FastQEM<TriSoupTraits_Coord>

	8. Use the elapsed() method under Logger to return the time elapsed since the last reset.

	9. write the grid to the obj file using write() under OBJWriter<TriSoupTraits_Coord>


#### The following breakdown ratios are 2., 3., 4., 5., 6., 7., 8., 9., 10.,11.,12.

<div align = center><img src="https://s2.loli.net/2024/09/30/CcaHTJVseXpR8Fn.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/TYvaDsWzdt1Pucg.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/2yozFLe3CGUQjPp.png" width="300" height="300"> 

<div align = center><img src="https://s2.loli.net/2024/09/30/DLXAoglqOM4IcxU.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/SipcMB6uPQJxf7j.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/JveO3oWPClpUnYs.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/MOFhW95x6ALiXG2.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/4jTsB9C683QbdhD.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/51ladnWL2KwANuS.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/CsfIHeOzkWhEK9d.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/r9lHUBDWqaQOc6F.png" width="300" height="300">