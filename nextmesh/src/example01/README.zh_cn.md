# 网格剖分示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示使用网格剖分的基本用法，导入step格式文件，通过json文件传入网格剖分控制参数，自动生成体网格。具体实现如下：

	1. 使用 AMCAX::NextMesh::NMAPIModel 下的 InitLogger() 配置 log 格式
	
	2. 使用 AMCAX::NextMesh::NMAPIModel 下的 ImportModel() 导入 cad 文件，新建模型
	
	3. 使用 AMCAX::NextMesh::NMAPIModel 下的 GenerateMesh() 根据json字符（网格生成控制参数），生成网格
	
	4. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetMesh() 得到生成的网格 api
	
	5. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetEntities() 获取 dim 维度下所有实体
	
	6. 使用 AMCAX::NextMesh::NMMesh 下的 GetEntityElementTypes() 获取实体 ent 所包含的全部单元类型
	
	7. 使用 AMCAX::NextMesh::NMMesh 下的 GetNodesByElementType() 获取实体所包含的cType类型单元的节点序列
	
	8. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetParentAdjacentEntities() 获取包含实体 ent 的 dim+1 维度实体序列
	
	9. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetChildAdjacentEntities() 获取实体 ent 包含的 dim-1 维度实体序列
	
	10. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetBBox() 获取整个模型的 boundingbox
	
	11. 使用 AMCAX::NextMesh::NMMesh 下的 GetAllNodes() 获取全部网格顶点
	
	12. 使用 AMCAX::NextMesh::NMAPIModel 下的 CreatePhysicalSet() 设置面组
	
	13. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetEntitiesInPhysicalSet() 获取指定面组中的实体
	
	14. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetPhysicalSets() 获取指定维度中所有面组
	
	15. 使用 AMCAX::NextMesh::NMMesh 下的 Write（）输出网格文件


生成的网格模型如下：

	1. Json示例（对应的导入文件为1.stp和1.json） 

<div align = center><img src="https://s2.loli.net/2024/08/21/fgE13hGHXuNz29m.png" width="400" height="300"></div>

	2. Json示例-平面边界层（对应的导入文件为2.step和2.json）

<div align = center><img src="https://s2.loli.net/2024/09/29/lamGrEMwyuhPvg8.png" width="300" height="250"></div>

	3. Json示例-空间边界层（对应的导入文件为3.step和3.json）

<div align = center><img src="https://s2.loli.net/2024/09/29/hc1jrQLRWPH6s8J.png" width="300" height="250"></div>

