# 附加属性示例二

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示属性冲突时的策略，具体实现如下：​

​	

		1. 通过 WithAttr<MakeBox> 构造带属性的立方体
		
		2. 通过 AMCAX::Lable 下的 GetResultLabel() 获取标签
		
		3. 通过 AMCAX::Lable 下的 GetFaceLabels() 获取标签上的所有面标签
		
		4. 通过 AMCAX::AttributeTool 下的 MakeAttribute() 构造属性
		
		5. 通过 AMCAX::Lable 下的 AddAttribute() 为标签附加属性
	
		6. 通过 WithAttr<MakeCylinder> 构造带属性的圆柱
		
		7. 通过 AMCAX::Lable 下的 GetResultLabel() 获取标签
		
		8. 通过 AMCAX::Lable 下的 GetFaceLabels() 获取标签上的所有面标签
		
		9. 通过 AMCAX::AttributeTool 下的 MakeAttribute() 构造属性
		
		10. 通过 AMCAX::Lable 下的 AddAttribute() 为标签附加属性
		
		11. 通过 WithAttr<BoolBRepFuse> 执行布尔并
		
		12. 通过 AMCAX::WithAttr< BoolOperation > 下的 SetPolicy() 定义指定属性类型的属性策略
		
		13. 通过 AMCAX::Lable 下的 GetResultLabel() 获取标签
		
		14. 通过 AMCAX::Lable 下的 GetFaceLabels() 获取标签上的所有面标签
		
		15. 通过 AMCAX::Lable 下的 FindAttribute() 查找属性
		
		16. 通过 AMCAX::Atrribute 下的 GetValue() 获取属性的值
		
		17. 通过 AMCAX::Lable 下的 UpdateAttribute() 更新标签上的属性

