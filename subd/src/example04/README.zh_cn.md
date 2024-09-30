# 多边形网格细分建模示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例实现将删除面留下的边向四周拉伸从而生成新的顶面，先执行拉伸操作，然后施加缩放变换将新生成的边移动到指定位置。具体实现如下：


## 1. 命名空间


	1. using namespace AMCAX
	
	2. using namespace SubD

## 2. 构建底面

#### 构建出一个平面
	1. 使用 MeshMakeRectangle 构建一个平面矩形

## 3. 拉伸面和变换

#### 拉伸中间的面形成一个峰

	1. 使用 MeshExtrude::ExtrudeFace 在平面矩形中进行挤压边缘
	
	2. 使用 Transformation3 定义了一个 Transformation3 类型的对象trsfMove
	
	3. 使用 TransformationT 下 SetTranslation 方法进行平移变换
	
	4. 使用 Transformation3 定义了一个新的 Transformation3 对象trsfRot
	
	5. 使用 TransformationT 中 SetRotation 方法进行旋转变换

## 4. 删除顶面

	1. 使用 MeshReduce::DeleteFaces 删除顶面

## 5. 拉伸边和变换

	1. 使用 MeshCheck::IsEdgeBoundary 检查当前边是否是边界边
	
	2. 使用 MeshTool::EdgeVertexIndexs 获取边界边两个顶点的索引
	
	3. 使用 MeshExtrude::ExtrudeEdge 拉伸边界边
	
	4. 使用 MeshTransform 定义一个 MeshTransform 对象 trsfE
	
	5. 使用 Transformation3 定义一个 Transformation3 对象 trsfScale
	
	6. 使用 TransformationT 下 SetScale 方法进行缩放变换

## 6. 执行细分

	1. 使用 MeshSubdivideHE::CatmullClark 细分网格


## 7. 保存网格

	1. 使用 PolyMeshIO::WriteMesh 将网格写入 example4 文件

<div align = center><img src="https://s2.loli.net/2024/09/30/gFRAHo2IXYnaVBv.png" width="300" height="300">

