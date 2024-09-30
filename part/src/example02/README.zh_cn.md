# 构建六棱柱

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

## 2. 应用2D圆角

#### 该示例实现构造出一个圆角六边形。具体实现如下：

	1. 使用AMCAX::MakeFillet2d 类将 2D 圆角应用于六边形的每个顶点，构造出一个圆角六边形。

	2. 使用AMCAX::BRepMeshIncrementalMesh 类为形状中的每个面生成网格。

	3. 使用AMCAX::MakeShapeTool::EnsureNormalConsistency() 来检查并调整形状的法线，以确保形状网格法线的一致性。

	4. 使用AMCAX::STLTool::WriteShape类将拓扑图形 face2 生成一个名为 part2 的 stl 文件。
	
<div align = center><img src="https://s2.loli.net/2024/09/30/eQE9rNm4WMJFAPi.png" width="300" height="300">




