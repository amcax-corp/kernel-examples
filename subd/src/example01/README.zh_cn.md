# 多边形网格细分建模示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例实现了构建一个平面矩形。具体实现如下：


## 1. 命名空间

	1. using namespace AMCAX
	
	2. using namespace SubD

## 2. 构建底面

	1. 使用 MeshMakeRectangle 类构建一个平面矩形。

## 3. 执行细分

	1. 使用 MeshSubdivideHE::CatmullClark 细分网格


## 4. 保存网格

	1. 使用 PolyMeshIO::WriteMesh 将网格写入 example1 文件
	
<div align = center><img src="https://s2.loli.net/2024/09/30/KVaLAUYFdOE6sDx.png" width="300" height="300">
