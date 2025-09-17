# 块结构网格示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例提供了使用块结构网格的基本用法，先导入需要生成结构化网格的几何文件，然后根据几何模型初始化网格块和编辑网格块，最后离散网格，实现基于几何模型生成结构化网格。具体实现如下：

	1. 使用 AMCAX::NextMesh::NMAPIModel 下的 InitLogger() 配置 log 格式
	
	2. 使用 AMCAX::OCCTIO::OCCTTool 下的 Read() 从文件中读取模型
	
	3. 使用 AMCAX::NextMesh::NMAPIModel 下的 ImportModel() 导入 TopoShape
	
	4. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetEntities() 获取指定维度下的所有实体
	
	5. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetNMBlock() 获取网格块句柄
	
	6. 使用 AMCAX::NextMesh::NMBlock 下的 OSplit() 对指定的六面体块进行 O 型分割
	
	7. 使用 AMCAX::NextMesh::NMBlock 下的 AssociateFace() 将网格面关联到几何面
	
	8. 使用 AMCAX::NextMesh::NMBlock 下的 MatchEdgeToEdge() 将源边的形状匹配到目标边的最优形状
	
	9. 使用 AMCAX::NextMesh::NMBlock 下的 SetEdgesDistribution() 设置边分布
	
	10. 使用 AMCAX::NextMesh::NMBlock 下的 SetEdgesDistribution() 离散化所有块生成三维网格
	
	11. 使用 AMCAX::NextMesh::NMBlock 下的 SmoothBlocks() 光顺三维块网格


