# 附加属性示例一

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示附加属性的相关操作，具体实现如下：​

​	

		1. 通过 AMCAX::MakeBox 创建一个 5x5x5 的立方体
		
		2. 通过 WithAttr<MakeCylinder> 创建一个半径为 5，高度为 10 的圆柱体
		
		3. 通过 AMCAX::Lable 下的 GetResultLabel() 获取标签
		
		4. 通过 AMCAX::Lable 下的 GetFaceLabels() 获取标签上的所有面标签
		
		5. 通过 AMCAX::AttributeTool 下的 MakeAttribute() 构造属性
		
		6. 通过 AMCAX::Lable 下的 AddAttribute() 为标签附加属性
		
		7. 通过 WithAttr<BoolBRepCommon> 执行布尔交
		
		8. 通过 WithAttr 的 SetPolicy() 定义指定属性类型的属性策略
		
		9. 通过 AMCAX::Lable 下的 GetResultLabel() 获取标签
		
		10. 通过 AMCAX::Lable 下的 FindAttribute() 查找属性
		
		11. 通过 AMCAX::Atrribute 下的 GetValue() 获取属性的值
		
		12. 通过 AMCAX::Lable 下的 UpdateAttribute() 更新标签上的属性

