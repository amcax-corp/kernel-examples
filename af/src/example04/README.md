# Additional Attribute Example 4

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example demonstrates serialization and deserialization of AMCAX::Label, with the following implementation:


	1. Construct a cube with attributes using AMCAX::WithAttr<MakeBox>
	
	2. Construct a cylinder with attributes using AMCAX::WithAttr<MakeCylinder>
	
	3. Obtain labels via GetResultLabel()under AMCAX::Label
	
	4. Construct attributes using MakeAttribute()under AMCAX::AttributeTool
	
	5. Add attributes to labels via AddAttribute()under AMCAX::Label
	
	6. Write labels to file using AMCAX::LabelTool::Write
	
	7. Read file using AMCAX::LabelTool::Read
	
	8. Retrieve attributes via FindAttribute()under AMCAX::Label
	
	9. Obtain attribute values via GetValue()under AMCAX::Attribute



