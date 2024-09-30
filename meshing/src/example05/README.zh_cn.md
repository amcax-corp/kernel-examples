# AMCAXMeshing 网格算法示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示了网格 Loop 细分算法。具体实现如下：


	
	1. 使用 OBJReader<TriSoupTraits_Coord> 创建一个 obj_reader 对象
	
	2. 使用 OBJWriter<TriSoupTraits_Coord> 创建一个 obj_writer 对象
	
	3. 使用 TriSoup_LoopSubdivision<TriSoupTraits_Coord> 定义一个 subdivider 对象
	
	4. 使用 Logger 下的 elapse_reset() 重置运行时间
	
	5. 使用 TriSoup_LoopSubdivision<TriSoupTraits_Coord> 下的 subdivide() 执行 Loop 细分
	
	6. 使用 FastQEM<TriSoupTraits_Coord> 定义一个 fast_qem 对象
	
	7. 使用 FastQEM<TriSoupTraits_Coord> 下的 simplify() 简化网格
	
	8. 使用 Logger 下的 elapsed() 返回自上次重置以来经过的时间
	
	9. 使用 OBJWriter<TriSoupTraits_Coord> 下的 write() 将网格写入 obj 文件


#### 以下细分比率依次为 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12.

<div align = center><img src="https://s2.loli.net/2024/09/30/MO6NjnyZku4DeVi.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/IGeL9o7HV4hcjZN.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/BClnpKzerUSVaNP.png" width="300" height="300"> 

<div align = center><img src="https://s2.loli.net/2024/09/30/U48eZHNTWXMRx5D.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/rXqoBG6hRA9wi1L.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/BatJu2IRNSEOKXl.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/rMnzeJbu8vlNUdi.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/7uNLnP5FYy4pbQj.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/d7DxaRn869MpSAO.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/Uk4qie5ZyAzN6VM.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/IcX5y6FGDEqUauJ.png" width="300" height="300">


