# MCNP 解析器示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 本教程提供 MCNP 解析器的基本用法：解析 MCNP 输入卡，自动构建拓扑实体，最终以 Label 的形式导出结果(Label 中挂载材料属性)。具体实现如下：

	1. 使用 AMCAX::MCNP::MCNPReader 构造一个解析器。
	
	2. 使用 AMCAX::MCNP::MCNPReader 下的 Read() 进行解析和构建。
	
	3. 使用 AMCAX::Label 下的 GetShape() 获取标签所对应的形状。
	
	4. 使用 AMCAX::TopoBuilder 下的 Add() 将遍历得到的形状添加到一个 Compound 中。
	
	5. 使用 AMCAX::Label 下的 FindAllAttributes() 获取标签上的所有属性。
	
	6. 使用 AMCAX::Attribute 下的 GetValue() 获取属性值。
	
	7. 使用 AMCAX::OCCTIO::OCCTTool 下的 Write() 将 Compound 写入 BREP 文件。


