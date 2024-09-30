# AMCAXMeshing Grid algorithm example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example shows the grid Boolean algorithm. The specific implementation is as follows:



	1. Declare a function called read_mesh that reads the triangular mesh file

	2. Create a reader object using OBJReader

	3. Declare a function called write_mesh that writes triangular mesh data to a file

	4. Create a writer object using OBJWriter

	5. Define a function called MeshBoolean_MeshBoolean

	6. Use read_mesh function to read grid data from obj file and store these data in variables points1, triangles1 and points2, triangles2 respectively

	7. Create a MeshBoolean object called boolean

	8. Use addTriMeshAsInput() under MeshBoolean to read the two triangular grid data as input

	9. Use setTriMeshAsOutput() under MeshBoolean to specify the variables used to store the points and triangles of the result

	10. Use Union() under MeshBoolean to compute the union of two input grids

	11. Use Intersection() under MeshBoolean to compute the intersection of two input grids

	12. Use the Xor() of MeshBoolean to calculate the XOR of the two input grids

	13. Use Subtraction() under MeshBoolean to calculate the difference between the two input grids

	14. Write the mesh to the obj file using the write_mesh function


#### The following are the results of union, intersection, exclusior, and difference in order

<div align = center><img src="https://img2.imgtp.com/2024/05/23/4E13p88B.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/23/gTaNhveA.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/23/3CtPRSIZ.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/23/ePr23VTQ.png" width="300" height="300">