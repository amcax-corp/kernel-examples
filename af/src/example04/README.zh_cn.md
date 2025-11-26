# 附加属性示例四

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示 AMCAX::Label 的序列化和反序列化，具体实现如下：


		1. 通过 AMCAX::WithAttr<MakeBox> 构造带属性的立方体
		
		2. 通过 AMCAX::WithAttr<MakeCylinder> 构造带属性的圆柱体
		
		3. 通过 AMCAX::Lable 下的 GetResultLabel() 获取标签
		
		4. 通过 AMCAX::AttributeTool 下的 MakeAttribute() 构造属性
		
		5. 通过 AMCAX::Lable 下的 AddAttribute() 为标签附加属性
		
		6. 通过 AMCAX::LabelTool::Write 将标签写入文件
		
		7. 通过 AMCAX::LabelTool::Read 读取文件
		
		8. 通过 AMCAX::Lable 下的 FindAttribute() 获取属性
		
		9. 通过 AMCAX::Atrribute 下的 GetValue() 获取属性值


​	

