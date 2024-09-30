# 构建阀门

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

## 2. 应用 3D 圆角

#### 该示例实现创建一个 3D 圆角的圆柱体。具体实现如下：
	1. 使用 AMCAX::MakeFillet 类向圆柱体添加了一个小的 3D 圆角。

	2. 使用 AMCAX::BRepMeshIncrementalMesh 类为形状中的每个面生成网格。

	3. 使用 AMCAX::MakeShapeTool::EnsureNormalConsistency() 来检查并调整形状的法线，以确保形状网格法线的一致性。

	4. 使用 AMCAX::STLTool::WriteShape 类将拓扑图形 middleCylinder 生成一个名为 part8 的 stl 文件。

<div align = center><img src="https://s2.loli.net/2024/09/30/y1bkn2rdAZt6YRe.png" width="300" height="300">

