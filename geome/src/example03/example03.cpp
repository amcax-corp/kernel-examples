#include <occtio/OCCTTool.hpp>
#include <shapeEdit/DetectTool.hpp>
#include <shapeEdit/FaceEditor.hpp>
#include <shapeEdit/GeomImprint.hpp>
#include <shapeEdit/Options.hpp>
#include <topology/TopoExplorerTool.hpp>
#include <topology/TopoShape.hpp>

void GeomEdit()
{
    AMCAX::TopoShape shape;
    AMCAX::OCCTIO::OCCTTool::Read(shape, "./data/weidai1.brep");

    AMCAX::IndexSet<AMCAX::TopoShape> solids;
    AMCAX::TopoExplorerTool::MapShapes(shape, AMCAX::ShapeType::Solid, solids);
    AMCAX::TopoShape solid = solids[0];
    AMCAX::GeomE::FaceEditor faceeditor;
    faceeditor.AlignFaceOrientations(solid);

    AMCAX::IndexSet<AMCAX::TopoShape> shells;
    AMCAX::TopoExplorerTool::MapShapes(solid, AMCAX::ShapeType::Shell, shells);
    bool isclosed = AMCAX::GeomE::DetectTool::IsClosed(shells[0]);

    // 1
    AMCAX::GeomE::GeomImprint imprint1;
    imprint1.Imprint(shape, { solids[0], solids[1] }, {});
    AMCAX::OCCTIO::OCCTTool::Write(shape, "./shape1.brep");

    // 2
    AMCAX::OCCTIO::OCCTTool::Read(shape, "./data/faces.brep");
    AMCAX::IndexSet<AMCAX::TopoShape> faces;
    AMCAX::TopoExplorerTool::MapShapes(shape, AMCAX::ShapeType::Face, faces);
    AMCAX::GeomE::GeomImprint imprint2;
    imprint2.Imprint(shape, { faces[0] }, { faces[2] });
    AMCAX::OCCTIO::OCCTTool::Write(shape, "./shape2.brep");

    // 3
    AMCAX::OCCTIO::OCCTTool::Read(shape, "./data/faces.brep");
    faces.clear();
    AMCAX::TopoExplorerTool::MapShapes(shape, AMCAX::ShapeType::Face, faces);
    AMCAX::GeomE::GeomImprint imprint3;
    imprint3.Imprint(shape, { faces[1] }, { faces[2] });
    AMCAX::OCCTIO::OCCTTool::Write(shape, "./shape3.brep");
}


int main()
{
    GeomEdit();
}
