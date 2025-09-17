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
	TopoShape shape;
	OCCTIO::OCCTTool::Read(shape, cadstr);
	nmapi.ImportModel({ shape });

	// Composite edges
	std::vector<NMEntity> composite_entitys_D11;
	composite_entitys_D11.push_back(nmapi.GetEntity(DimType::D1, 210));
	composite_entitys_D11.push_back(nmapi.GetEntity(DimType::D1, 211));
	auto cpD11 = nmapi.AddCompositeEntity(composite_entitys_D11);

	// Composite faces
	std::vector<NMEntity> composite_entitys_D21;
	composite_entitys_D21.push_back(nmapi.GetEntity(DimType::D2, 66));
	composite_entitys_D21.push_back(nmapi.GetEntity(DimType::D2, 67));
	composite_entitys_D21.push_back(nmapi.GetEntity(DimType::D2, 68));
	composite_entitys_D21.push_back(nmapi.GetEntity(DimType::D2, 69));
	composite_entitys_D21.push_back(nmapi.GetEntity(DimType::D2, 70));
	composite_entitys_D21.push_back(nmapi.GetEntity(DimType::D2, 71));
	composite_entitys_D21.push_back(nmapi.GetEntity(DimType::D2, 79));
	composite_entitys_D21.push_back(nmapi.GetEntity(DimType::D2, 80));
	composite_entitys_D21.push_back(nmapi.GetEntity(DimType::D2, 81));
	composite_entitys_D21.push_back(nmapi.GetEntity(DimType::D2, 86));
	composite_entitys_D21.push_back(nmapi.GetEntity(DimType::D2, 87));
	composite_entitys_D21.push_back(nmapi.GetEntity(DimType::D2, 90));
	auto cpD21 = nmapi.AddCompositeEntity(composite_entitys_D21, false);

	// Composite edges
	std::vector<NMEntity> composite_entitys_D12;
	composite_entitys_D12.push_back(nmapi.GetEntity(DimType::D1, 157));
	composite_entitys_D12.push_back(nmapi.GetEntity(DimType::D1, 158));
	auto cpD12 = nmapi.AddCompositeEntity(composite_entitys_D12);

	// Composite faces
	std::vector<NMEntity> composite_entitys_D22;
	composite_entitys_D22.push_back(nmapi.GetEntity(DimType::D2, 33));
	composite_entitys_D22.push_back(nmapi.GetEntity(DimType::D2, 34));
	composite_entitys_D22.push_back(nmapi.GetEntity(DimType::D2, 35));
	composite_entitys_D22.push_back(nmapi.GetEntity(DimType::D2, 36));
	auto cpD22 = nmapi.AddCompositeEntity(composite_entitys_D22);

	// Composite faces
	std::vector<NMEntity> composite_entitys_D23;
	composite_entitys_D23.push_back(cpD21);
	composite_entitys_D23.push_back(cpD22);
	auto cpD23 = nmapi.AddCompositeEntity(composite_entitys_D23);

	// remove comosite entity
	/*
	std::vector<NMEntity> remove_entitys;
	remove_entitys.push_back(cpD11);
	remove_entitys.push_back(cpD21);
	remove_entitys.push_back(cpD12);
	remove_entitys.push_back(cpD22);
	remove_entitys.push_back(cpD23);
	nmapi.RemoveEntities(remove_entitys);
	*/

	nlohmann::json paraJ = nlohmann::json::parse(std::ifstream(jsonPath));
	paraJ["MeshSize"][0]["SelectedEntities"][0] = nmapi.EntityGetTag(cpD23);

	nmapi.GenerateMesh(paraJ.dump());
	auto meshapi = nmapi.GetMesh();

	OutParams outp{};
	meshapi.Write("./zhijiav1.obj", OutFileType::OBJ, outp);

}