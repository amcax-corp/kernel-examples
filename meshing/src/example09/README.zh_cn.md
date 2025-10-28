# 网格缺陷检测示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 本教程提供了多种三角形网格缺陷检测方法的使用示例。具体如下：

	1. 创建 obj_reader 和 obj_writer 对象，用于读取和写入 OBJ 文件
	
	2. 使用 OBJReader 下的 read() 读取 OBJ 文件，并将读取到的数据存储在 io_options 中
	
	3. 使用 AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> 创建一个检测器
	
	4. 使用 AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> 下的 DetectNonManifoldVertices() 检测网格中的非流形顶点
	
	5. 使用 AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> 下的 DetectNonManifoldEdges() 检测网格中的非流形边
	
	6. 使用 AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> 下的 DetectNonManifoldEdgesFor3DPrint() 检测用于 3D 打印的非流形边
	
	7. 使用 AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> 下的 DetectFreeEdges() 检测网格中的自由（边界）边
	
	8. 使用 AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> 下的 DetectDegenerateFaces() 检测网格中的退化（无效）面
	
	9. 使用 AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> 下的 DetectDuplicateFaces() 检测网格中的重复面
	
	10.使用 AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> 下的 DetectIsolatedFaces() 检测网格中的孤立面
	
	11. 使用 AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> 下的 DetectDuplicateVertices() 在给定容差范围内检测重复顶点组
	
	12. 使用 AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> 下的 DetectSelfIntersectingFaces() 检测网格中的自相交面
	
	13. 使用 AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> 下的 DetectFacesWithInconsistentNormals() 检测每个连通组件中法向不一致的面





