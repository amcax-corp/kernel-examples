# 实体建模示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例使用简化的阀门模型来展示 AMCAX 内核中的一些主要建模功能。具体实现如下：

## 1. 创建多边形

#### 创建一个六边形
	1. 使用 AMCAX::MakePolygon 类创建一个六边形。

	2. 使用 AMCAX::MakeFace 类构造出一个面。

## 2. 应用2D圆角

#### 构造一个圆角六边形

	1. 使用AMCAX::MakeFillet2d 类将 2D 圆角应用于六边形的每个顶点，构造出一个圆角六边形。

	2. 使用AMCAX::BRepMeshIncrementalMesh 类为形状中的每个面生成网格。
	
## 3. 拉伸柱体

#### 创建出一个六棱柱
	1.	使用 AMCAX::MakePrism 类拉伸圆角六边形以创建一个六棱柱。

	2.	使用 AMCAX::BRepMeshIncrementalMesh 类为形状中的每个面生成网格。

## 4. 应用 3D 倒角

#### 构造一个 3D 倒角的六棱柱

	1. 使用 AMCAX::MakeChamfer 类为六棱柱应用 3D 倒角的效果。

	2. 使用 AMCAX::BRepMeshIncrementalMesh 类为形状中的每个面生成网格。

# 构建弯曲管道

#### 构造两个弯曲管道，即 pipe1 和 pipe2 
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

# 构建阀门

## 1. 创建圆柱体

#### 构造一个圆柱体 

	1. 使用 AMCAX::MakeCylinder 类创建一个圆柱体。


## 2. 应用 3D 圆角

#### 构造一个 3D 圆角的圆柱体 


	1. 使用 AMCAX::MakeFillet 类向圆柱体添加了一个小的 3D 圆角。

## 3. 镜像弯曲管道

#### 构造出镜像后的 pipe3 ，pipe4 ，hex

	1. 使用 AMCAX::TransformShape 类来镜像管道。

## 4. 布尔运算

#### 将所有部分通过布尔运算组合在一起

	1. 使用 AMCAX::BoolBRepFuse 类执行布尔融合操作，将两个形状合并成一个。
	
	2. 使用 AMCAX::BoolBRepCut 类对一个已有的 TopoShape 对象进行布尔切割操作。


# 网格化

## 1. 构建网格

	1. 使用 AMCAX::BRepMeshIncrementalMesh 类为形状中的每个面生成网格。

	2. 使用 AMCAX::MakeShapeTool::EnsureNormalConsistency() 来检查并调整形状的法线，以确保形状网格法线的一致性。


## 2. 导出为 STL 文件

	1. 使用 AMCAX::STLTool::WriteShape 类将拓扑图形 result 生成一个名为 partSample 的 stl 文件。

<div align = center><img src="https://img2.imgtp.com/2024/05/11/GPTWfGiY.png" width="300" height="300">



