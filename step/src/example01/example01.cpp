#include <step/STEPStyledReader.hpp>
#include <step/STEPTool.hpp>
#include <step/STEPWriter.hpp>
#include <topology/TopoExplorer.hpp>
#include <topology/TopoIterator.hpp>
#include <iostream>

void printProductName(const std::shared_ptr<AMCAX::STEP::STEPStyledProduct>& node, int indent = 0)
{
    for (int i = 0; i < indent; ++i) {
        std::cout << "|   ";
        if (node->IsShadow()) {
            std::cout << "SHADOW: " << node->ProductName() << std::endl;
        }
        else {
            std::cout << node->ProductName() << std::endl;
            for (auto& child : node->Children()) {
                printProductName(child, indent + 1);
            }
        }
    }
}

void printSolidName(const std::shared_ptr<AMCAX::STEP::STEPStyledProduct>& node, int indent = 0)
{
    for (size_t i = 0; i < node->ShapesSize(); ++i)
    {
        const auto& origShape = node->ShapeAt(i);
        const auto& props = node->PropertyAt(i);

        for (AMCAX::TopoExplorer SolidExp(origShape, AMCAX::ShapeType::Solid);
            SolidExp.More(); SolidExp.Next())
        {
            const auto& solid = SolidExp.Current();
            auto it = props.find(solid);
            if (it != props.end() && it->second.NameHasValue())
            {
                std::string name = it->second.Name();
                std::cout << '\"' << name << '\"' << std::endl;
            }
        }
    }

    for (auto& child : node->Children())
    {
        printSolidName(child, indent + 1);
    }
}

int main()
{
    std::vector<std::shared_ptr<AMCAX::STEP::STEPStyledProduct>> products;

    AMCAX::STEP::STEPStyledReader reader("./data/bed214T.step");
    reader.SetTargetUnit(AMCAX::STEP::STEPLengthUnit::Presets::METRE);

    bool topo_success = reader.Read();
    if (!topo_success) return -1;

    products = reader.GetProducts();

    for (auto root : products)
    {
        printProductName(root);
        printSolidName(root);
    }

    // 提取整体 Shape
    AMCAX::TopoShape compound = AMCAX::STEP::STEPTool::MakeCompound(products);

    // 将树展开为一维数组
    AMCAX::STEP::STEPTool::FlattenInplace(products);

    AMCAX::STEP::STEPWriter writer("./output.step");
    writer.SetOutputUnit(AMCAX::STEP::STEPLengthUnit::Presets::METRE);
    writer.WriteShapes(products);
    writer.Done();
}
