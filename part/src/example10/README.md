# Build valve

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

## 3. Mirror bending pipe

#### This example constructs pipe4 by mirroring the curved pipe pipe2. The specific implementation is as follows:
	1. Use the AMCAX::TransformShape class to mirror the pipe.

	2. Use AMCAX::BRepMeshIncrementalMesh class for each generated grids in shape.

	3. Using AMCAX::MakeShapeTool::EnsureNormalConsistency () to check and adjust the shape of normal, to ensure the consistency of shape mesh normals.

	4. Use AMCAX::STLTool::WriteShape class will topology graphics pipe4 generated a STL file caslled part10.

<div align = center><img src="https://img2.imgtp.com/2024/05/10/72WpaRMZ.png" width="300" height="300">