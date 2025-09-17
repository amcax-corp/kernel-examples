# 三维边界层详细 JSON 示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示使用网格剖分的三维边界层的详细配置方法，导入brep格式文件，通过json文件传入网格剖分控制参数，自动生成网格。具体实现如下：

	1. 使用 AMCAX::NextMesh::NMAPIModel 下的 InitLogger() 配置 log 格式
	
	2. 使用 AMCAX::NextMesh::NMAPIModel 下的 ImportModel() 导入 TopoShape
	
	3. 使用 AMCAX::NextMesh::NMAPIModel 下的 GenerateMesh() 根据json字符（网格生成控制参数），生成网格
	
	4. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetMesh() 得到生成的网格 api
	
	5. 使用 AMCAX::NextMesh::NMAPIModel 下的 CreatePhysicalSet() 设置面组
	
	6. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetEntitiesInPhysicalSet() 获取指定面组中的实体
	
	7. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetPhysicalSets() 获取指定维度中所有面组
	
	8. 使用 AMCAX::NextMesh::NMMesh 下的 Write（）输出网格文件


