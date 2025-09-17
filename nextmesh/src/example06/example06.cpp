#include <nextmesh/NMAPIModel.hpp>
#include<occtio/OCCTTool.hpp>

using namespace AMCAX::NextMesh;
using namespace AMCAX;

int main()
{
    // import geometry and get instance of NMBlock
    const std::string filedir = "./data/7.brep";
    AMCAX::TopoShape shape;
    OCCTIO::OCCTTool::Read(shape, filedir);
    NMAPIModel nmapi;
    nmapi.ImportModel({ shape });

    std::vector<NMEntity> ents0, ents1, ents2;
    nmapi.GetEntities(ents0, DimType::D0);
    nmapi.GetEntities(ents1, DimType::D1);
    nmapi.GetEntities(ents2, DimType::D2);

    NMBlock& blockapi = nmapi.GetNMBlock();

    std::vector<Indext> vertexIds;
    std::vector<Indext> edgeIds;
    std::vector<Indext> faceIds;
    std::vector<Indext> blockIds;
    std::vector<Indext> sourceEdges;
    std::vector<Indext> targetEdges;
    std::vector<NMEntity> NMEnts;
    bool success;
    double matchFactor = 0.0;
    NMVector3 moveVector = { 0., .0, .0 };

    // init
    blockapi.Init();

    // edit
    blockIds = { 0 };
    faceIds = { 0, 5 };
    double offset = 0.5;
    blockapi.OSplit(blockIds, faceIds, offset);

    // associate
    faceIds = { 0, 2, 5, 8 };
    NMEnts = { ents2[0] };
    success = blockapi.AssociateFace(faceIds, NMEnts);

    // match
    sourceEdges = { 20 };
    targetEdges = { 0 };
    matchFactor = 0.5;
    success = blockapi.MatchEdgeToEdge(sourceEdges, targetEdges, matchFactor);

    sourceEdges = { 23 };
    targetEdges = { 4 };
    matchFactor = 0.5;
    success = blockapi.MatchEdgeToEdge(sourceEdges, targetEdges, matchFactor);

    sourceEdges = { 25 };
    targetEdges = { 7 };
    matchFactor = 0.5;
    success = blockapi.MatchEdgeToEdge(sourceEdges, targetEdges, matchFactor);

    sourceEdges = { 21 };
    targetEdges = { 1 };
    matchFactor = 0.5;
    success = blockapi.MatchEdgeToEdge(sourceEdges, targetEdges, matchFactor);

    sourceEdges = { 28 };
    targetEdges = { 12 };
    matchFactor = 0.5;
    success = blockapi.MatchEdgeToEdge(sourceEdges, targetEdges, matchFactor);

    sourceEdges = { 30 };
    targetEdges = { 15 };
    matchFactor = 0.5;
    success = blockapi.MatchEdgeToEdge(sourceEdges, targetEdges, matchFactor);

    sourceEdges = { 31 };
    targetEdges = { 17 };
    matchFactor = 0.5;
    success = blockapi.MatchEdgeToEdge(sourceEdges, targetEdges, matchFactor);

    sourceEdges = { 29 };
    targetEdges = { 13 };
    matchFactor = 0.5;
    success = blockapi.MatchEdgeToEdge(sourceEdges, targetEdges, matchFactor);

    // distribution
    SpacingParam param;
    param._type = SpacingType::Length;
    param._startLen = 2;
    param._reverse = false;
    param._parallel = false;
    edgeIds = { 0, 1, 2, 3 };

    blockapi.SetEdgesDistribution(edgeIds, param);

    // Discrete block
    if (blockapi.DiscreteHyperBlock())
    {
        std::cout << "Discrete all blocks." << std::endl;
    }

    // Smooth block
    SmoothParam smoothParam;
    smoothParam.blockIds = { 0 };
    smoothParam._optimizerType = SmoothType::ENERGY_BASED;
    smoothParam._maxIteration = 5;
    smoothParam._relaxationFactor = 0.3;
    blockapi.SmoothBlocks(smoothParam);

    return 0;
}