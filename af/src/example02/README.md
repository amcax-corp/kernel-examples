# Additional Attributes Example 2

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example demonstrates the strategy for handling attribute conflicts, with the following implementation details:

​	

	1. Construct a cube with attributes using WithAttr<MakeBox>
	
	2. Obtain the label using GetResultLabel() under AMCAX::Label
	
	3. Obtain all face labels on the label using GetFaceLabels() under AMCAX::Label
	
	4. Construct an attribute using MakeAttribute() under AMCAX::AttributeTool
	
	5. Attach the attribute to the label using AddAttribute() under AMCAX::Label
	
	6. Construct a cylinder with attributes using WithAttr<MakeCylinder>
	
	7. Obtain the label using GetResultLabel() under AMCAX::Label
	
	8. Obtain all face labels on the label using GetFaceLabels() under AMCAX::Label
	
	9. Construct an attribute using MakeAttribute() under AMCAX::AttributeTool
	
	10. Attach the attribute to the label using AddAttribute() under AMCAX::Label
	
	11. Perform a boolean union using WithAttr<BoolBRepFuse>
	
	12. Define the attribute policy for the specified attribute type using SetPolicy() under AMCAX::WithAttr<BoolOperation>
	
	13. Obtain the label using GetResultLabel() under AMCAX::Label
	
	14. Obtain all face labels on the label using GetFaceLabels() under AMCAX::Label
	
	15. Find the attribute using FindAttribute() under AMCAX::Label
	
	16. Obtain the attribute value using GetValue() under AMCAX::Attribute
	
	17. Update the attribute on the label using UpdateAttribute() under AMCAX::Label

