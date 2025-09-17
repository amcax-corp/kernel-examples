# Geometric Cleaning and Repair Example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example demonstrates the basic usage of geometric editing. A STEP file is imported, and geometric editing operations are performed on the model using the GeomE API to repair it. The specific steps are as follows:
#### Note:​​ Before running this example, please extract the FEA.rar file in the data folder to ensure that FEA.brep exists in data.

	1. Use AMCAX::TopoExplorerTool's MapShapes() to get the coordinates of the insertion point and the inserted edge
	
	2. Use AMCAX::GeomE::EdgeEditor's TrimEdgeWithPoint() to insert a point onto the edge
	
	3. Use AMCAX::TopoExplorerTool's MapShapes() to get the two edges to be sewn together
	
	4. Use AMCAX::GeomE::EdgeEditor's SewEdges() to sew edge2 to edge1
	
	5. Use AMCAX::TopoExplorerTool's MapShapes() to get the edge to be projected and the face to project onto
	
	6. Use AMCAX::GeomE::FaceEditor's EdgesProjectFace() to project the edge onto the face
	
	7. Use AMCAX::TopoExplorerTool's MapShapes() to get the two edges to be sewn together
	
	8. Use AMCAX::GeomE::EdgeEditor's SewEdges() to sew edge2 to edge1
	
	9. Use AMCAX::TopoExplorerTool's MapShapes() to get the vertex to be released
	
	10. Use AMCAX::GeomE::VertexEditor's ReleaseVertex() to release the vertex
	
	11. Use AMCAX::TopoExplorerTool's MapShapes() to get the vertex to be deleted
	
	12. Use AMCAX::GeomE::VertexEditor's RemoveVertex() to remove the vertex
	
	13. Use AMCAX::TopoExplorerTool's MapShapes() to get the sewn vertex
	
	14. Use AMCAX::GeomE::VertexEditor's SewVertices() to sew vertex2 to vertex1
	
	15. Use AMCAX::TopoExplorerTool's MapShapes() to get the two edges to be sewn together
	
	16. Use AMCAX::GeomE::EdgeEditor's SewEdges() to sew edge2 to edge1
	
	17. Use AMCAX::TopoExplorerTool's MapShapes() to get the split vertex and split face
	
	18. Use AMCAX::GeomE::FaceEditor's ParameterFaceCut() to perform parameter-based cutting
	
	19. Use AMCAX::TopoExplorerTool's MapShapes() to get the rebuilt edge
	
	20. Use AMCAX::GeomE::EdgeEditor's RebuildAndUpdateEdge() to rebuild and update the edge
	
	21. Use AMCAX::TopoExplorerTool's MapShapes() to get the inserted edge
	
	22. Use AMCAX::GeomE::EdgeEditor's TrimEdgeWithRatio() to insert a vertex into the edge based on a ratio
	
	23. Use AMCAX::TopoExplorerTool's MapShapes() to get the released edge
	
	24. Use AMCAX::GeomE::EdgeEditor's ReleaseEdge() to release the edge
	
	25. Use AMCAX::TopoExplorerTool's MapShapes() to get the face to be deleted
	
	26. Use AMCAX::GeomE::FaceEditor's DeleteFace() to delete the face
	
	27. Use AMCAX::TopoExplorerTool's MapShapes() to get the two edges to be joined
	
	28. Use AMCAX::GeomE::EdgeEditor's JoinEdgesAndUpdate() to join the two edges into one
	
	29. Use AMCAX::TopoExplorerTool's MapShapes() to get the face whose orientation needs to be reversed
	
	30. Use AMCAX::GeomE::FaceEditor's ReverseOrientation() to reverse the orientation of the face
	
	31. Use AMCAX::OCCTIO::OCCTTool's Write() to output the result

The output result is as follows:

<div align = center><img src="https://s2.loli.net/2024/11/29/FHETkbaPmUCInYu.png" width="400" height="300"></div>