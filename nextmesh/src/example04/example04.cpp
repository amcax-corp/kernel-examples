#include <fstream>
#include <nlohmann/json.hpp>
#include <nextmesh/NMAPIModel.hpp>
#include <set>
#include<occtio/OCCTTool.hpp>

using namespace AMCAX::NextMesh;

void Quality()
{
    const std::string jsonPath = "./data/test.json";

    NMAPIModel nmapi;
    NMAPIModel::InitLogger();

    AMCAX::TopoShape shape;
    AMCAX::OCCTIO::OCCTTool::Read(shape, "./data/test.brep");
    std::vector<NMShape>shapes = { shape };
    nmapi.ImportModel(shapes);

    std::vector<NMEntity> ent_d2, ent_d3;
    nmapi.GetEntities(ent_d2, DimType::D2);
    nmapi.GetEntities(ent_d3, DimType::D3);

    nlohmann::json paraJ = nlohmann::json::parse(std::ifstream(jsonPath));
    nmapi.GenerateMesh(paraJ.dump());
    auto meshapi = nmapi.GetMesh();

    for (auto entf : ent_d2)
    {
        auto ec = meshapi.EntityGetElementCount(entf);
        for (size_t i = 0; i < ec; i++)
        {
            auto elem = meshapi.EntityGetElementByIndex(entf, i);
            double quality = 1.0;
            if (meshapi.ElementGetType(elem) == ElemType::Tri_3)
            {
                quality = meshapi.ComputeQuality(
                    elem,
                    QualityType::SkewnessByVolume,
                    CommercialSoftware::Fluent
                );
            }
        }
    }

    for (auto entf : ent_d3)
    {
        auto ec = meshapi.EntityGetElementCount(entf);
        for (size_t i = 0; i < ec; i++)
        {
            auto elem = meshapi.EntityGetElementByIndex(entf, i);
            double quality = 1.0;
            if (meshapi.ElementGetType(elem) == ElemType::Tet_4)
            {
                quality = meshapi.ComputeQuality(
                    elem,
                    QualityType::SkewnessByVolume,
                    CommercialSoftware::Fluent
                );
            }
        }
    }
}


int main()
{
    Quality();
    return 0;
}