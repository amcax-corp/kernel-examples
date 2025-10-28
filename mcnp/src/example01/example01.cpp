#include<mcnp/MCNPReader.hpp>
#include<topology/TopoBuilder.hpp>
#include<topology/TopoCompound.hpp>
#include<occtio/OCCTTool.hpp>
#include <af/attribute/AttributeTool.hpp>
#include <iostream>
#include <fstream> 
#include <filesystem>

using namespace AMCAX;
using namespace AMCAX::MCNP;

int main()
{
    MCNPReader reader("./data/LCT001");
    std::vector<Label> labels = reader.Read();
    AMCAX::TopoBuilder builder;
    AMCAX::TopoCompound cmp;
    builder.MakeCompound(cmp);
    for (auto& iter : labels)
    {
        AMCAX::TopoShape  shape = iter.GetShape();
        builder.Add(cmp, shape);
        auto attrs = iter.FindAllAttributes();
        for (auto& attr : attrs)
        {
            int mat = attr->GetValue<AMCAX::Int16Attribute>();
            std::cout << "m: " << mat << "\n";
        }
    }
    std::string file("LCT001.brep");
    std::ofstream mcnp(file);
    AMCAX::OCCTIO::OCCTTool::Write(cmp, mcnp);
}