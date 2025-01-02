#include <occtio/OCCTTool.hpp>
#include <shapeEdit/VertexEditor.hpp>
#include <shapeEdit/EdgeEditor.hpp>
#include <shapeEdit/FaceEditor.hpp>
#include <step/StepDataTool.hpp>
#include <topology/TopoCast.hpp>
#include <topology/TopoExplorerTool.hpp>
#include <topology/TopoFace.hpp>
#include <topology/TopoEdge.hpp>
#include <topology/TopoVertex.hpp>
#include <topology/TopoTool.hpp>

void GeomEdit()
{
    using namespace AMCAX;
    using namespace AMCAX::GeomE;

    TopoShape shape;
    STEP::StepDataTool::Read(shape, "./data/FEA_13.step");

    // OCCTIO::OCCTTool::Read(shape, "./FEA.brep");

    // 获取插入点的坐标
    IndexSet<TopoShape> vertices;
    TopoExplorerTool::MapShapes(shape, ShapeType::Vertex, vertices);
    TopoVertex vertex = TopoCast::Vertex(vertices[799]);
    Point3     point = TopoTool::Point(vertex);

    // 获取插入的边
    IndexSet<TopoShape> edges;
    TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
    TopoEdge edge = TopoCast::Edge(edges[1528]);

    // 将点插入到边上
    EdgeEditor::TrimEdgeWithPoint(shape, edge, { point });

    // 获取两条要缝合的边
    edges.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
    TopoEdge edge1 = TopoCast::Edge(edges[1528]);
    TopoEdge edge2 = TopoCast::Edge(edges[1759]);

    // 将edge2缝合到edge1上
    EdgeEditor::SewEdges(shape, edge2, edge1, 0.1);

    // 获取要投影的边
    edges.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
    edge = TopoCast::Edge(edges[1736]);

    // 获取要投影的面
    IndexSet<TopoShape> faces;
    TopoExplorerTool::MapShapes(shape, ShapeType::Face, faces);
    TopoFace face = TopoCast::Face(faces[30]);

    // 边投影到面上
    TopoShape           replaceshape;
    IndexSet<TopoShape> projectedges;
    projectedges.insert(edge);
    FaceEditor::EdgesProjectFace(shape, projectedges, face, replaceshape);

    // 获取两条要缝合的边
    edges.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
    edge1 = TopoCast::Edge(edges[1737]);
    edge2 = TopoCast::Edge(edges[102]);

    // 将edge2缝合到edge1上
    EdgeEditor::SewEdges(shape, edge2, edge1, 0.1);

    // 获取要释放的顶点
    vertices.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Vertex, vertices);
    vertex = TopoCast::Vertex(vertices[845]);

    // 释放顶点
    VertexEditor::ReleaseVertex(shape, vertex);

    // 获取删除的顶点
    vertices.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Vertex, vertices);
    vertex = TopoCast::Vertex(vertices[845]);

    // 删除顶点
    VertexEditor::RemoveVertex(shape, vertex);

    // 获取缝合的顶点
    vertices.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Vertex, vertices);
    TopoVertex vertex1 = TopoCast::Vertex(vertices[417]);
    TopoVertex vertex2 = TopoCast::Vertex(vertices[847]);

    // 将vertex2缝合到vertex1上
    VertexEditor::SewVertices(shape, vertex2, vertex1);

    // 获取两条要缝合的边
    edges.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
    edge1 = TopoCast::Edge(edges[1887]);
    edge2 = TopoCast::Edge(edges[1880]);

    // 将edge2缝合到edge1上
    EdgeEditor::SewEdges(shape, edge2, edge1, 0.1);

    // 获取切分的顶点
    vertices.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Vertex, vertices);
    vertex1 = TopoCast::Vertex(vertices[578]);
    vertex2 = TopoCast::Vertex(vertices[821]);

    // 获取切分的面
    faces.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Face, faces);
    face = TopoCast::Face(faces[903]);

    // 进行参数切分
    FaceEditor::ParameterFaceCut(shape, face, vertex1, vertex2);

    // 获取重建的边
    edges.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
    edge = TopoCast::Edge(edges[452]);

    // 重建并更新边
    EdgeEditor::RebuildAndUpdateEdge(shape, edge);

    // 获取插入的边
    edges.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
    edge = TopoCast::Edge(edges[446]);

    // 根据比例在边上插入顶点
    EdgeEditor::TrimEdgeWithRatio(shape, edge, { 0.3 });

    // 获取释放的边
    edges.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
    edge = TopoCast::Edge(edges[447]);

    // 释放边
    EdgeEditor::ReleaseEdge(shape, edge);

    // 获取要删除的面
    faces.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Face, faces);
    face = TopoCast::Face(faces[832]);

    // 删除面
    FaceEditor::DeleteFace(shape, face);

    // 获取两条要连接的边
    edges.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
    edge1 = TopoCast::Edge(edges[446]);
    edge2 = TopoCast::Edge(edges[447]);

    // 连接两条边为一条边
    IndexSet<TopoShape> joinedges;
    joinedges.insert(edge1);
    joinedges.insert(edge2);
    TopoEdge newedge = EdgeEditor::JoinEdgesAndUpdate(shape, joinedges);

    // 获取要反转定向的面
    faces.clear();
    TopoExplorerTool::MapShapes(shape, ShapeType::Face, faces);
    face = TopoCast::Face(faces[139]);

    // 反转面的定向
    FaceEditor::ReverseOrientation(shape, face);

    OCCTIO::OCCTTool::Write(shape, "./shape.brep");
}


int main()
{
    GeomEdit();
    return 0;
}