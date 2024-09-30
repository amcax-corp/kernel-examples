# STEP 文件读写示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示了 Mesh Reader 的基本用法。具体如下：

	1. 使用 using AMCAX::STEP::StepMeshReader<AMCAX::Meshing::Mesh::TriSoupTraits_Coord> 创建对象 reader
	
	2. 使用 using AMCAX::STEP::StepMeshReader<AMCAX::Meshing::Mesh::TriSoupTraits_Coord> 下的 Read() 读取 STEP 文件
	
	3. 使用 using AMCAX::STEP::StepMeshReader<AMCAX::Meshing::Mesh::TriSoupTraits_Coord> 下的 GetShapes() 获取 StepMeshData 树的指针列表
	
	4. 调用函数 _ApplyTrsfInplace，该函数对传入的形状 shape 进行原地变换，并将变换后的结果存储在 trsfStack 中
	
	5. 使用 using AMCAX::STEP::StepMeshReader<AMCAX::Meshing::Mesh::TriSoupTraits_Coord> 下的 ToMesh() 将 TopoShape 对象转换为 Mesh 对象
	
	6. 调用 func 函数，递归遍历每个元素的子元素，并将 StepMeshData 中的网格信息添加到最外层的 meshes 向量中
	
	7. 使用 AMCAX::Meshing::Mesh::IOOptions 声明一个 io_options 对象
	
	8. 使用 Points 声明 points1, result_points 对象
	
	9. 使用 Triangles 声明 triangles1, result_triangles 对象
	
	10. 使用 AMCAX::Meshing::Mesh::STLWriter<AMCAX::Meshing::Mesh::TriSoupTraits_Coord> 声明一个 stl_writer 对象
	
	11. 使用 Triangles 声明一个 trianglestmp 对象
	
	12. 创建了一个三角形对象 tritmp ，用于调整顶点的索引
	
	13. 使用 AMCAX::Meshing::Mesh::STLWriter<AMCAX::Meshing::Mesh::TriSoupTraits_Coord> 下的 write() 将网格写入 STL 文件


<div align = center><img src="https://s2.loli.net/2024/06/12/RjXdmbpAn7UKN1x.png" width="500" height="400">

