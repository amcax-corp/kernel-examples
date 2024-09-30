#include <fstream>
#include <nlohmann/json.hpp>
#include <nextmesh/NMAPIModel.hpp>
#include <set>

using namespace AMCAX::NextMesh;

void GenMesh()
{
    const std::string cadstr = "./data/1.stp";

    const std::string jsonPath = "./data/1.json";

    NMAPIModel::InitLogger();

    NMAPIModel nmapi;

    nmapi.ImportModel(cadstr);

    nlohmann::json paraJ = nlohmann::json::parse(std::ifstream(jsonPath));

    nmapi.GenerateMesh(paraJ.dump());

    auto meshapi = nmapi.GetMesh();

    for (DimType dim : {DimType::D0, DimType::D1, DimType::D2, DimType::D3})
    {
        std::vector<NMEntity> etVec;

        nmapi.GetEntities(etVec, dim);
        printf("dim %d, etag size %zu\n", dim, etVec.size());
        for (auto ent : etVec)
        {
            auto eTag = nmapi.EntityGetTag(ent);
            auto dim = nmapi.EntityGetDim(ent);

            std::vector<ElemType> typeVec;

            meshapi.GetEntityElementTypes(typeVec, ent);
            printf("- dim %d, etag %u, ctype size %zu\n", dim, eTag,
                typeVec.size());
            for (auto cType : typeVec)
            {
                std::vector<Indext> nodeVec;

                meshapi.GetNodesByElementType(nodeVec, cType, ent);
                printf("-- dim %d, etag %u, ctype %u, node size %zu\n", dim, eTag,
                    (int)cType, nodeVec.size());
            }

            std::vector<NMEntity> parentVec;
            nmapi.GetParentAdjacentEntities(parentVec, ent);
            printf("- parent dim %d, etag %u, parentSize %zu\n", dim, eTag,
                parentVec.size());
            if (parentVec.empty())
            {
                for (auto pent : parentVec)
                {
                    printf("%u ", nmapi.EntityGetTag(pent));
                }
                printf("\n");
            }

            std::vector<NMEntity>    childVec;
            std::vector<Orientation> ories;
            nmapi.GetChildAdjacentEntities(childVec, ories, ent);
            printf("- child dim %d, etag %u, childSize %zu\n", dim, eTag,
                childVec.size());
            if (childVec.size() > 0)
            {
                for (auto& cent : childVec)
                {
                    printf("%u ", nmapi.EntityGetTag(cent));
                }
                printf("\n");
            }
            printf("\n");
        }
    }

    NMPoint3 pmin, pmax;

    nmapi.GetBBox(pmin, pmax);

    std::vector<NMPoint3> pts;
    meshapi.GetAllNodes(pts);

    nmapi.CreatePhysicalSet(DimType::D2, { 1, 2 }, "inlet");
    nmapi.CreatePhysicalSet(DimType::D2, { 3, 4 }, "outlet");
    nmapi.CreatePhysicalSet(DimType::D2, { 5 }, "symmetry");

    std::vector<EntTag> entTags;
    nmapi.GetEntitiesInPhysicalSet(entTags, DimType::D2, "outlet");

    std::set<std::string> pNames;
    nmapi.GetPhysicalSets(pNames, DimType::D2);

    meshapi.Write("flmsh.vtk", OutFileType::VTK);
    meshapi.Write("flmsh.obj", OutFileType::OBJ);
}

int main()
{
    GenMesh();
    return 0;
}