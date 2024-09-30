# Polygonal mesh subdivision modeling example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example implements building a flat rectangle. The specific implementation is as follows:


## 1. Namespace

	1. using namespace AMCAX

	2. using namespace SubD

## 2. Build the underside

	1. Use the MeshMakeRectangle class to construct a flat rectangle.

## 3. Perform segmentation

	1. Use MeshSubdivideHE::CatmullClark subdivision mesh


## 4. Save grid

	1. Write the grid to the example1 file using PolyMeshIO::WriteMesh

<div align = center><img src="https://img2.imgtp.com/2024/05/15/5nSPEYem.png" width="300" height="300">