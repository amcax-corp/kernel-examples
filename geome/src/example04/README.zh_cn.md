# 直升机模型修复与完善示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示使用几何编辑的基本用法修复直升机模型。具体实现如下： 

	融合面：
	
	1. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取模型的面和边
	
	2. 使用 AMCAX::GeomE::FaceEditor 下的 DeleteFace() 删除面
	
	3. 使用 AMCAX::GeomE::FaceEditor 下的 BuildFaceFromSurface() 构造新面
	
	4. 使用 AMCAX::ShapeFixTool 下的 UpgradeUnifySameDomain() 合并面和边
	
	缝合边：
	
	1. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取模型的边
	
	2. 使用 AMCAX::GeomE::DetectTool 下的 DetectFreeEdges() 寻找自由边
	
	3. 使用 AMCAX::GeomE::EdgeEditor 下的 SewEdges() 将两条边缝合起来
	
	补洞：
	1. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取模型的面和边
	
	2. 使用 AMCAX::GeomE::FaceEditor 下的 BuildFaceFromSurface() 构造新面
	
	3. 使用 AMCAX::ShapeFixTool 下的 UpgradeUnifySameDomain() 合并面和边


