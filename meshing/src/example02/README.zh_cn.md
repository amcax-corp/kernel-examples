# AMCAXMeshing 网格算法示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示了网格布尔算法。具体实现如下：



	1. 声明一个名为 read_mesh 的函数，用于读取三角网格文件
	
	2. 使用 OBJReader 创建一个 reader 对象
	
	3. 声明一个名为 write_mesh 的函数，用于将三角网格数据写入文件
	
	4. 使用 OBJWriter 创建一个 writer 对象
	
	5. 定义一个名为 MeshBoolean_MeshBoolean 的函数
	
	6. 使用 read_mesh 函数从 obj 文件中读取网格数据，并将这些数据分别存储在变量 points1, triangles1 和变量 points2, triangles2 中
	
	7. 创建一个 MeshBoolean 对象，名为 boolean
	
	8. 使用 MeshBoolean 下的 addTriMeshAsInput() 将读取的两个三角形网格数据作为输入
	
	9. 使用 MeshBoolean 下的 setTriMeshAsOutput() 指定用于存储结果的点和三角形的变量
	
	10. 使用 MeshBoolean 下的 Union() 计算两个输入网格的并集
	
	11. 使用 MeshBoolean 下的 Intersection() 计算两个输入网格的交集
	
	12. 使用 MeshBoolean 下的 Xor() 计算两个输入网格的异或
	
	13. 使用 MeshBoolean 下的 Subtraction() 计算两个输入网格的差
	
	14. 使用 write_mesh 函数将网格写入 obj 文件

	
#### 以下依次是并集，交集，异或，差的结果

<div align = center><img src="https://s2.loli.net/2024/09/30/4TdxrM6DpyhNKIa.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/VTIAUJF2pseyBkH.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/HUPx1e9p3nSNvYt.png" width="300" height="300">

<div align = center><img src="https://s2.loli.net/2024/09/30/Hmyep8arM9n5Ubg.png" width="300" height="300">