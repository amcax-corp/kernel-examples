# AMCAXMeshing 网格算法示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示了增量式重网格化。具体实现如下：

	
	1. 使用 OBJReader<TriSoupTraits> 创建一个 obj_reader 对象
	
	2. 使用 OBJReader<TriSoupTraits> 下的 read() 读取 OBJ 文件
	
	3. 使用 TriMesh_IncrementalRemeshing<TriSoupTraits> 创建一个 remesher 对象
	
	4. 使用 TriMesh_IncrementalRemeshing<TriSoupTraits>::Params 创建一个 params 对象
	
	5. 使用 TriMesh_IncrementalRemeshing<TriSoupTraits>下的 setReferenceMesh() 添加一个三角形网格作为输入
	
	6. 使用 TriMesh_IncrementalRemeshing<TriSoupTraits>下的 setVariableMesh() 将三角形网格设置为输出目标	

	7. 使用 TriMesh_IncrementalRemeshing<TriSoupTraits>下的 remesh() 对输入网格进行各向同性重网格化

	8. 使用 OBJWriter<TriSoupTraits> 创建一个 writer 对象
	
	9. 使用 OBJWriter<TriSoupTraits> 下的 write() 将网格写入 obj 文件
	
	

<div align = center><img src="https://s2.loli.net/2024/09/29/NoZXSl68EBn45Ac.png" width="500" height="300">
