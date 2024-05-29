#include <modeling/MakeCylinder.hpp>
#include <common/CartesianCoordinateSystem.hpp>
#include <topomesh/BRepMeshIncrementalMesh.hpp>
#include <modeling/MakeShapeTool.hpp>
#include <io/STLTool.hpp>
#include <fillet/MakeFillet.hpp>
#include <topology/TopoExplorer.hpp>
#include <topology/TopoCast.hpp>
#include <topology/TopoTool.hpp>
int main()
{
	AMCAX::TopoShape middleCylinder = AMCAX::MakeCylinder(AMCAX::Frame3(AMCAX::Point3(0.0, 0.0, 0.0), AMCAX::CartesianCoordinateSystem::DZ()), 31.0, 114.0);

	AMCAX::MakeFillet fillet(middleCylinder);
	for (AMCAX::TopoExplorer ex(middleCylinder, AMCAX::ShapeType::Edge); ex.More(); ex.Next())
	{
		const auto& edge = AMCAX::TopoCast::Edge(ex.Current());
		if (AMCAX::TopoTool::IsClosed(edge))
		{
			fillet.Add(1.0, edge);
		}
	}
	middleCylinder = fillet.Shape();




	// Meshing
	AMCAX::BRepMeshIncrementalMesh mesher(middleCylinder, 0.005, true);
	if (mesher.IsDone())
	{
		AMCAX::MakeShapeTool::EnsureNormalConsistency(middleCylinder);
	}

	// Export to a STL file
	AMCAX::STLTool::WriteShape(middleCylinder, "part8.stl");
}
