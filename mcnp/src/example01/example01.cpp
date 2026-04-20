#include<mcnp/MCNPReader.hpp>
#include<topology/TopoBuilder.hpp>
#include<topology/TopoCompound.hpp>
#include<occtio/OCCTTool.hpp>
#include <af/attribute/AttributeTool.hpp>
#include <af/attribute/ArrayAttribute.hpp>
#include <iostream>
#include <fstream> 
#include <filesystem>
#include <map>

using namespace AMCAX;
using namespace AMCAX::MCNP;

int main()
{
    MCNPReader reader("./data/LCT001");
    std::vector<Label> labels = reader.Read();
    AMCAX::TopoBuilder builder;
    AMCAX::TopoCompound cmp;
    builder.MakeCompound(cmp);

    for (auto& label : labels)
    {
        AMCAX::TopoShape shape = label.GetShape();
        builder.Add(cmp, shape);
        auto mat = label.FindAttribute("Material");
        auto cellid = label.FindAttribute("CellId");
        auto rho = label.FindAttribute("Density");
        auto zaids_attr = label.FindAttribute("MaterialZAIDs");
        auto fractions_attr = label.FindAttribute("MaterialFractions");
        auto sabids_attr = label.FindAttribute("ThermalSABIDs");
        if (mat)
        {
            int16_t material = mat->GetValue<AMCAX::Int16Attribute>();
            std::cout << "Material: " << material << "\n";
        }
        if (rho)
        {
            double density = rho->GetValue<AMCAX::DoubleAttribute>();
            std::cout << "Density: " << density << "\n";
        }
        if (cellid)
        {
            int16_t cellId = cellid->GetValue<AMCAX::Int16Attribute>();
            std::cout << "CellId: " << cellId << "\n";
        }
        if (zaids_attr && fractions_attr)
        {
            auto zaids = std::static_pointer_cast<ArrayAttribute<std::string>>(zaids_attr);
            auto fractions = std::static_pointer_cast<ArrayAttribute<double>>(fractions_attr);
            const auto count = std::min(zaids->Size(), fractions->Size());
            for (size_t i = 0; i < count; ++i)
            {
                std::cout << "ZAID:Fraction: " << zaids->Get(i) << ": " << std::abs(fractions->Get(i)) << std::endl;
            }
        }
        if (sabids_attr)
        {
            auto sabids = std::static_pointer_cast<ArrayAttribute<std::string>>(sabids_attr);
            for (size_t i = 0; i < sabids->Size(); ++i)
            {
                std::cout << "SABID: " << sabids->Get(i) << std::endl;
            }
        }
    }

    std::string file("LCT001.brep");
    std::ofstream mcnp(file);
    AMCAX::OCCTIO::OCCTTool::Write(cmp, mcnp);
}