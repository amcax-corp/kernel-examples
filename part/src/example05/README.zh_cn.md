# 构建弯曲管道

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

#### 该示例实现构建弯曲轨道pipe1。具体实现如下：
## 1. 构建扫掠路径

	1. 使用 AMCAX::MakeGeom2Circle 类创建 2D 圆。

	2. 使用 AMCAX::GccLine2Tangent 类构建与 2D 圆相切的直线。

	3. 使用 AMCAX::GeometryTool::To3d 类将 2D 曲线转换为 3D 曲线。

	4. 使用 AMCAX::MakeArcOfCircle 类创建圆弧。

	5. 使用 AMCAX::MakeSegment 类创建线段。
	
	6. 使用 AMCAX::MakeEdge 类实现从曲线创建边。
	
	7. 使用 AMCAX::MakeWire 类实现从边创建路径。

## 2. 创建轮廓线

	1. 使用 AMCAX::MakeGeom3Circle 类创建出轮廓线。


## 3. 创建 2D 偏移线

	1. 使用 AMCAX::CopyShape 类复制上一步形成的轮廓线。

	2. 使用 AMCAX::MakeOffset 类创建 2D 偏移曲线。

## 4. 创建扫掠面

	1. 使用 AMCAX::MakeFace 类生成面，将其作为轮廓形状。

	2. 使用 AMCAX::MakePipe 类构造扫描实体。

## 5. 网格化

	1. 使用 AMCAX::MakeShapeTool::EnsureNormalConsistency() 来检查并调整形状的法线，以确保形状网格法线的一致性。

	2. 使用 AMCAX::STLTool::WriteShape 类将拓扑图形 pipe1 生成一个名为 part5 的 stl 文件。

<div align = center><img src="https://s2.loli.net/2024/09/30/vprfRF7euVBSDxN.png" width="300" height="300">

