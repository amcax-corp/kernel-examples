﻿#include <step/mesh/StepMeshReader.hpp>
#include <iostream>
#include <common/IndexSet.hpp>
#include <topology/TopoExplorerTool.hpp>
#include "example02.h"
#include <step/mesh/StepMesh.hpp>
#include <vector>
#include <topomesh/BRepMeshIncrementalMesh.hpp>
#include <modeling/MakeShapeTool.hpp>
#include <mesh/io/STLWriter.hpp>
#include <mesh/io/IOOptions.hpp>


template<typename Traits>
std::shared_ptr<AMCAX::STEP::StepMeshData<Traits>>
_ApplyTrsfInplace(std::shared_ptr<AMCAX::STEP::StepMeshData<Traits>>& orig, std::vector<AMCAX::TopoLocation>& trsfStack)
{
	trsfStack.push_back(orig->Transformation());
	for (auto& shape : orig->Shapes())
	{
		for (auto revit = trsfStack.rbegin(); revit != trsfStack.rend(); ++revit)
		{
			shape.Move(*revit);
		}
	}
	for (auto& child : orig->Children())
	{
		_ApplyTrsfInplace<Traits>(child, trsfStack);
	}
	trsfStack.pop_back();
	orig->Transformation() = AMCAX::TopoLocation();
	return orig;
}
int main()
{
	const std::string INPUT = "./data/bed214T.step";
	using TriSoupTraits = AMCAX::Meshing::Mesh::TriSoupTraits_Coord;
	using Points = typename TriSoupTraits::Points;
	using Triangles = typename TriSoupTraits::Triangles;
	using MeshReader = AMCAX::STEP::StepMeshReader<TriSoupTraits>;
	using MeshDataList = AMCAX::STEP::StepMeshDataList<TriSoupTraits>;
	using MeshDataPtr = MeshDataList::value_type;
	MeshReader reader(INPUT);
	reader.Read();
	auto& shapes = reader.GetShapes();
	for (auto& shape : shapes)
	{
		std::vector<AMCAX::TopoLocation> trsfStack;
		_ApplyTrsfInplace<TriSoupTraits>(shape, trsfStack);
	}
	reader.ToMesh();
	std::vector<std::vector<AMCAX::STEP::StepMesh<TriSoupTraits>>> meshes;
	std::function<void(
		std::shared_ptr<AMCAX::STEP::StepMeshData<TriSoupTraits>>&)>
		func = [&](std::shared_ptr<AMCAX::STEP::StepMeshData<TriSoupTraits>>& meshdata)
		{
			for (const auto& cur : meshdata->Meshes())
			{
				meshes.push_back(cur);
			}
			for (auto& ptr : meshdata->Children())
			{
				func(ptr);
			}
		};
	for (auto& sp : shapes)
	{
		func(sp);
	}
	AMCAX::Meshing::Mesh::IOOptions io_options;
	io_options.vertex_has_point = true;
	io_options.face_has_normal = false;
	io_options.stl_binary = false;
	Points points1, result_points;
	Triangles triangles1, result_triangles;
	AMCAX::Meshing::Mesh::STLWriter<AMCAX::Meshing::Mesh::TriSoupTraits_Coord> stl_writer;
	int nvcount = 0;
	for (auto& meshvec : meshes)
	{
		for (auto& m : meshvec)
		{
			points1.insert(points1.end(), m.MPoints().begin(), m.MPoints().end());
			Triangles trianglestmp;
			trianglestmp.reserve(m.MTriangles().size());
			for (auto& tri : m.MTriangles())
			{
				auto tritmp = tri;
				tritmp.SetX(tri.x() + nvcount);
				tritmp.SetY(tri.y() + nvcount);
				tritmp.SetZ(tri.z() + nvcount);
				trianglestmp.emplace_back(tritmp);
			};
			triangles1.insert(triangles1.end(), trianglestmp.begin(),
				trianglestmp.end());
			nvcount += m.MPoints().size();
		}
	}
	stl_writer.m_points = points1;
	stl_writer.m_triangles = triangles1;
	stl_writer.write("output.stl", io_options, 10);
}