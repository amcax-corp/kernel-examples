#include <nextmesh/NMAPIModel.hpp>
#include <nlohmann/json.hpp>
#include<occtio/OCCTTool.hpp>
#include<step/STEPTool.hpp>
#include <fstream>

using namespace AMCAX::NextMesh;
using namespace AMCAX;

int main()
{
	const std::string jsonPath = "./data/Canard.json";
	std::string pts_path = "./data/Canard_repair_fluid.step";

	AMCAX::TopoShape step_shape;
	AMCAX::STEP::STEPTool::Read(step_shape, pts_path);

	NMAPIModel nmapi;
	NMAPIModel::InitLogger();
	nmapi.ImportModel({ step_shape });
	nlohmann::json paraJ = nlohmann::json::parse(std::ifstream(jsonPath));
	nmapi.GenerateMesh(paraJ.dump());
	auto meshapi = nmapi.GetMesh();
	meshapi.Write("result", OutFileType::VTK);
}