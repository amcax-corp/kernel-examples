# Additional Attributes Example 3

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example demonstrates the property-encapsulated kernel modeling interface, with the following implementation:

​	

	I.
	1. Create a WithAttr<TopoShape> object
	
	2. Obtain the label using GetResultLabel() under AMCAX::Label
	
	3. Construct an attribute using MakeAttribute() under AMCAX::AttributeTool
	
	4. Attach the attribute to the label using AddAttribute() under AMCAX::Label
	
	5. Create a WithAttr<MakeEdge> object
	
	6. Obtain the label using GetResultLabel() under AMCAX::Label
	
	7. Check whether the attribute is automatically inherited using FindAllAttributes() under AMCAX::Label and GetValue() under AMCAX::Attribute
	
	II.
	1. Construct a cube with attributes using WithAttr<MakeBox>
	
	2. Obtain the label using GetResultLabel() under AMCAX::Label
	
	3. Obtain all face labels on the label using GetFaceLabels() under AMCAX::Label
	
	4. Construct an attribute using MakeAttribute() under AMCAX::AttributeTool
	
	5. Attach the attribute to the label using AddAttribute() under AMCAX::Label
	
	6. Create a WithAttr<TransformShape> object and perform the transformation via Perform
	
	7. Obtain the label using GetResultLabel() under AMCAX::Label
	
	8. Obtain all face labels on the label using GetFaceLabels() under AMCAX::Label
	
	9. Check whether the attribute is automatically inherited using FindAttribute() under AMCAX::Label and GetValue() under AMCAX::Attribute
	
	10. Obtain the vertex labels on the transformed label using GetVertexLabels() under AMCAX::Label

