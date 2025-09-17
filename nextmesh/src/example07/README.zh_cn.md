# 复合边示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示如何复合边。具体实现如下：

	1. 使用 AMCAX::NextMesh::NMAPIModel 下的 InitLogger() 配置 log 格式
	
	2. 使用 AMCAX::OCCTIO::OCCTTool 下的 Read() 从文件中读取模型
	
	3. 使用 AMCAX::NextMesh::NMAPIModel 下的 ImportModel() 导入 TopoShape
	
	4. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetEntity() 获取指定维度下的所有实体
	
	5. 使用 AMCAX::NextMesh::NMAPIModel 下的 AddCompositeEntity() 生成复合边
	
	6. 使用 AMCAX::NextMesh::NMAPIModel 下的 GenerateMesh() 根据json字符（网格生成控制参数），生成网格
	
	7. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetMesh() 获取网格句柄
	
	8. 使用 AMCAX::NextMesh::NMMesh 下的 Write（）输出网格文件

<div align = center><img src="https://s2.loli.net/2025/09/10/MmBlXNZPRcG84ph.png" width="400" height="300"></div>

