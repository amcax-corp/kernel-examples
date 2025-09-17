# STEP 文件读写示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示了 Mesh Reader 的基本用法。具体如下：

	1. 使用 AMCAX::STEP::STEPMeshReader<TriSoupTraits> 下的 Read() 读取文件
	
	2. 使用 AMCAX::STEP::STEPMeshReader<TriSoupTraits> 下的 GetProducts() 获取 STEPMeshProduct 节点
	
	3. 使用 AMCAX::STEP::STEPTool 下的 ApplyTrsfInplace() 实现对传入的shapes 进行原地变换
	
	4. 使用 AMCAX::STEP::STEPMeshReader<TriSoupTraits> 下的 ToMesh() 将 TopoShape 对象转换为 Mesh 对象
	
	5. 调用 func 函数，递归遍历每个元素的子元素，并将 meshdata 中的网格信息添加到 meshes 向量中
	
	6. 使用 AMCAX::Meshing::Mesh::IOOptions 声明一个 io_options 对象
	
	7. 使用 AMCAX::Meshing::Mesh::TriSoupTraits_Coord::Points 声明 points1, result_points 对象
	
	8. 使用AMCAX::Meshing::Mesh::TriSoupTraits_Coord::Triangles 声明 triangles1, result_triangles 对象
	
	9. 使用 AMCAX::Meshing::Mesh::STLWriter<AMCAX::Meshing::Mesh::TriSoupTraits_Coord> 声明一个 stl_writer 对象
	
	10. 使用AMCAX::Meshing::Mesh::TriSoupTraits_Coord::Triangles 声明一个 trianglestmp 对象
	
	11. 创建了一个 tritmp 对象，用于调整顶点的索引
	
	12. 使用 AMCAX::Meshing::Mesh::STLWriter<AMCAX::Meshing::Mesh::TriSoupTraits_Coord> 下的 write() 将网格写入 STL 文件


<div align = center><img src="https://s2.loli.net/2024/06/12/RjXdmbpAn7UKN1x.png" width="500" height="400">

