# Build a hexagonal prism

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

## 1. Create polygons

### The example implementation creates a hexagon. The specific implementation is as follows:
	1. Create a hexagon using the AMCAX::MakePolygon class.

	2. Construct a face using the AMCAX::MakeFace class.

	3. Use AMCAX::BRepMeshIncrementalMesh class for each generated grids in shape.

	4. Using AMCAX::MakeShapeTool::EnsureNormalConsistency () to check and adjust the shape of normal, to ensure the consistency of shape mesh normals.

	5. Use AMCAX: : STLTool::WriteShape class will topological surface f generated a STL file called part1.

<div align = center><img src="https://s2.loli.net/2024/09/30/gWVwEbHC6D8uOXk.png" width="300" height="300">