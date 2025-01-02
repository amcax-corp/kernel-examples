#include <fstream>
#include <nlohmann/json.hpp>
#include <nextmesh/NMAPIModel.hpp>
#include <set>

using namespace AMCAX::NextMesh;

void GenMesh()
{
    const std::string cadstr = "./data/doubleInnerBoundary.step";

    const std::string jsonPath = "./data/1.json";

    NMAPIModel::InitLogger();

    NMAPIModel nmapi;

    nmapi.ImportModel(cadstr);

    nlohmann::json paraJ = nlohmann::json::parse(std::ifstream(jsonPath));

    nmapi.GenerateMesh(paraJ.dump());

    auto meshapi = nmapi.GetMesh();


    nmapi.CreatePhysicalSet(DimType::D2, { 1, 2 }, "inlet");
    nmapi.CreatePhysicalSet(DimType::D2, { 3, 4 }, "outlet");
    nmapi.CreatePhysicalSet(DimType::D2, { 5 }, "symmetry");

    std::vector<EntTag> entTags;
    nmapi.GetEntitiesInPhysicalSet(entTags, DimType::D2, "outlet");

    std::set<std::string> pNames;
    nmapi.GetPhysicalSets(pNames, DimType::D2);

    meshapi.Write("flmsh1.vtk", OutFileType::VTK);
    meshapi.Write("flmsh1.obj", OutFileType::OBJ);
}

int main()
{
    GenMesh();
    return 0;
}