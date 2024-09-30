# 多边形网格细分建模示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例实现将顶面删除。具体实现如下：


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
	
	5. 使用 TransformationT 下 SetRotation 方法进行旋转变换

## 4. 删除顶面

	1. 使用 MeshReduce::DeleteFaces 删除顶面

## 5. 执行细分

	1. 使用 MeshSubdivideHE::CatmullClark 细分网格


## 6. 保存网格

	1. 使用 PolyMeshIO::WriteMesh 将网格写入 example3 文件

<div align = center><img src="https://s2.loli.net/2024/09/30/m91InhVoRZ7zqET.png" width="300" height="300">

