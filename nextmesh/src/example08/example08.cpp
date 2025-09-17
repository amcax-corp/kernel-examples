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
	std::vector<NMEntity> composite_entitys_D2;
	composite_entitys_D2.push_back(nmapi.GetEntity(DimType::D2, 66));
	composite_entitys_D2.push_back(nmapi.GetEntity(DimType::D2, 67));
	composite_entitys_D2.push_back(nmapi.GetEntity(DimType::D2, 68));
	composite_entitys_D2.push_back(nmapi.GetEntity(DimType::D2, 69));
	composite_entitys_D2.push_back(nmapi.GetEntity(DimType::D2, 70));
	composite_entitys_D2.push_back(nmapi.GetEntity(DimType::D2, 71));
	composite_entitys_D2.push_back(nmapi.GetEntity(DimType::D2, 79));
	composite_entitys_D2.push_back(nmapi.GetEntity(DimType::D2, 80));
	composite_entitys_D2.push_back(nmapi.GetEntity(DimType::D2, 81));
	composite_entitys_D2.push_back(nmapi.GetEntity(DimType::D2, 86));
	composite_entitys_D2.push_back(nmapi.GetEntity(DimType::D2, 87));
	composite_entitys_D2.push_back(nmapi.GetEntity(DimType::D2, 90));
	auto cpD2 = nmapi.AddCompositeEntity(composite_entitys_D2);
	nlohmann::json paraJ = nlohmann::json::parse(std::ifstream(jsonPath));
	paraJ["MeshSize"][0]["MeshingDim"] = 2;
	paraJ["MeshSize"][0]["SelectedEntities"][0] = nmapi.EntityGetTag(cpD2);
	nmapi.GenerateMesh(paraJ.dump());
	auto meshapi = nmapi.GetMesh();

	OutParams outp{};
	meshapi.Write("./imprint_f.obj", OutFileType::OBJ, outp);
}