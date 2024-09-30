# AMCAXMeshing 网格算法示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示了网格简化算法。具体实现如下：


	1. 使用 FastQEM<TriSoupTraits_Coord>::ProFn 定义一个名为 pro_fn 的算法进度回调函数
	
	2. 使用 OBJReader<TriSoupTraits_Coord> 创建一个 obj_reader 对象
	
	3. 使用 OBJWriter<TriSoupTraits_Coord> 创建一个 obj_writer 对象
	
	4. 使用 OBJReader 下的 read() 读取 OBJ 文件
	
	5. 使用 FastQEM<TriSoupTraits_Coord> 定义一个 fast_qem 对象，接收 obj_reader 读取的顶点和三角形数据
	
	6. 使用 Logger 下的 elapse_reset() 重置运行时间
	
	7. 使用 FastQEM<TriSoupTraits_Coord> 下的 simplify() 简化网格
	
	8. 使用 Logger 下的 elapsed() 返回自上次重置以来经过的时间
	
	9. 使用 OBJWriter<TriSoupTraits_Coord> 下的 write() 将简化后的网格写入文件，文件名包含简化比率

##### 以下简化比率依次为 0.01, 0.1, 0.3, 0.6


<div align = center><img src="https://img2.imgtp.com/2024/05/23/rD4HtwaU.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/23/9qimxCQj.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/23/tDg2YitA.png" width="300" height="300">

<div align = center><img src="https://img2.imgtp.com/2024/05/23/HAiTZfrv.png" width="300" height="300">
