#include <common/FrameT.hpp>
#include <polymeshAPI/MeshMakeRectangle.hpp>
#include <polymeshAPI/MeshSubdivideHE.hpp>
#include <polymesh/PolyMeshIO.hpp>
#include <polymeshAPI/MeshExtrude.hpp>
#include <common/VectorT.hpp>
#include <polymeshAPI/MeshTransform.hpp>
#include <common/AxisT.hpp>
#include <polymeshAPI/MeshReduce.hpp>
#include <polymeshAPI/MeshCheck.hpp>
#include <polymeshAPI/MeshTool.hpp>
#include <polymeshAPI/MeshOffset.hpp>
#include <polymeshAPI/MeshSplit.hpp>

using namespace AMCAX;
using namespace SubD;

int main()
{
	//Build Bottom mesh
	Frame3 frame;
	MeshMakeRectangle mkRect(frame, 3, 3, 3, 3);
	PolyMesh* mesh = mkRect.BuildMesh();

	//Extrude faces and apply transformations
	std::vector<int> face_id = { 4 };
	std::vector<int> face_id_new;
	MeshExtrude::ExtrudeFace(mesh, face_id, face_id_new);

	double h = 2;
	Vector3 vh(frame.Direction().Coord() * h);
	MeshTransform trsfF;
	Transformation3 trsfMove;
	trsfMove.SetTranslation(vh);
	trsfF.SetTransformation(trsfMove);
	trsfF.TransformMeshFaces(mesh, face_id_new);
	Transformation3 trsfRot;
	trsfRot.SetRotation(Axis3(Point3(1.5, 1.5, 0.), Direction3(0., 0., 1.)), M_PI / 4);
	trsfF.SetTransformation(trsfRot);
	trsfF.TransformMeshFaces(mesh, face_id_new);

	//Delete top face
	MeshReduce::DeleteFaces(mesh, face_id_new);

	//Extrude edges and apply transformations
	std::vector<int> edgeid;
	std::vector<int> edge_id_new;
	for (int i = 0; i < mesh->numEdges(); ++i)
	{
		if (MeshCheck::IsEdgeBoundary(mesh, i))
		{
			int v0, v1;
			MeshTool::EdgeVertexIndexs(mesh, i, v0, v1);
			Point3 pv0 = MeshTool::Position(mesh, v0);
			Point3 pv1 = MeshTool::Position(mesh, v1);
			if (pv0.Z() > 0.9 * h && pv1.Z() > 0.9 * h)
			{
				edgeid.push_back(i);
			}
		}
	}

	MeshExtrude::ExtrudeEdge(mesh, edgeid, edge_id_new);
	MeshTransform trsfE;
	Transformation3 trsfScale;
	trsfScale.SetScale(Point3(1.5, 1.5, h), 3);
	trsfE.SetTransformation(trsfScale);
	trsfE.TransformMeshEdges(mesh, edge_id_new);

	//Perform thickening
	MeshOffset::ThickenMesh(mesh, 0.2);

	//Apply face split
	for (int i = 0; i < mesh->numEdges(); ++i)
	{
		int v0, v1;
		MeshTool::EdgeVertexIndexs(mesh, i, v0, v1);
		Point3 pv0 = MeshTool::Position(mesh, v0);
		Point3 pv1 = MeshTool::Position(mesh, v1);
		if (std::fabs(pv1.Z() - pv0.Z()) > 0.8 * h)
		{
			MeshSplit::SplitLoop(mesh, i);
			i = 0;
		}
	}

	//Do Subdivision
	MeshSubdivideHE::CatmullClark(mesh, 3);


	//Save Mesh
	std::string fileNameOBJ = "example6.obj";
	PolyMeshIO::WriteMesh(fileNameOBJ, mesh);
}
