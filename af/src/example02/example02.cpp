#include <iostream>
#include <af/attribute/Attribute.hpp>
#include <af/feature/WithAttrModeling.hpp>
#include <af/feature/WithAttrBoolOperation.hpp>

using namespace AMCAX;

int main()
{
    auto boxWithAttr = WithAttr<MakeBox>(5., 5., 10.);
    boxWithAttr.Build();
    auto box = boxWithAttr.GetResultLabel();
    auto boxFaces = box.GetFaceLabels();
    uint64_t cnt = 1;
    for (auto boxFace : boxFaces) {
        boxFace.AddAttribute(AttributeTool::MakeAttribute<StringAttribute>("string", "box1_" + std::to_string(cnt++)));
    }

    auto boxWithAttr_ = WithAttr<MakeBox>(5., 5., 10.);
    boxWithAttr_.Build();
    auto box_ = boxWithAttr_.GetResultLabel();
    auto boxFaces_ = box_.GetFaceLabels();
    cnt = 1;
    for (auto boxFace : boxFaces_) {
        boxFace.AddAttribute(AttributeTool::MakeAttribute<StringAttribute>("string", "box2_" + std::to_string(cnt++)));
    }

    auto cylinderWithAttr = WithAttr<MakeCylinder>(5., 10.);
    cylinderWithAttr.Build();
    auto cylnder = cylinderWithAttr.GetResultLabel();
    auto cylinderFaces = cylnder.GetFaceLabels();
    cnt = 1;
    for (auto cylFace : cylinderFaces) {
        cylFace.AddAttribute(AttributeTool::MakeAttribute<StringAttribute>("string", "cyl_" + std::to_string(cnt++)));
    }
    WithAttr<BoolBRepFuse> fuseKeepTool{ {box,  box_}, {cylnder} };
    // 注：此处也可使用 StringAttribute::policy = AttributePolicy::ATTRIBUTE_POLICY_KEEP_TOOL
    // 但是，SetPolicy 设定的策略优先级更高。
    fuseKeepTool.SetPolicy(AttributeType::STRING_ATTRIBUTE, AttributePolicy::ATTRIBUTE_POLICY_KEEP_TOOL);
    fuseKeepTool.Build();
    // 开启级联追踪
    auto fuseLabel = fuseKeepTool.GetResultLabel(true);
    auto fuseFaces = fuseLabel.GetFaceLabels();
    auto boxFace1 = boxFaces[0];
    auto cylFace2 = cylinderFaces[1];
    // 注：可验证布尔结果的第一个面同时从box的第六个面，box_的第六个面和cyl第二个面modified过来，存在属性冲突。
    auto fuseFace_1 = fuseFaces[0];
    if (auto attr = fuseFace_1.FindAttribute("string"); attr) {
        // 由属性策略是 ATTRIBUTE_POLICY_KEEP_TOOL，此输出为 cyl_2
        std::cout << attr->GetValue<StringAttribute>() << std::endl;
    }

    cylFace2.UpdateAttribute(AttributeTool::MakeAttribute<StringAttribute>("string", "CYL_2"));
    if (auto attr = fuseFace_1.FindAttribute("string"); attr) {
        // 级联更新，此输出为 CYL_2
        std::cout << attr->GetValue<StringAttribute>() << std::endl;
    }
}