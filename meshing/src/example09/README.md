# Mesh Defect Detection Example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This tutorial provides usage examples of various triangle mesh defect detection methods. The details are as follows:

	1. Create obj_reader and obj_writer objects for reading and writing OBJ files
	
	2. Use read() under OBJReader to read the OBJ file and store the read data in io_options
	
	3. Create a detector using AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits>
	
	4. Use DetectNonManifoldVertices() under AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> to detect non-manifold vertices in the mesh
	
	5. Use DetectNonManifoldEdges() under AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> to detect non-manifold edges in the mesh
	
	6. Use DetectNonManifoldEdgesFor3DPrint() under AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> to detect non-manifold edges for 3D printing
	
	7. Use DetectFreeEdges() under AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> to detect free (boundary) edges in the mesh
	
	8. Use DetectDegenerateFaces() under AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> to detect degenerate (invalid) faces in the mesh
	
	9. Use DetectDuplicateFaces() under AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> to detect duplicate faces in the mesh
	
	10. Use DetectIsolatedFaces() under AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> to detect isolated faces in the mesh
	
	11. Use DetectDuplicateVertices() under AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> to detect groups of duplicate vertices within a given tolerance
	
	12. Use DetectSelfIntersectingFaces() under AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> to detect self-intersecting faces in the mesh
	
	13. Use DetectFacesWithInconsistentNormals() under AMCAX::Meshing::MeshTools::TriMesh_DefectDetector<TriSoupTraits> to detect faces with inconsistent normals in each connected component





