#include <af/feature/WithAttrModeling.hpp>
#include <af/feature/WithAttrBoolOperation.hpp>
#include<iostream>

using namespace AMCAX;

int main()
{
    TopoShape topoShape = MakeBox(5., 5., 5.);
    WithAttr<TopoShape> shapeWithAttr(topoShape);
    Label boxLabel = shapeWithAttr.GetResultLabel();
    WithAttr<MakeCylinder> cylinder{ 5., 10. };
    cylinder.Build();
    Label cylinderLabel = cylinder.GetResultLabel();

    std::vector<Label> boxFaceLabels = boxLabel.GetFaceLabels();
    std::vector<Label> cylinderFaceLabels = cylinderLabel.GetFaceLabels();
    Label boxFace_1 = boxFaceLabels.front();
    Label boxFace_3 = boxFaceLabels[2];
    Label cylinderFace_1 = cylinderFaceLabels.front();

    auto color = std::make_tuple(1., 0., 0., 1.);
    boxFace_1.AddAttribute(AttributeTool::MakeAttribute<ColorAttribute>("color", color));
    boxFace_1.AddAttribute(AttributeTool::MakeAttribute<Int8Attribute>("int8", int8_t(100)));
    boxFace_1.AddAttribute(AttributeTool::MakeAttribute<Int16Attribute>("int16", int16_t(16)));
    boxFace_1.AddAttribute(AttributeTool::MakeAttribute<Int16Attribute>("guid", int32_t(17)));
    color = std::make_tuple(1., 1., 1., 1.);
    boxFace_3.AddAttribute(AttributeTool::MakeAttribute<ColorAttribute>("color", color));

    color = std::make_tuple(0., 1., 0., 1.);
    cylinderFace_1.AddAttribute(AttributeTool::MakeAttribute<ColorAttribute>("color", color));
    cylinderFace_1.AddAttribute(AttributeTool::MakeAttribute<Int8Attribute>("int8", int8_t(32)));
    cylinderFace_1.AddAttribute(AttributeTool::MakeAttribute<Int16Attribute>("int16", int16_t(-32)));

    WithAttr<BoolBRepCommon> common{ {boxLabel}, {cylinderLabel} };
    common.SetPolicy(AttributeType::INT16_ATTRIBUTE, AttributePolicy::ATTRIBUTE_POLICY_KEEP_TOOL);
    common.Build();
    // 开启级联
    Label commonLabel = common.GetResultLabel(true);

    std::vector<Label> commonFaceLabels = commonLabel.GetFaceLabels();
    for (auto commonFacelabel : commonFaceLabels) {
        if (auto foundAttr = commonFacelabel.FindAttribute("color"); foundAttr) {
            auto [r, g, b, a] = foundAttr->GetValue<ColorAttribute>();
            std::cout << "r = " << r << ", g = " << g << ", b = " << b << ", a = " << a << std::endl;
        }
        if (auto foundAttr = commonFacelabel.FindAttribute("int8"); foundAttr) {
            std::cout << foundAttr->GetValue<Int8Attribute>() << std::endl;
        }
        if (auto foundAttr = commonFacelabel.FindAttribute("int16"); foundAttr) {
            std::cout << foundAttr->GetValue<Int16Attribute>() << std::endl;
        }
        if (auto foundAttr = commonFacelabel.FindAttribute("guid"); foundAttr) {
            std::cout << foundAttr->GetValue<Int16Attribute>() << std::endl;
        }
    }

    color = std::make_tuple(0., 1., 1., 1.);
    // 触发级联更新
    boxFace_1.UpdateAttribute(AttributeTool::MakeAttribute<ColorAttribute>("color", color));

    for (auto commonFacelabel : commonFaceLabels) {
        if (auto foundAttr = commonFacelabel.FindAttribute("color"); foundAttr) {
            auto [r, g, b, a] = foundAttr->GetValue<ColorAttribute>();
            std::cout << "r = " << r << ", g = " << g << ", b = " << b << ", a = " << a << std::endl;
        }
        if (auto foundAttr = commonFacelabel.FindAttribute("int8"); foundAttr) {
            std::cout << foundAttr->GetValue<Int8Attribute>() << std::endl;
        }
        if (auto foundAttr = commonFacelabel.FindAttribute("int16"); foundAttr) {
            std::cout << foundAttr->GetValue<Int16Attribute>() << std::endl;
        }
        if (auto foundAttr = commonFacelabel.FindAttribute("guid"); foundAttr) {
            std::cout << foundAttr->GetValue<Int16Attribute>() << std::endl;
        }
    }
    return 0;
}