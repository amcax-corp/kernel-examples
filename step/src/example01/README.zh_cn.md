# STEP 文件读写示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示了 AMCAX STEP Reader 与 AMCAX STEP Writer 的基本用法。具体如下：

	
	

	1. 定义一个 printProductName 函数，用于输出 Product 树状结构
	
	2. 定义一个 printSubName 函数，用于输出 Product 树中所有 Sub-Shape 的命名
	
	3. 使用 AMCAX::STEP::StepDataList 创建用于储存数据的容器

	4. 使用 AMCAX::STEP::StepReader 创建 shapes 对象，用于将 STEP 文件转换为 TopoShape 对象
	
	5. 使用 AMCAX::STEP::StepReader 下的 SetUnit() 设置 STEP 转换为 TopoShape 时使用的基本单位，基本单位为 AMCAX::STEP::StepLengthUnit::PresetLengthUnit::METRE
	
	6. 使用 AMCAX::STEP::StepReader 下的 Read() 读取 STEP 实体
	
	7. 使用 AMCAX::STEP::StepReader 下的 GetShapes() 获取StepData树的指针列表
 
	8. 使用 AMCAX::STEP::StepDataTool::Flatten 创建一个 StepData 树的副本，并将其平铺成一个数组
	
	9. 使用 AMCAX::STEP::StepWriter 将 TopoShape 对象转换为 STEP 文件
	
	10. 使用 AMCAX::STEP::StepWriter 下的 SetUnit() 设置 STEP 文件的长度单位
	
	11. 使用 AMCAX::STEP::StepWriter 下的 Init() 将 STEP 文件的头部分写入流
	
	12. 使用 AMCAX::STEP::StepWriter 下的 WriteShape() 写入STEP文件的数据部分
	
	13. 使用 AMCAX::STEP::StepWriter 下的 Done() 编写 STEP 文件的结束部分，关闭输出文件

 

<div align = center><img src="https://s2.loli.net/2024/06/04/tmsLOyEUe1GZDnI.png" width="600" height="300">
