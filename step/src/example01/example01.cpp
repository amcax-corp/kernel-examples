#include <step/StepReader.hpp>
#include <step/StepWriter.hpp>
#include <step/StepDataTool.hpp>

#include <topology/TopoIterator.hpp>

#include <iostream>

void printProductName(const std::shared_ptr<AMCAX::STEP::StepData> node, int indent = 0)
{
    for (int i = 0; i < indent; ++i)
    {
        std::cout << "|   ";
    }
    std::cout << node->ProductName() << std::endl;
    for (const std::shared_ptr<AMCAX::STEP::StepData> child : node->Children())
    {
        printProductName(child, indent + 1);
    }
}

void printSubName(const std::shared_ptr<AMCAX::STEP::StepData> node, int indent = 0)
{
    for (int i = 0; i < indent; ++i)
    {
        std::cout << "|   ";
    }
    std::unordered_map<AMCAX::TopoShape, std::string> partname = node->PartName();
    for (const AMCAX::TopoShape& shape : node->Shapes())
    {
        for (AMCAX::TopoIterator iter(shape); iter.More(); iter.Next())
        {
            if (auto it = partname.find(iter.Value()); it != partname.end())
            {
                std::cout << it->second << std::endl;
            }
            else
            {
                std::cout << "No PartName" << std::endl;
            }
        }
    }

    for (const std::shared_ptr<AMCAX::STEP::StepData> child : node->Children())
    {
        printSubName(child, indent + 1);
    }
}

int main()
{
    AMCAX::STEP::StepDataList shapes;

    AMCAX::STEP::StepReader reader("./data/bed214T.step");

    reader.SetUnit(AMCAX::STEP::StepLengthUnit::PresetLengthUnit::METRE);

    bool topo_success = reader.Read();
    if (!topo_success)
    {
        return -1;
    }

    shapes = reader.GetShapes();

    for (std::shared_ptr<AMCAX::STEP::StepData> root : shapes)
    {
        printProductName(root);
        printSubName(root);
    }

    AMCAX::STEP::StepDataList flatten = AMCAX::STEP::StepDataTool::Flatten(shapes);

    AMCAX::STEP::StepWriter writer("./output.step");
    writer.SetUnit(AMCAX::STEP::StepLengthUnit::PresetLengthUnit::METRE);
    writer.Init();
    writer.WriteShapes(shapes);
    writer.Done();
}
