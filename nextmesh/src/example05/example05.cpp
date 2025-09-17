#include <fstream>
#include <nlohmann/json.hpp>
#include <nextmesh/NMAPIModel.hpp>
#include<occtio/OCCTTool.hpp>
#include <set>

using namespace AMCAX::NextMesh;

void GenMesh()
{
	const std::string jsonPath = "./data/1.json";

	NMAPIModel::InitLogger();

	NMAPIModel nmapi;

	AMCAX::TopoShape shape;
	AMCAX::OCCTIO::OCCTTool::Read(shape, "./data/box.brep");
	std::vector<NMShape>shapes = { shape };
	nmapi.ImportModel(shapes);

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

	meshapi.Write("result1.vtk", OutFileType::VTK);
	meshapi.Write("result1.obj", OutFileType::OBJ);
	meshapi.WriteGmsh4("result1.msh", false, true);
}

int main()
{
	GenMesh();
	return 0;
}