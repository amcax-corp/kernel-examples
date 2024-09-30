# 网格参数化算法

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示了网格参数化算法的基本用法。具体如下：

	1. 创建 obj_reader 和 obj_writer 对象，用于读取和写入 OBJ 文件
	
	2. 使用 OBJReader 下的 read() 读取 OBJ 文件，并将读取到的数据存储在 io_options 中
	
	3. 使用 AMCAX::Meshing::Parameterization::BijectivePara<TriSoupTraits_Coord> 创建对象 para
	
	4. 使用 AMCAX::Meshing::Parameterization::BijectivePara<TriSoupTraits_Coord> 下的 parameterization() 对网格执行参数化操作
	
	5. 使用 OBJWriter 下的 write() 将参数化后的网格写入到 OBJ 文件中

参数化结果：

<div align = center><img src="https://s2.loli.net/2024/07/30/mjFYrbToCVD6BLc.png" width="500" height="400">
