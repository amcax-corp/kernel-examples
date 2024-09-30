#include <common/FrameT.hpp>
#include <polymeshAPI/MeshMakeRectangle.hpp>
#include <polymeshAPI/MeshSubdivideHE.hpp>
#include <polymesh/PolyMeshIO.hpp>
#include <polymeshAPI/MeshExtrude.hpp>
#include <common/VectorT.hpp>
#include <polymeshAPI/MeshTransform.hpp>
#include <common/AxisT.hpp>
#include <polymeshAPI/MeshReduce.hpp>

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

	//Do Subdivision
	MeshSubdivideHE::CatmullClark(mesh, 3);


	//Save Mesh
	std::string fileNameOBJ = "example3.obj";
	PolyMeshIO::WriteMesh(fileNameOBJ, mesh);
}
