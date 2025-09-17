# Mesh Size Control Example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example provides detailed configuration methods for various local size fields in mesh generation to control mesh sizes. The specific implementations are as follows:

	1. Use AMCAX::NextMesh::NMAPIModel::InitLogger() to configure the log format.
	
	2. Use AMCAX::NextMesh::NMAPIModel::ImportModel() to import TopoShape.
	
	3. Use AMCAX::NextMesh::NMAPIModel::GenerateMesh() to generate a mesh based on the JSON string (mesh generation control parameters).
	
	4. Use AMCAX::NextMesh::NMAPIModel::GetMesh() to obtain the generated mesh API.
	
	5. Use AMCAX::NextMesh::NMAPIModel::CreatePhysicalSet() to define a set of faces.
	
	6. Use AMCAX::NextMesh::NMAPIModel::GetEntitiesInPhysicalSet() to retrieve the entities within a specified physical set.
	
	7. Use AMCAX::NextMesh::NMAPIModel::GetPhysicalSets() to retrieve all physical sets in the specified dimension.
	
	8. Use AMCAX::NextMesh::NMMesh::Write() to output the mesh file.


The generated mesh model is shown in the figure:

<div align = center><img src="https://s2.loli.net/2025/03/27/75yzeE6NUGVZfmW.png" width="400" height="300"></div>

<div align = center><img src="https://s2.loli.net/2025/03/27/OQ5CbIBiDdJvezg.png" width="400" height="300"></div>

<div align = center><img src="https://s2.loli.net/2025/03/27/xcijdZu7GVqM1fS.png" width="400" height="300"></div>

<div align = center><img src="https://s2.loli.net/2025/03/27/nDkvZFsRmfPzqdt.png" width="400" height="300"></div>

<div align = center><img src="https://s2.loli.net/2025/03/27/DtaglXPC4mMKsYe.png" width="400" height="300"></div>

<div align = center><img src="https://s2.loli.net/2025/03/27/MBTCNh3oOt7r8G9.png" width="400" height="300"></div>

<div align = center><img src="https://s2.loli.net/2025/03/27/lkbW3pNLFhoUyxZ.png" width="400" height="300"></div>

<div align = center><img src="https://s2.loli.net/2025/03/27/SxT5E2H6IhjgfkR.png" width="400" height="300"></div>

<div align = center><img src="https://s2.loli.net/2025/03/27/kniBWN9GcC3j2Od.png" width="400" height="300"></div>