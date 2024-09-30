# AMCAXMeshing 网格算法示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示了网格修复算法。具体实现如下：



	1. 使用 FastQEM<TriSoupTraits_Coord>::ProFn 定义一个名为 pro_fn 的算法进度回调函数
	
	2. 使用 OBJReader<TriSoupTraits_Coord> 创建一个 obj_reader 对象
	
	3. 使用 STLReader<TriSoupTraits_Coord> 创建一个 stl_reader 对象
	
	4. 使用 OBJWriter<TriSoupTraits_Coord> 创建一个 obj_writer 对象
	
	5. 使用 STLWriter<TriSoupTraits_Coord> 创建一个 stl_writer 对象
	
	6. 使用 STLReader<TriSoupTraits_Coord> 下的 read() 读取 stl 文件
	
	7. 使用 TriMeshRepair<TriSoupTraits_Coord> 下的 repair() 修复网格
	
	8. 使用 STLWriter<TriSoupTraits_Coord> 下的 write() 将网格写入 stl 文件
	
	9. 使用 OBJWriter<TriSoupTraits_Coord> 下的 write() 将网格写入 obj 文件



<div align = center><img src="https://s2.loli.net/2024/09/30/Rad3QoCSHWlgNFD.png" width="300" height="300">

