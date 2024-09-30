# Build a hexagonal prism

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

## 4. Apply 3D chamfer

#### This example implements a 3D chamfered hexagonal prism. The specific implementation is as follows:

	1. Use the AMCAX::MakeChamfer class to apply the 3D chamfer effect to the hexagonal prism.

	2. Use AMCAX::BRepMeshIncrementalMesh class for each generated grids in shape.

	3. Using AMCAX::MakeShapeTool::EnsureNormalConsistency () to check and adjust the shape of normal, to ensure the consistency of shape mesh normals.

	4. Use AMCAX::STLTool::WriteShape class will topology graph generated a hex called part4 STL files.

<div align = center><img src="https://s2.loli.net/2024/09/30/eX5FPmIL81prNCY.png" width="300" height="300">