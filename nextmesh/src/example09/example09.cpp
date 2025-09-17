#include <nextmesh/NMAPIModel.hpp>
#include <nlohmann/json.hpp>
#include<occtio/OCCTTool.hpp>
#include <fstream>

using namespace AMCAX::NextMesh;
using namespace AMCAX;

int main()
{
	const std::string cadstr = "./data/imprint.brep";
	const std::string jsonPath = "./data/param.json";
	NMAPIModel nmapi;
	NMAPIModel::InitLogger();
	TopoShape shape;
	OCCTIO::OCCTTool::Read(shape, cadstr);
	nmapi.ImportModel({ shape });
	std::vector<NMEntity> composite_entitys_D3;
	composite_entitys_D3.push_back(nmapi.GetEntity(DimType::D3, 1));
	composite_entitys_D3.push_back(nmapi.GetEntity(DimType::D3, 2));
	auto cpD3 = nmapi.AddCompositeEntity(composite_entitys_D3, false);
	nlohmann::json paraJ = nlohmann::json::parse(std::ifstream(jsonPath));
	paraJ["MeshSize"][0]["MeshingDim"] = 3;
	paraJ["MeshSize"][0]["SelectedEntities"][0] = nmapi.EntityGetTag(cpD3);
	nmapi.GenerateMesh(paraJ.dump());
	auto meshapi = nmapi.GetMesh();

	OutParams outp{};
	meshapi.Write("./imprint_v.obj", OutFileType::OBJ, outp);
}