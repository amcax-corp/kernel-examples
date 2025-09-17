# 网格质量示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例提供了如何计算网格质量。具体实现如下：

	1. 使用 AMCAX::NextMesh::NMAPIModel 下的 InitLogger() 配置 log 格式
	
	2. 使用 AMCAX::NextMesh::NMAPIModel 下的 ImportModel() 导入 TopoShape

	3. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetEntities() 获取指定维度下的所有实体
	
	4. 使用 AMCAX::NextMesh::NMAPIModel 下的 GenerateMesh() 根据json字符（网格生成控制参数），生成网格
	
	5. 使用 AMCAX::NextMesh::NMMesh 下的 EntityGetElementCount（）获取实体中的单元数量

	6. 使用 AMCAX::NextMesh::NMMesh 下的 EntityGetElementByIndex（）获取实体中的指定索引处的单元

	7. 使用 AMCAX::NextMesh::NMMesh 下的 ElementGetType（）获取单元类型

	8. 使用 AMCAX::NextMesh::NMMesh 下的 ComputeQuality（）计算网格质量