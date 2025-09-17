#include <fstream>
#include <nlohmann/json.hpp>
#include <nextmesh/NMAPIModel.hpp>
#include <set>
#include <occtio/OCCTTool.hpp>

using namespace AMCAX::NextMesh;

void GenMesh()
{
    const std::string jsonPath = "./data/mesh_para-mesh000.json";

    NMAPIModel::InitLogger();

    NMAPIModel nmapi;

    AMCAX::TopoShape shape;
    AMCAX::OCCTIO::OCCTTool::Read(shape, "./data/qiuwotaojian.brep");
    std::vector<NMShape>shapes = { shape };
    nmapi.ImportModel(shapes);

    nlohmann::json paraJ = nlohmann::json::parse(std::ifstream(jsonPath));

    nmapi.GenerateMesh(paraJ.dump());

    auto meshapi = nmapi.GetMesh();

    for (DimType dim : {DimType::D0, DimType::D1, DimType::D2, DimType::D3})
    {
        std::vector<NMEntity> etVec;

        nmapi.GetEntities(etVec, dim);
        for (auto ent : etVec)
        {
            auto eTag = nmapi.EntityGetTag(ent);
            auto dim = nmapi.EntityGetDim(ent);

            std::vector<NMEntity> parentVec;
            nmapi.GetParentAdjacentEntities(parentVec, ent);


            std::vector<NMEntity>    childVec;
            std::vector<Orientation> ories;
            nmapi.GetChildAdjacentEntities(childVec, ories, ent);


            auto entElemNum = meshapi.EntityGetElementCount(ent);
            for (size_t i = 0; i < entElemNum; i++)
            {
                auto elem = meshapi.EntityGetElementByIndex(ent, i);
            }

            auto entNodeNum = meshapi.EntityGetNodeCount(ent);
            for (size_t i = 0; i < entNodeNum; i++)
            {
                auto node = meshapi.EntityGetNodeByIndex(ent, i);
            }
        }
    }

    NMPoint3 pmin, pmax;
    nmapi.GetBBox(pmin, pmax);

    auto elemTotalNum = meshapi.GetElementCount();
    for (size_t i = 0; i < elemTotalNum; i++)
    {

        auto elem = meshapi.GetElementByIndex(i);

        auto elemId = meshapi.ElementGetID(elem);
        auto elemType = meshapi.ElementGetType(elem);
        auto nodeCount = meshapi.ElementGetNodeCount(elem);

        for (size_t in = 0; in < nodeCount; in++)
        {

            auto   node = meshapi.ElementGetNode(elem, in);

            auto   nodeId = meshapi.NodeGetID(node);
            auto   nodeEnt = meshapi.NodeGetEntity(node);
            auto   nodePos = meshapi.NodeGetPosition(node);

            if (nmapi.EntityGetDim(nodeEnt) == DimType::D1 ||
                nmapi.EntityGetDim(nodeEnt) == DimType::D2)
                double u = meshapi.NodeGetFirstParameter(node);

            if (nmapi.EntityGetDim(nodeEnt) == DimType::D2)
                double v = meshapi.NodeGetSecondParameter(node);
        }
    }

    auto nodeTotalNum = meshapi.GetNodeCount();
    for (size_t i = 0; i < nodeTotalNum; i++)
    {
        auto node = meshapi.GetNodeByIndex(i);
    }

    nmapi.CreatePhysicalSet(DimType::D2, { 1, 2 }, "inlet");
    nmapi.CreatePhysicalSet(DimType::D2, { 3, 4 }, "outlet");
    nmapi.CreatePhysicalSet(DimType::D2, { 5 }, "symmetry");

    std::vector<EntTag> entTags;
    nmapi.GetEntitiesInPhysicalSet(entTags, DimType::D2, "outlet");

    std::set<std::string> pNames;
    nmapi.GetPhysicalSets(pNames, DimType::D2);

    meshapi.Write("result.vtk", OutFileType::VTK);
    meshapi.Write("result.obj", OutFileType::OBJ);
    meshapi.Write("result.msh", OutFileType::FLUENT_MSH);
    meshapi.WriteGmsh4("result.msh", false, true);
}

int main()
{
    GenMesh();
    return 0;
}