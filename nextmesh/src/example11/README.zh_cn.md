# 流体网格剖分示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例提供了使用流体网格剖分的基本方法，具体实现如下：

	1. 使用 AMCAX::STEP::STEPTool 下的 Read() 读取 STEP 文件
	
	2. 使用 AMCAX::NextMesh::NMAPIModel 下的 InitLogger() 配置 log 格式
	
	3. 使用 AMCAX::NextMesh::NMAPIModel 下的 ImportModel() 导入 模型
	
	4. 使用 AMCAX::NextMesh::NMAPIModel 下的 GenerateMesh() 根据json字符（网格生成控制参数），生成网格
	
	5. 使用 AMCAX::NextMesh::NMAPIModel 下的 GetMesh() 获取网格句柄
	
	6. 使用 AMCAX::NextMesh::NMMesh 下的 Write（）输出网格文件
