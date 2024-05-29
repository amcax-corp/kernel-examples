#include <common/FrameT.hpp>
#include <polymeshAPI/MeshMakeRectangle.hpp>
#include <polymeshAPI/MeshSubdiveHE.hpp>
#include <polymesh/PolyMeshIO.hpp>
using namespace AMCAX;
using namespace SubD;

int main()
{
	//Build Bottom mesh
	Frame3 frame;
	MeshMakeRectangle mkRect(frame, 3, 3, 3, 3);
	PolyMesh* mesh = mkRect.BuildMesh();

	//Do Subdivision
	MeshSubdiveHE::CatmullClarkSubdive(mesh, 3);


	//Save Mesh
	std::string fileNameOBJ = "example1.obj";
	PolyMeshIO::WriteMesh(fileNameOBJ, mesh);
}
