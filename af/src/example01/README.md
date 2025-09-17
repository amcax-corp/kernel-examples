# Additional Attributes Example 1

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example demonstrates operations related to additional attributes. The specific implementation steps are as follows:

​	

	1. Create a 5x5x5 cube using AMCAX::MakeBox
	
	2. Create a cylinder with a radius of 5 and a height of 10 using WithAttr<MakeCylinder>
	
	3. Obtain the label using GetResultLabel() under AMCAX::Label
	
	4. Obtain all face labels on the label using GetFaceLabels() under AMCAX::Label
	
	5. Construct an attribute using MakeAttribute() under AMCAX::AttributeTool
	
	6. Attach the attribute to the label using AddAttribute() under AMCAX::Label
	
	7. Perform a boolean intersection using WithAttr<BoolBRepCommon>
	
	8. Define the attribute policy for the specified attribute type using SetPolicy() of WithAttr
	
	9. Obtain the label using GetResultLabel() under AMCAX::Label
	
	10. Find the attribute using FindAttribute() under AMCAX::Label
	
	11. Obtain the attribute value using GetValue() under AMCAX::Attribute
	
	12. Update the attribute on the label using UpdateAttribute() under AMCAX::Label

