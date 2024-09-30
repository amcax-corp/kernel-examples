#include <modeling/MakeCylinder.hpp>
#include <common/CartesianCoordinateSystem.hpp>
#include <topomesh/BRepMeshIncrementalMesh.hpp>
#include <modeling/MakeShapeTool.hpp>
#include <io/STLTool.hpp>
int main()
{
	AMCAX::TopoShape middleCylinder = AMCAX::MakeCylinder(AMCAX::Frame3(AMCAX::Point3(0.0, 0.0, 0.0), AMCAX::CartesianCoordinateSystem::DZ()), 31.0, 114.0);
	
	// Meshing
	AMCAX::BRepMeshIncrementalMesh mesher(middleCylinder, 0.005, true);
	if (mesher.IsDone())
	{
		AMCAX::MakeShapeTool::EnsureNormalConsistency(middleCylinder);
	}

	// Export to a STL file
	AMCAX::STLTool::WriteShape(middleCylinder, "part7.stl");
}
