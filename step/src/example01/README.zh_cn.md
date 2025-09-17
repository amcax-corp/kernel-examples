# STEP 文件读写示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示了 AMCAX STEP Reader 与 AMCAX STEP Writer 的基本用法。具体如下：


​	

	1. 定义一个 printProductName 函数，用于输出 Product 树状结构
	
	2. 定义一个 printSolidName 函数，用于输出 Product 树中所有 Solid 的命名
	
	3. 使用 AMCAX::STEP::STEPStyledReader 下的 SetTargetUnit() 设置 STEP 转换为 TopoShape 时使用的基本单位，基本单位为 AMCAX::STEP::StepLengthUnit::PresetLengthUnit::METRE
	
	4. 使用 AMCAX::STEP::STEPStyledReader 下的 Read() 读取文件
	
	5. 使用 AMCAX::STEP::STEPStyledReader 下的 GetProducts() 获取 STEPStyledProduct 树列表
	
	6. 使用 AMCAX::STEP::STEPTool 下的 MakeCompound() 提取整体 Shape
	
	7. 使用  AMCAX::STEP::STEPTool 下的 FlattenInplace() 将树展开为一维数组
	
	8. 使用 AMCAX::STEP::STEPWriter 将 TopoShape 对象转换为 STEP 文件
	
	9. 使用 AMCAX::STEP::STEPWriter 下的 SetOutputUnit() 设置 STEP 文件的长度单位
	
	10. 使用 AMCAX::STEP::STEPWriter 下的 WriteShapes() 写入STEP文件的数据部分
	
	11. 使用 AMCAX::STEP::STEPWriter 下的 Done() 编写 STEP 文件的结束部分，关闭输出文件

 




<div align = center><img src="https://s2.loli.net/2024/06/04/tmsLOyEUe1GZDnI.png" width="600" height="300">

