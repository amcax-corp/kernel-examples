#include <occtio/OCCTTool.hpp>
#include <shapeEdit/DetectTool.hpp>
#include <shapeEdit/EdgeEditor.hpp>
#include <shapeEdit/FaceEditor.hpp>
#include <shapeEdit/GeomEMacros.hpp>
#include <shapeEdit/VertexEditor.hpp>
#include <step/StepDataTool.hpp>
#include <topology/TopoCast.hpp>
#include <topology/TopoExplorerTool.hpp>
#include <topology/TopoFace.hpp>
#include <topology/TopoEdge.hpp>
#include <topology/TopoVertex.hpp>
#include <modeling/MakeVertex.hpp>

void GeomEdit()
{
    using namespace AMCAX;
    using namespace AMCAX::GeomE;

    TopoShape shape;
    bool      success = STEP::StepDataTool::Read(shape, "./data/skin.step");

    // 获取检测的边
    IndexSet<TopoShape> edges;
    TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
    TopoEdge edge = TopoCast::Edge(edges[15]);

    // 检测该边的类型
    EdgeType edgetype = DetectTool::GetEdgeType(shape, edge);

    // 检测该边所属的自由边界
    IndexSet<TopoShape> freeboundaries =
        DetectTool::DetectFreeBoundaries(shape, edge);

    // 选中自由边界进行补洞
    FaceEditor::FillHole(shape, freeboundaries);

    // 获取边集
    edges.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
    TopoEdge            edge1 = TopoCast::Edge(edges[9]);
    TopoEdge            edge2 = TopoCast::Edge(edges[10]);
    TopoEdge            edge3 = TopoCast::Edge(edges[11]);
    IndexSet<TopoShape> edgeset;
    edgeset.insert(edge1);
    edgeset.insert(edge2);
    edgeset.insert(edge3);

    // 用边集构建Coons曲面
    TopoFace face = FaceEditor::BuildCoons(shape, edgeset);

    // 获取边集
    edges.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
    edge = TopoCast::Edge(edges[8]);
    edgeset.clear();
    edgeset.insert(edge);

    // 用边集构建平面
    face = FaceEditor::BuildPlane(shape, edgeset);

    // 获取边集
    edges.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
    edge = TopoCast::Edge(edges[3]);
    edge1 = TopoCast::Edge(edges[4]);
    edge2 = TopoCast::Edge(edges[13]);
    edge3 = TopoCast::Edge(edges[14]);
    edgeset.clear();
    edgeset.insert(edge);
    edgeset.insert(edge1);
    edgeset.insert(edge2);
    edgeset.insert(edge3);

    // 获取已有的面
    IndexSet<TopoShape> faces;
    TopoExplorerTool::MapShapes(shape, ShapeType::Face, faces);
    TopoFace existface = TopoCast::Face(faces[0]);

    // 用边集根据已有曲面建立新的面
    face = FaceEditor::BuildFaceFromSurface(shape, edgeset, existface);

    // 造一个顶点
    Point3              p(350., -7., 380.);
    TopoVertex          vertex =MakeVertex(p);
    IndexSet<TopoShape> vertices;
    vertices.insert(vertex);

    // 点投影到面
    TopoShape replaceshape;
    FaceEditor::VerticesProjectFace(shape, vertices, existface, replaceshape);

    OCCTIO::OCCTTool::Write(shape, "./shape.brep");
}

int main()
{
    GeomEdit();
}
