#include<iostream>
#include <af/label/LabelTool.hpp>
#include <af/feature/WithAttrModeling.hpp>

using namespace AMCAX;

int main() {
    // 准备一个盒子和一个圆柱体。
    AMCAX::WithAttr<MakeBox> box(5., 5., 5.);
    box.Build();
    auto boxLabel = box.GetResultLabel();

    AMCAX::WithAttr<MakeCylinder> cylinder(5., 10.);
    cylinder.Build();
    auto cylinderLabel = cylinder.GetResultLabel();

    // 给盒子和圆柱体添加属性。
    boxLabel.AddAttribute(AttributeTool::MakeAttribute<StringAttribute>("box", "box"));
    cylinderLabel.AddAttribute(AttributeTool::MakeAttribute<StringAttribute>("cylinder", "cylinder"));

    // 写入文件。
    AMCAX::LabelTool::Write(std::vector<Label>{boxLabel, cylinderLabel}, "shapes.apmr");

    // 从文件读取。
    std::vector<AMCAX::Label> labels;
    AMCAX::LabelTool::Read(labels, "shapes.apmr");
    auto boxLabel2 = labels[0];
    auto cylinderLabel2 = labels[1];
    auto boxAttr = boxLabel2.FindAttribute("box");
    if (boxAttr) {
        std::cout << boxAttr->GetValue<StringAttribute>() << std::endl;
    }
    auto cylinderAttr = cylinderLabel2.FindAttribute("cylinder");
    if (cylinderAttr) {
        std::cout << cylinderAttr->GetValue<StringAttribute>() << std::endl;
    }
    return 0;
}