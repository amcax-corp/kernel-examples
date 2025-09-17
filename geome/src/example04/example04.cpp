#include <iostream>
#include <vector>
#include <string>
#include <filesystem> 
#include <modeling/MakeShapeTool.hpp>
#include <modeling/MakeSolid.hpp>
#include <topology/TopoCast.hpp>
#include <topology/TopoSolid.hpp>
#include <topology/TopoShell.hpp>
#include <topology/TopoExplorerTool.hpp>
#include <topology/TopoTool.hpp>
#include <shapeEdit/EdgeEditor.hpp>
#include <shapeEdit/FaceEditor.hpp>
#include <shapeEdit/DetectTool.hpp>
#include <occtio/OCCTTool.hpp>
#include <step/STEPTool.hpp>
#include <fillet/MakeFillet.hpp>
#include <healing/ShapeFixTool.hpp>
#include <boolean/BoolBRepDefeaturing.hpp>


using namespace std;
using namespace AMCAX;
using namespace GeomE;

// Read
bool readtopo(TopoShape& s, const string& mfile)
{
	if (!std::filesystem::exists(mfile)) {
		cout << "File not found!" << endl;
		return false;
	}
	string suffix = mfile.substr(mfile.find_last_of('.') + 1);
	std::transform(suffix.begin(), suffix.end(), suffix.begin(), [](unsigned char c) {
		return std::tolower(c);
		});
	// Check the file extension. If it's .stp or .step, call StepDataTool; if it's .brep, call OCCTTool
	if (suffix == "stp" || suffix == "step") {
		return STEP::STEPTool::Read(s, mfile);
	}
	else if (suffix == "brep") {
		return OCCTIO::OCCTTool::Read(s, mfile);
	}
	else {
		std::cout << "Unsupported file format!" << endl;
		return false;
	}
}

// Write
bool writetopo(const TopoShape& s, const string& outfile)
{
	string suffix = outfile.substr(outfile.find_last_of('.') + 1);
	transform(suffix.begin(), suffix.end(), suffix.begin(), [](unsigned char c) {
		return tolower(c);
		});
	// Check the file extension. If it's .stp or .step, call StepDataTool; if it's .brep, call OCCTTool
	if (suffix == "stp" || suffix == "step")
		return STEP::STEPTool::Write(s, outfile);
	else if (suffix == "brep")
		return OCCTIO::OCCTTool::Write(s, outfile);
	else {
		cout << "Unsupported output file format: " << suffix << endl;
		return false;
	}
}

TopoShape combineFaces(TopoShape& shape)
{
	IndexSet<TopoShape> edges, faces;
	TopoExplorerTool::MapShapes(shape, ShapeType::Face, faces);
	TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
	FaceEditor faceEditor;
	// Right side of the fuselage
	{
		// Delete two faces
		faceEditor.DeleteFace(shape, TopoCast::Face(faces[17 - 1]));
		faceEditor.DeleteFace(shape, TopoCast::Face(faces[19 - 1]));
		// Construct a new face based on the given set of edges and an existing face
		// Top
		IndexSet<TopoShape> set;// All edges  to be fused
		set.insert(edges[110 - 1]);
		set.insert(edges[111 - 1]);
		set.insert(edges[109 - 1]);
		set.insert(edges[28 - 1]);
		set.insert(edges[27 - 1]);
		faceEditor.BuildFaceFromSurface(shape, set, TopoCast::Face(faces[18 - 1]));
		// Bottom
		IndexSet<TopoShape> setdown;// All edges  to be fused
		setdown.insert(edges[114 - 1]);
		setdown.insert(edges[115 - 1]);
		setdown.insert(edges[116 - 1]);
		setdown.insert(edges[35 - 1]);
		faceEditor.BuildFaceFromSurface(shape, setdown, TopoCast::Face(faces[18 - 1]));
	}
	// Left side of the fuselage
	{
		// Delete three faces
		faceEditor.DeleteFace(shape, TopoCast::Face(faces[52 - 1]));
		faceEditor.DeleteFace(shape, TopoCast::Face(faces[26 - 1]));
		faceEditor.DeleteFace(shape, TopoCast::Face(faces[24 - 1]));
		// Construct a new face based on the given set of edges and an existing face
		// Top
		IndexSet<TopoShape> set;// All edges  to be fused
		set.insert(edges[233 - 1]);
		set.insert(edges[138 - 1]);
		set.insert(edges[61 - 1]);
		set.insert(edges[60 - 1]);
		set.insert(edges[135 - 1]);
		set.insert(edges[190 - 1]);
		set.insert(edges[137 - 1]);
		faceEditor.BuildFaceFromSurface(shape, set, TopoCast::Face(faces[25 - 1]));
		// Bottom
		IndexSet<TopoShape> setdown;// All edges  to be fused
		setdown.insert(edges[130 - 1]);
		setdown.insert(edges[131 - 1]);
		setdown.insert(edges[132 - 1]);
		setdown.insert(edges[53 - 1]);
		faceEditor.BuildFaceFromSurface(shape, setdown, TopoCast::Face(faces[25 - 1]));
	}
	// Unify faces and edges of the shape
	auto result = ShapeFixTool::UpgradeUnifySameDomain(shape);
	writetopo(result, "combineFaces.brep");
	return result;
}


void sewEdges(TopoShape& shape, const string& filePath, int e1, int e2, double tolerance)
{
	cout << "Applying auto fix (tolerance = " << tolerance << ") to file: " << filePath << endl;
	try {
		// Find all free edges
		IndexSet<TopoShape> edges;
		TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
		IndexSet<TopoShape> list = GeomE::DetectTool::DetectFreeEdges(shape);
		// Sew two edges
		TopoEdge edge1 = TopoCast::Edge(edges[e1]);
		TopoEdge edge2 = TopoCast::Edge(edges[e2]);
		EdgeEditor editor;
		editor.SewEdges(shape, edge1, edge2, tolerance);
	}
	catch (const exception& e) {
		cout << "Auto fix failed for file " << filePath << ". Exception: " << e.what() << endl;
		return;
	}

	// Construct the output filename by appending "_autosew" suffix to the original filename
	filesystem::path p(filePath);
	string stem = p.stem().string();
	string extension = p.extension().string();
	extension = ".step";
	string outFile = (p.parent_path() / (stem + "_autosew" + extension)).string();
	// Write
	if (writetopo(shape, outFile))
		cout << "Auto fix succeeded, output saved to: " << outFile << endl;
	else
		cout << "Failed to write output file: " << outFile << endl;
	cout << "success auto fix" << endl;
}

TopoShape fillhole_with_newface(TopoShape& shape)
{
	IndexSet<TopoShape> edges, faces;
	TopoExplorerTool::MapShapes(shape, ShapeType::Edge, edges);
	TopoExplorerTool::MapShapes(shape, ShapeType::Face, faces);
	IndexSet<TopoShape> set;
	set.insert(edges[14 - 1]);
	set.insert(edges[16 - 1]);
	set.insert(edges[88 - 1]);

	FaceEditor faceEditor;
	// Construct a new face extending from Face 2, using specified edge set. The new face shares the same surface geometry as Face 2.
	faceEditor.BuildFaceFromSurface(shape, set, TopoCast::Face(faces[3 - 1]));
	// Unify faces and edges of the shape
	auto result = ShapeFixTool::UpgradeUnifySameDomain(shape);
	// Write
	writetopo(result, "fillhole_with_newface.step");
	return result;
}


int main(int argc, char* argv[])
{
	try {
		std::cout << "start work" << endl;
		TopoShape shape;
		readtopo(shape, "./data/helicopter-2025.stp");
		shape = combineFaces(shape);
		sewEdges(shape, "./combineFaces.step", 187 - 1, 247 - 1, 0.007);
		shape = fillhole_with_newface(shape);
		writetopo(shape, "./outshape.brep");
	}
	catch (const std::exception& e) {
		std::cout << "Sorry, there was an exception: " << e.what() << endl;
	}
	catch (...) {
		std::cout << "Unknown exception" << endl;
	}
	system("pause");
	return 0;
}
