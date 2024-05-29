#include <common/FrameT.hpp>
#include <tmeshSplineAPI/TMSplineMakeRectangle.hpp>
#include <tmeshSpline/TMSplineMeshing.hpp>
#include <tmeshSpline/TMSplineMeshingIO.hpp>
#include <tmeshSplineAPI/TMSplineExtrude.hpp>
#include <tmeshSplineAPI/TMSplineTransform.hpp>
#include <common/AxisT.hpp>
#include <tmeshSplineAPI/TMSplineReduce.hpp>

using namespace AMCAX;
using namespace TMS;

int main()
{
	//Constructing the base
	Frame3 frame;
	TMSplineMakeRectangle mkRect(frame, 3, 3, 3, 3);
	TMSpline* tsp = mkRect.BuildSpline();

	//Stretch edges and transform
	TMSplineExtrude extrude;
	std::vector<int> face_id = { 4 };
	std::vector<int> face_id_new;
	if (extrude.CanExtrudeFaces(tsp, face_id))
	{
		extrude.ExtrudeFaces(tsp, face_id, face_id_new);
	}
	double h = 2;
	Vector3 vh(frame.Direction().Coord() * h);
	TMSplineTransform trsfF;
	Transformation3 trsfMove;
	trsfMove.SetTranslation(vh);
	trsfF.SetTransformation(trsfMove);
	trsfF.TransformTMSplineFaces(tsp, face_id_new);
	Transformation3 trsfRot;
	trsfRot.SetRotation(Axis3(Point3(1.5, 1.5, 0.), Direction3(0., 0., 1.)), M_PI / 4);
	trsfF.SetTransformation(trsfRot);
	trsfF.TransformTMSplineFaces(tsp, face_id_new);
	trsfF.TransformReprocessing(tsp);

	//Remove top
	TMSplineReduce reduce;
	reduce.DeleteFaces(tsp, face_id_new);

	// Meshing
	TMSplineMeshing tspMesh(tsp, 4);
	tspMesh.UpdateDrawMesh();

	// Export to a OBJ file
	TMSplineMeshingIO meshIO;
	std::string fileNameOBJ = "part3.obj";
	meshIO.ExportToOBJ(fileNameOBJ, tspMesh.GetDrawMesh());

	delete tsp;



}
