# AMCAXMeshing Grid algorithm example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example shows the mesh Loop subdivision algorithm. The specific implementation is as follows:



	1. Create an obj_reader object using OBJReader<TriSoupTraits_Coord>

	2. Create an obj_writer object using the OBJWriter<TriSoupTraits_Coord> command

	3. Define a subdivider object using TriSoup_LoopSubdivision<TriSoupTraits_Coord>

	4. Use elapse_reset() in Logger to reset the running time

	5. Perform Loop segmentation using subdivide() in TriSoup_LoopSubdivision<TriSoupTraits_Coord>

	6. Define a fast_qem object using FastQEM<TriSoupTraits_Coord>

	7. simplify the grid using simplify() under FastQEM<TriSoupTraits_Coord>

	8. Use the elapsed() method under Logger to return the time elapsed since the last reset.

	9. write the grid to the obj file using write() under OBJWriter<TriSoupTraits_Coord>


#### The following breakdown ratios are 2., 3., 4., 5., 6., 7., 8., 9., 10.,11.,12.

<div align = center><img src="https://img2.imgtp.com/2024/05/24/XQDqp4dn.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/24/0FbNLzRI.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/24/LN0vY84K.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/24/ZyqNwaXl.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/24/LYgwOcbV.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/24/qGZN2N2q.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/24/ujQU8ImO.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/24/beFHjEyM.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/24/ms792y5v.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/24/CqBh4YDl.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/24/JEaNI89K.png" width="300" height="300">