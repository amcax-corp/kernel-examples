# T 网格样条建模示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例实现了构建一个平面矩形。具体实现如下：


## 1. 命名空间

	1. using namespace AMCAX
	
	2. using namespace TMS

## 2. 构建底面

	1. 使用 TMSplineMakeRectangle 构建一个平面矩形
	
	2. 使用 TMSplineMakeRectangle 下的 BuildSpline 方法构建样条曲线

## 3. 执行细分

	1. 使用 TMSplineSplit 定义一个 TMSplineSplit 类型的对象split
	
	2. 使用 TMSplineSplit 下 SplitFacesCross 对 T 网络样条进行 1-4 分割法分割面


## 4. 网格化

	1. 使用 TMSplineMeshing 定义了一个 TMSplineMeshing 类型的对象 tspMesh
	
	2. 使用 TMSplineMeshing 下 UpdateDrawMesh 进行网格化


## 4. 保存网格

	1. 使用 TMSplineMeshingIO 定义了一个 TMSplineMeshingIO 类型的对象 meshIO
	
	2. 使用 TMSplineMeshing 下的 GetDrawMesh 得到网格化结果
	
	3. 使用 TMSplineMeshingIO 下的 ExportToOBJ 将网格化结果导出为 part1 的 OBJ 文件
	
<div align = center><img src="https://img2.imgtp.com/2024/05/16/ZXC6Wu4i.png" width="300" height="300">
