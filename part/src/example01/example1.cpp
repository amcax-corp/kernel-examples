#include "example1.h"
#include <common/PointT.hpp>
#include <modeling/MakePolygon.hpp>
#include <common/VectorT.hpp>
#include <topology/TopoWire.hpp>
#include <topology/TopoFace.hpp>
#include <modeling/MakeFace.hpp>
#include <modeling/MakePolygon.hpp>
#include <io/OBJTool.hpp>
#include <io/STLTool.hpp>
#include <topomesh/BRepMeshIncrementalMesh.hpp>
#include <modeling/MakeShapeTool.hpp>
#include <boolean/BoolBRepFuse.hpp>
#include <fillet/MakeFillet2d.hpp>
#include <common/IndexSet.hpp>
#include <topology/TopoExplorerTool.hpp>
#include <topology/TopoCast.hpp>
int main()
{
    AMCAX::Point3 p1(-80.0, 0.0, 56.0);
    AMCAX::MakePolygon makePolygon;
    int n = 6;
    for (int i = 0; i < n; ++i)
    {
        double t = M_PI * 2.0 * i / n;
        makePolygon.Add(p1.Translated(AMCAX::Vector3(0.0, std::cos(t), std::sin(t)) * 50.0));
    }
    makePolygon.Close();
    AMCAX::TopoWire w = makePolygon;
    AMCAX::TopoFace f = AMCAX::MakeFace(w, true);

    // Meshing
    AMCAX::BRepMeshIncrementalMesh mesher(f, 0.005, true);
    if (mesher.IsDone())
    {
        AMCAX::MakeShapeTool::EnsureNormalConsistency(f);
    }

    AMCAX::STLTool::WriteShape(f, "part1.stl");

}