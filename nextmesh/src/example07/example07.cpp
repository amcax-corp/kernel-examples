#include <nextmesh/NMAPIModel.hpp>
#include <nlohmann/json.hpp>
#include<occtio/OCCTTool.hpp>
#include <fstream>

using namespace AMCAX::NextMesh;
using namespace AMCAX;

int main()
{
	const std::string cadstr = "./data/zhijiav1.brep";
	const std::string jsonPath = "./data/param.json";
	NMAPIModel nmapi;
	NMAPIModel::InitLogger();
	AMCAX::TopoShape shape;
	OCCTIO::OCCTTool::Read(shape, cadstr);
	nmapi.ImportModel({ shape });
	std::vector<NMEntity> composite_entitys_D1;
	composite_entitys_D1.push_back(nmapi.GetEntity(DimType::D1, 210));
	composite_entitys_D1.push_back(nmapi.GetEntity(DimType::D1, 211));
	auto cpD1 = nmapi.AddCompositeEntity(composite_entitys_D1);
	nlohmann::json paraJ = nlohmann::json::parse(std::ifstream(jsonPath));
	paraJ["MeshSize"][0]["MeshingDim"] = 1;
	paraJ["MeshSize"][0]["SelectedEntities"][0] = nmapi.EntityGetTag(cpD1);
	nmapi.GenerateMesh(paraJ.dump());
	auto meshapi = nmapi.GetMesh();

	OutParams outp{};
	meshapi.Write("./imprint_e.obj", OutFileType::OBJ, outp);
}