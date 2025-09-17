#include <af/feature/WithAttrModeling.hpp>
#include<iostream>

using namespace AMCAX;
int main() {
    Point3 p1{ 0.,0.,0. }, p2{ 1.,0.,0. }, p{ 0.,0.,0. };
    WithAttr<TopoShape> v1{ MakeVertex{p1} };
    WithAttr<TopoShape> v2{ MakeVertex{p2} };
    auto labelV1 = v1.GetResultLabel();
    auto labelV2 = v2.GetResultLabel();
    // 为两个 Vertex 附加属性。
    labelV1.AddAttribute(AttributeTool::MakeAttribute<StringAttribute>("string", "labelV1"));
    labelV2.AddAttribute(AttributeTool::MakeAttribute<StringAttribute>("string", "labelV2"));

    uint64_t cnt = 0;
    WithAttr<MakeEdge> edge_01{ labelV1, labelV2 };
    edge_01.Build();
    auto edgeLabel_01 = edge_01.GetResultLabel();
    // 检查属性是否自动继承。
    for (ChildIterator iter{ edgeLabel_01 }; iter.More(); iter.Next()) {
        auto attrs = iter.Value().FindAllAttributes();
        std::cout << attrs[0]->GetValue<StringAttribute>() << std::endl;
    }

    auto boxWithAttr = WithAttr<MakeBox>(5., 5., 5.);
    boxWithAttr.Build();
    auto boxLabel = boxWithAttr.GetResultLabel();
    auto boxFace01 = boxLabel.GetFaceLabels()[0];
    boxFace01.AddAttribute(AttributeTool::MakeAttribute<StringAttribute>("string", "face01"));
    auto boxVertex02 = boxFace01.GetVertexLabels()[1];
    boxVertex02.AddAttribute(AttributeTool::MakeAttribute<StringAttribute>("string", "vertex02"));

    AMCAX::Transformation3 trans;
    trans.SetTranslation(Vector3{ 1., 1., 1. });

    WithAttr<TransformShape> transShape{ trans };
    transShape.Perform(boxLabel);
    auto transBoxLabel = transShape.GetResultLabel();
    auto transBoxFace01 = transBoxLabel.GetFaceLabels()[0];
    // 检查属性是否被自动继承
    auto face01Attr = transBoxFace01.FindAttribute("string");
    std::cout << face01Attr->GetValue<StringAttribute>() << std::endl;
    auto transBoxVertex02 = transBoxFace01.GetVertexLabels()[1];
    auto vertex02Attr = transBoxVertex02.FindAttribute("string");
    std::cout << vertex02Attr->GetValue<StringAttribute>() << std::endl;
}