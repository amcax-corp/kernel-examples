# 构建六棱柱

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

## 4. 应用 3D 倒角

#### 该示例实现3D倒角的六棱柱。具体实现如下：
	1. 使用 AMCAX::MakeChamfer 类为六棱柱应用 3D 倒角的效果。

	2. 使用 AMCAX::BRepMeshIncrementalMesh 类为形状中的每个面生成网格。

	3. 使用 AMCAX::MakeShapeTool::EnsureNormalConsistency() 来检查并调整形状的法线，以确保形状网格法线的一致性。

	4. 使用 AMCAX::STLTool::WriteShape 类将拓扑图形 hex 生成一个名为 part4 的 stl 文件。

<div align = center><img src="https://img2.imgtp.com/2024/05/10/R46nZjtD.png" width="300" height="300">

