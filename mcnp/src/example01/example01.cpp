#include<mcnp/MCNPReader.hpp>
#include<topology/TopoBuilder.hpp>
#include<topology/TopoCompound.hpp>
#include<occtio/OCCTTool.hpp>
#include <af/attribute/AttributeTool.hpp>
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

    std::map<int16_t, size_t> mattimes_mat;
    std::map<int16_t, size_t> mattimes_id;
    std::map<double, size_t> mattimes_rho;

    for (auto& iter : labels)
    {
        AMCAX::TopoShape shape = iter.GetShape();
        builder.Add(cmp, shape);
        auto mat = iter.FindAttribute("Material");
        auto cellid = iter.FindAttribute("CellId");
        auto rho = iter.FindAttribute("Density");
        if (mat)
        {
            int16_t Material = mat->GetValue<AMCAX::Int16Attribute>();
            mattimes_mat[Material]++;
            if (mattimes_mat[Material] == 1)
            {
                std::cout << "Material:" << Material << "\n";
            }
        }

        if (rho)
        {
            double Density = rho->GetValue<AMCAX::DoubleAttribute>();
            mattimes_rho[Density]++;
            if (mattimes_rho[Density] == 1)
            {
                std::cout << "Density: " << Density << "\n";
            }
        }

        if (cellid)
        {
            int16_t CellId = cellid->GetValue<AMCAX::Int16Attribute>();
            mattimes_id[CellId]++;
            if (mattimes_id[CellId] == 1)
            {
                std::cout << "CellId: " << CellId << "\n";
            }
        }
    }

    std::string file("LCT001.brep");
    std::ofstream mcnp(file);
    AMCAX::OCCTIO::OCCTTool::Write(cmp, mcnp);
}