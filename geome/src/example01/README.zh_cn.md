# 几何清理修复示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示使用几何编辑的基本用法，导入 step 格式文件，通过调用 GeomE 的 API 对模型进行几何编辑操作对模型进行修复。具体实现如下： 

	1. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取插入点的坐标和插入的边
	
	2. 使用 AMCAX::GeomE::EdgeEditor 下的 TrimEdgeWithPoint() 将点插入到边上
	
	3. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取获取两条要缝合的边
	
	4. 使用 AMCAX::GeomE::EdgeEditor 下的 SewEdges() 将 edge2 缝合到 edge1 上
	
	5. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取要投影的边和要投影的面
	
	6. 使用 AMCAX::GeomE::FaceEditor 下的 EdgesProjectFace()  将边投影到面上
	
	7. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取两条要缝合的边
	
	8. 使用 AMCAX::GeomE::EdgeEditor 下的 SewEdges() 将 edge2 缝合到 edge1 上
	
	9. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取要释放的顶点
	
	10. 使用 AMCAX::GeomE::VertexEditor 下的 ReleaseVertex() 释放顶点
	
	11. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取删除的顶点
	
	12. 使用 AMCAX::GeomE::VertexEditor 下的 RemoveVertex() 删除顶点
	
	13. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取缝合的顶点
	
	14. 使用 AMCAX::GeomE::VertexEditor 下的 SewVertices() 将 vertex2 缝合到 vertex1 上
	
	15. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取两条要缝合的边
	
	16. 使用 AMCAX::GeomE::EdgeEditor 下的 SewEdges() 将 edge2 缝合到 edge1 上
	
	17. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取切分的顶点和切分的面
	
	18. 使用 AMCAX::GeomE::FaceEditor 下的 ParameterFaceCut() 进行参数切分
	
	19. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取重建的边
	
	20. 使用 AMCAX::GeomE::EdgeEditor 下的 RebuildAndUpdateEdge() 重建并更新边
	
	21. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取插入的边
	
	22. 使用 AMCAX::GeomE::EdgeEditor 下的 TrimEdgeWithRatio() 根据比例在边上插入顶点
	
	23. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取释放的边
	
	24. 使用 AMCAX::GeomE::EdgeEditor 下的 ReleaseEdge() 释放边
	
	25. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取要删除的面
	 
	26. 使用 AMCAX::GeomE::FaceEditor 下的 DeleteFace) 删除面
	
	27. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取两条要连接的边
	
	28. 使用 AMCAX::GeomE::EdgeEditor 下的 JoinEdgesAndUpdate() 连接两条边为一条边
	
	29. 使用 AMCAX::TopoExplorerTool 下的 MapShapes() 获取要反转定向的面
	
	30. 使用 AMCAX::GeomE::FaceEditor 下的 ReverseOrientation() 反转面的定向
	
	31. 使用 AMCAX::OCCTIO::OCCTTool 下的 Write() 输出结果


输出结果如下：


<div align = center><img src="https://s2.loli.net/2024/11/29/FHETkbaPmUCInYu.png" width="400" height="300"></div>


