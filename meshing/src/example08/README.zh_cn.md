# 网格切割算法

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示了网格切割算法的基本用法。具体如下：

	1. 创建 obj_reader 和 obj_writer 对象，用于读取和写入 OBJ 文件
	
	2. 定义输入文件的路径 in_filename
	
	3. 定义输出文件的路径 out_cut_filename 和 out_para_filename，分别表示剪切后的网格文件和参数化后的网格文件的路径
	
	4. 使用 OBJReader 下的 read() 读取 OBJ 文件，并将读取到的数据存储在 io_options 中
	
	5. 使用 AMCAX::Meshing::TriMeshCut::GreedyCut<TriSoupTraits_Coord> 创建对象 mesh_cut，并传入 i_points 和 i_triangles
	
	6. 使用 AMCAX::Meshing::TriMeshCut::GreedyCut<TriSoupTraits> 下的 cut() 对网格进行切割，切割后的顶点和三角形存储在 cut_points 和 cut_triangles 中
	
	7. 使用 OBJWriter 下的 write() 将切割后的网格写入到 OBJ 文件中
	
	8. 使用 OBJWriter 下的 clear() 清除数据
	
	9. 使用 AMCAX::Meshing::Parameterization::BijectivePara<TriSoupTraits_Coord> 创建对象 para，并传入切割后的顶点和三角形数据，以及一个空的 para_points 容器
	
	10. 使用 AMCAX::Meshing::Parameterization::BijectivePara<TriSoupTraits_Coord> 下的 parameterization() 执行参数化操作
	
	11. 使用 OBJWriter 下的 write() 将参数化后的网格写入到 OBJ 文件中

切割后和参数化结果如下（注：每次执行切割后的结果并不相同。）

<div align = center><img src="https://s2.loli.net/2024/07/30/phWa9Itz4QyFmL3.png" width="500" height="400">


<div align = center><img src="https://s2.loli.net/2024/07/30/hKe5auQdSDpYrRC.png" width="500" height="400">




