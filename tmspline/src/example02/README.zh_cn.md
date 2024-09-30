# T 网格样条建模示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例实现了拉伸中间的面形成一个峰。具体实现如下：


## 1. 命名空间

	1. using namespace AMCAX
	
	2. using namespace TMS

## 2. 构建底面

	1. 使用 TMSplineMakeRectangle 构建一个平面矩形
	
	2. 使用 TMSplineMakeRectangle 下的 BuildSpline 方法构建样条曲线

## 3. 拉伸面和变换

	1. 使用 TMSplineExtrude 定义了一个 TMSplineExtrude 类型的对象 extrude
	
	2. 使用 TMSplineExtrude 下的 ExtrudeFaces 对面进行挤压
	
	3. 使用 Transformation3 定义了一个 Transformation3 类型的对象 trsfMove
	
	4. 使用 TransformationT 下 SetTranslation 进行平移变换
	
	5. 使用 Transformation3 定义了一个新的 Transformation3 对象 trsfRot
	
	6. 使用 TransformationT 下 SetRotation 进行旋转变换

## 4. 网格化

	1. 使用 TMSplineMeshing 定义了一个 TMSplineMeshing 类型的对象 tspMesh
	
	2. 使用 TMSplineMeshing 下 UpdateDrawMesh 进行网格化


## 5. 保存网格

	1. 使用 TMSplineMeshingIO 定义了一个 TMSplineMeshingIO 类型的对象 meshIO
	
	2. 使用 TMSplineMeshing 下的 GetDrawMesh 得到网格化结果
	
	3. 使用 TMSplineMeshingIO 下的 ExportToOBJ 将网格化结果导出为 part2 的 OBJ 文件
	
<div align = center><img src="https://s2.loli.net/2024/09/30/xmbpUFt6VlMPEDY.png" width="300" height="300">
