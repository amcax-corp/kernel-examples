# 附加属性示例三

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示内核建模接口的带属性封装，具体实现如下：


	一.
		1. 创建 WithAttr<TopoShape> 对象
		
		2. 通过 AMCAX::Lable 下的 GetResultLabel() 获取标签
		
		3. 通过 AMCAX::AttributeTool 下的 MakeAttribute() 构造属性
		
		4. 通过 AMCAX::Lable 下的 AddAttribute() 为标签附加属性
		
		5. 创建 WithAttr<MakeEdge> 对象
		
		5. 通过 AMCAX::Lable 下的 GetResultLabel() 获取标签
		
		6. 通过 AMCAX::Lable 下的 FindAllAttributes() 和 AMCAX::Atrribute 下的 GetValue() 检查属性是否自动继承
		
	二.
		1. 通过 WithAttr<MakeBox> 构造带属性的立方体
		
		2. 通过 AMCAX::Lable 下的 GetResultLabel() 获取标签
		
		3. 通过 AMCAX::Lable 下的 GetFaceLabels() 获取标签上的所有面标签
		
		4. 通过 AMCAX::AttributeTool 下的 MakeAttribute() 构造属性
		
		5. 通过 AMCAX::Lable 下的 AddAttribute() 为标签附加属性
		
		6. 创建 WithAttr<TransformShape> 对象，并通过 Perform 执行变换
		
		7. 通过 AMCAX::Lable 下的 GetResultLabel() 获取标签
		
		8. 通过 AMCAX::Lable 下的 GetFaceLabels() 获取标签上的所有面标签
		
		9. 通过 AMCAX::Lable 下的 FindAttribute() 和 AMCAX::Atrribute 下的 GetValue() 检查属性是否自动继承
		
		10. 通过 AMCAX::Lable 下的 GetVertexLabels() 获取变换后标签上的顶点标签
		
	

