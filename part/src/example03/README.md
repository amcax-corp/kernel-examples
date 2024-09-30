# Build a hexagonal prism

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

## 3. Stretch the column

#### The example implementation creates a hexagonal prism. The specific implementation is as follows:

	1. Use the AMCAX::MakePrism class to stretch the rounded hexagon to create a hexagonal prism.

	2. Use AMCAX::BRepMeshIncrementalMesh class for each generated grids in shape.

	3. Using AMCAX::MakeShapeTool::EnsureNormalConsistency () to check and adjust the shape of normal, to ensure the consistency of shape mesh normals.

	4. Use AMCAX::STLTool::WriteShape class will topology graphics hexagonPrism generated a STL file called part3.


<div align = center><img src="https://s2.loli.net/2024/09/30/mDi7B3Qct8ukvAG.png" width="300" height="300">