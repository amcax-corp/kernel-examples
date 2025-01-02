# 几何清理修复示例二

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示使用几何编辑的基本用法，导入 step 格式文件，通过调用 GeomE 的 API 对模型进行几何编辑操作对模型进行修复。具体实现如下： 

	1. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取检测的边
	
	2. 使用 AMCAX::GeomE::DetectTool 下的 GetEdgeType() 检测该边的类型
	
	3. 使用 AMCAX::GeomE::DetectTool 下的 DetectFreeBoundaries() 检测该边所属的自由边界
	
	4. 使用 AMCAX::GeomE::FaceEditor 下的 FillHole() 将选中的自由边界进行补洞
	
	5. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取边集
	
	6. 使用 AMCAX::GeomE::FaceEditor 下的 BuildCoons() 用边集构建 Coons 曲面
	
	7. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取边集
	
	8. 使用 AMCAX::GeomE::FaceEditor 下的 BuildPlane() 用边集构建平面
	
	9. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取边集
	
	10. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取已有的面
	
	11. 使用 AMCAX::GeomE::FaceEditor 下的 BuildFaceFromSurface() 用边集根据已有曲面建立新的面
	
	12. 使用 AMCAX::MakeVertex 下的 MakeVertex() 造一个顶点
	
	13. 使用 AMCAX::GeomE::FaceEditor 下的 VerticesProjectFace() 将点投影到面
	
	14. 使用 AMCAX::OCCTIO::OCCTTool 下的 Write() 输出结果


输出结果如下：


<div align = center><img src="https://s2.loli.net/2024/12/31/NnMQrTok6DCdPzZ.png" width="400" height="300"></div>


