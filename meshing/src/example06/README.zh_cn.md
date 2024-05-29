# AMCAXMeshing 网格算法示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示了增量式重网格化。具体实现如下：


	
	1. 使用 OBJReader<TriSoupTraits> 创建一个 obj_reader 对象
	
	2. 使用 OBJWriter<TriSoupTraits> 创建一个 obj_writer 对象
	
	3. 使用 TriMesh_Incremental_Remeshing 定义一个 inc_remesher 对象
	
	4. 使用 OBJReader<TriSoupTraits> 下的 read() 读取 OBJ 文件

	5. 使用 TriMesh_Incremental_Remeshing 下的  setReferenceMesh() 将三角形网格作为输入
	
	6. 使用 TriMesh_Incremental_Remeshing 下的 setVariableMesh() 将三角形网格作为输出
	
	7. 使用 TriMesh_Incremental_Remeshing::Params 定义一个 param 对象
	
	8. 使用 TriMesh_Incremental_Remeshing::Params 控制重网格的参数
	
	9. 使用 TriMesh_Incremental_Remeshing 下的 remesh() 对网格进行重网格化
	
	10. 使用 OBJWriter<TriSoupTraits> 下的 write() 将网格写入 obj 文件
	
	

<div align = center><img src="https://img2.imgtp.com/2024/05/27/np3W9m2j.png" width="300" height="300">

