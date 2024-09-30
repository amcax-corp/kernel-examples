#include <common/FrameT.hpp>
#include <tmeshSplineAPI/TMSplineMakeRectangle.hpp>
#include <tmeshSpline/TMSplineMeshing.hpp>
#include <tmeshSpline/TMSplineMeshingIO.hpp>

using namespace AMCAX;
using namespace TMS;

int main()
{
	//Constructing the base
	Frame3 frame;
	TMSplineMakeRectangle mkRect(frame, 3, 3, 3, 3);
	TMSpline* tsp = mkRect.BuildSpline();

	// Meshing
	TMSplineMeshing tspMesh(tsp, 4);
	tspMesh.UpdateDrawMesh();

	// Export to a OBJ file
	TMSplineMeshingIO meshIO;
	std::string fileNameOBJ = "part1.obj";
	meshIO.ExportToOBJ(fileNameOBJ, tspMesh.GetDrawMesh());

	delete tsp;

}
