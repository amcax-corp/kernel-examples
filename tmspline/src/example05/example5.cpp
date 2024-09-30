#include <common/FrameT.hpp>
#include <tmeshSplineAPI/TMSplineMakeRectangle.hpp>
#include <tmeshSpline/TMSplineMeshing.hpp>
#include <tmeshSpline/TMSplineMeshingIO.hpp>
#include <tmeshSplineAPI/TMSplineExtrude.hpp>
#include <tmeshSplineAPI/TMSplineTransform.hpp>
#include <common/AxisT.hpp>
#include <tmeshSplineAPI/TMSplineReduce.hpp>
#include <tmeshSplineAPI/TMSplineCheck.hpp>
#include <tmeshSplineAPI/TMSplineTool.hpp>
#include <tmeshSplineAPI/TMSplineThicken.hpp>

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


	//Stretch edges and transform
	std::vector<int> edgeid;
	std::vector<int> edge_id_new;
	for (int i = 0; i < tsp->numEdges(); ++i)
	{
		if (TMSplineCheck::IsEdgeBoundary(tsp, i))
		{
			int v0, v1;
			TMSplineTool::EdgeVertexIndexs(tsp, i, v0, v1);
			Point3 pv0 = TMSplineTool::ControlPosition(tsp, v0);
			Point3 pv1 = TMSplineTool::ControlPosition(tsp, v1);
			if (pv0.Z() > 0.9 * h && pv1.Z() > 0.9 * h)
			{
				edgeid.push_back(i);
			}
		}
	}

	extrude.CanExtrudeEdges(tsp, edgeid);
	extrude.ExtrudeEdges(tsp, edgeid, edge_id_new);
	TMSplineTransform trsfE;
	Transformation3 trsfScale;
	trsfScale.SetScale(Point3(1.5, 1.5, h), 3);
	trsfE.SetTransformation(trsfScale);
	trsfE.TransformTMSplineEdges(tsp, edge_id_new);
	trsfE.TransformReprocessing(tsp);


	//Perform the thickening operation
	TMSplineThicken mkThick;
	mkThick.ThickenTMSpline(tsp, 0.2);

	// Meshing
	TMSplineMeshing tspMesh(tsp, 4);
	tspMesh.UpdateDrawMesh();

	// Export to a OBJ file
	TMSplineMeshingIO meshIO;
	std::string fileNameOBJ = "part5.obj";
	meshIO.ExportToOBJ(fileNameOBJ, tspMesh.GetDrawMesh());

	delete tsp;



}
