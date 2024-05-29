#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/directory.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/lexical_cast/try_lexical_convert.hpp>
#include <boost/lexical_cast.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_set>

#include "GCS3D.h"

#include "rapidjson/document.h"

#define DATASET_PATH "D:/gcs3d_test_data/dataset/filtered_top_level_assemblies"

typedef boost::filesystem::directory_entry DirectoryEntry;

bool check_result = false;

enum class AssemblyConstraintType {
	kLineLineCoin = 1,
	kPlanePlaneDistance = 2,
	kVecVecCoin = 3,
	kPointPointCoin = 4,
	kPointLineCoin = 5,
	kVecVecAngle = 7,
	kPointPointDistance = 9
};

struct AssemblyConstraint {
	bool is_inverse = false;
	int body1_id;
	int body2_id;
	AssemblyConstraintType constraint_type;
	double param = 0;
	Eigen::Vector3d point1;
	Eigen::Vector3d vector1;
	Eigen::Vector3d point2;
	Eigen::Vector3d vector2;
};

void ParseVector(std::vector<std::string>& content, int start_index,
	Eigen::Vector3d& vector) {
	for (int i = start_index; i < start_index + 3; i++) {
		vector[i - start_index] = std::stod(content[i]);
	}
}

void RegularizeVector(Eigen::Vector3d& vector) {
	int nan = -1;
	for (int i = 0; i < 3; i++) {
		if (std::abs(vector(i)) > 1e10) {
			nan = i;
			break;
		}
	}
	if (nan >= 0) {
		double value =
			vector(nan) / std::abs(vector(nan));
		vector = Eigen::Vector3d::Zero();
		vector(nan) = value;
	}
	vector.normalize();
}

bool ParseConstraintLine(std::vector<AssemblyConstraint>& constraint_items,
	std::vector<int>& bodies,
	std::string& constraint_line) {
	try {
		AssemblyConstraint constraint;
		std::vector<std::string> content;
		boost::split(content, constraint_line, boost::is_any_of(";"),
			boost::algorithm::token_compress_on);
		auto constraint_type =
			static_cast<AssemblyConstraintType>(std::stoi(content[0]));
		std::vector<std::string> body_ids;
		boost::split(body_ids, content[1], boost::is_any_of(" "),
			boost::algorithm::token_compress_on);
		int body1_id = std::stoi(body_ids[0]);
		int body2_id = std::stoi(body_ids[1]);
		std::vector<std::string> point_normal;
		boost::split(point_normal, content[2], boost::is_any_of(" "),
			boost::algorithm::token_compress_on);
		auto empty_content = point_normal.end();
		while (point_normal.end() !=
			(empty_content =
				std::find(point_normal.begin(), point_normal.end(), ""))) {
			point_normal.erase(empty_content);
		}
		switch (constraint_type) {
		case AssemblyConstraintType::kLineLineCoin: {
			ParseVector(point_normal, 0, constraint.point1);
			ParseVector(point_normal, 3, constraint.vector1);
			ParseVector(point_normal, 6, constraint.point2);
			ParseVector(point_normal, 9, constraint.vector2);
			RegularizeVector(constraint.vector1);
			RegularizeVector(constraint.vector2);
			constraint.is_inverse = false;
			if (content.size() > 3) {
				boost::conversion::try_lexical_convert<bool>(content[3],
					constraint.is_inverse);
			}
			break;
		}
		case AssemblyConstraintType::kPlanePlaneDistance: {
			ParseVector(point_normal, 0, constraint.point1);
			ParseVector(point_normal, 3, constraint.vector1);
			ParseVector(point_normal, 6, constraint.point2);
			ParseVector(point_normal, 9, constraint.vector2);
			RegularizeVector(constraint.vector1);
			RegularizeVector(constraint.vector2);
			constraint.is_inverse = false;
			if (content.size() > 3) {
				boost::conversion::try_lexical_convert<bool>(content[3],
					constraint.is_inverse);
			}
			if (content.size() > 4) {
				constraint.param = std::stod(content[4]);
			}
			else {
				constraint.param = 0;
			}
			break;
		}
		case AssemblyConstraintType::kVecVecCoin: {
			ParseVector(point_normal, 0, constraint.vector1);
			ParseVector(point_normal, 3, constraint.vector2);
			constraint.is_inverse = false;
			if (content.size() > 3) {
				boost::conversion::try_lexical_convert<bool>(content[3],
					constraint.is_inverse);
			}
			break;
		}
		case AssemblyConstraintType::kPointPointCoin: {
			ParseVector(point_normal, 0, constraint.point1);
			ParseVector(point_normal, 3, constraint.point2);
			break;
		}
		case AssemblyConstraintType::kPointLineCoin: {
			ParseVector(point_normal, 0, constraint.point1);
			ParseVector(point_normal, 3, constraint.point2);
			ParseVector(point_normal, 6, constraint.vector2);
			break;
		}
		case AssemblyConstraintType::kVecVecAngle: {
			ParseVector(point_normal, 0, constraint.vector1);
			ParseVector(point_normal, 3, constraint.vector2);
			constraint.param = std::stod(content[3]);
			break;
		}
		case AssemblyConstraintType::kPointPointDistance: {
			ParseVector(point_normal, 0, constraint.point1);
			ParseVector(point_normal, 3, constraint.point2);
			constraint.param = std::stod(content[3]);
			break;
		}
		default:
			break;
		}
		constraint.body1_id = body1_id;
		constraint.body2_id = body2_id;
		constraint.constraint_type = constraint_type;
		constraint_items.push_back(constraint);
		bodies.push_back(body1_id);
		bodies.push_back(body2_id);
		return true;
	}
	catch (std::exception& e) {
		return false;
	}
}

std::string GenerateParam(int index, int type, double value) {
	std::string result = "{\"DragComponent\":0.0,\"Group\":0,\"H\":";
	result += std::to_string(index);
	result += ",\"Type\":";
	result += std::to_string(type);
	result += ",\"Val\":";
	result += boost::lexical_cast<std::string>(value);
	result += "}";
	return result;
}

std::string GenerateEntity(int index) {
	std::string result = "{\"Distance\":0,\"Group\":0,\"H\":";
	result += std::to_string(index + 1);
	result +=
		",\"Locsys\":0,\"Normal\":0,\"NumNormal\":[0.0,0.0,0.0,0.0],\"NumPoint\":"
		"[0.0,0.0,0.0],\"Param\":[";
	std::vector<std::string> params;
	for (int i = 1; i <= 7; i++) {
		params.push_back(std::to_string(7 * index + i));
	}
	result += boost::join(params, ",");
	result +=
		"],\"Point\":[0,0,0,0],\"SE3\":[1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0,0.0,"
		"0.0,0.0],\"Type\":80000}";
	return result;
}

std::string GenerateRigidBody(int index) {
	std::string result = "{\"ID\":";
	result += std::to_string(index);
	result +=
		",\"IsGrounded\":false,\"CenterOfRotate\":[0.0,0.0,0.0],\"Transform\":[1."
		"0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0],"
		"\"Entity\":";
	result += std::to_string(index + 1);
	result += "}";
	return result;
}

std::string GenerateConstraint(AssemblyConstraint constraint) {
	std::string result = "{\"ConstraintType\":";
	std::string body1 = boost::lexical_cast<std::string>(constraint.body1_id);
	std::string body2 = boost::lexical_cast<std::string>(constraint.body2_id);
	switch (constraint.constraint_type) {
	case AssemblyConstraintType::kLineLineCoin: {
		result += "\"LnLnCoinCons\",\"Body\":[";
		result += body1 + "," + body2;
		result += "],\"Line\":[{\"Origin\":[";
		result += boost::lexical_cast<std::string>(constraint.point1.x()) + "," +
			boost::lexical_cast<std::string>(constraint.point1.y()) + "," +
			boost::lexical_cast<std::string>(constraint.point1.z());
		result += "],\"Direction\":[";
		result += boost::lexical_cast<std::string>(constraint.vector1.x()) + "," +
			boost::lexical_cast<std::string>(constraint.vector1.y()) + "," +
			boost::lexical_cast<std::string>(constraint.vector1.z());
		result += "]},{\"Origin\":[";
		result += boost::lexical_cast<std::string>(constraint.point2.x()) + "," +
			boost::lexical_cast<std::string>(constraint.point2.y()) + "," +
			boost::lexical_cast<std::string>(constraint.point2.z());
		result += "],\"Direction\":[";
		result += boost::lexical_cast<std::string>(constraint.vector2.x()) + "," +
			boost::lexical_cast<std::string>(constraint.vector2.y()) + "," +
			boost::lexical_cast<std::string>(constraint.vector2.z());
		result += "]}],\"VecSense\":";
		result += constraint.is_inverse ? "-1" : "1";
		result += ",\"Param\": 1.0 }";
		break;
	}
	case AssemblyConstraintType::kPlanePlaneDistance: {
		result += "\"PlPlDistCons\",";
		result += "\"Body\":[" + body1 + "," + body2 + "],\"Plane\":[[";
		result += boost::lexical_cast<std::string>(constraint.point1.x()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point1.y()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point1.z()) + ",";
		result += boost::lexical_cast<std::string>(constraint.vector1.x()) + ",";
		result += boost::lexical_cast<std::string>(constraint.vector1.y()) + ",";
		result += boost::lexical_cast<std::string>(constraint.vector1.z()) + "],[";
		result += boost::lexical_cast<std::string>(constraint.point2.x()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point2.y()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point2.z()) + ",";
		result += boost::lexical_cast<std::string>(constraint.vector2.x()) + ",";
		result += boost::lexical_cast<std::string>(constraint.vector2.y()) + ",";
		result += boost::lexical_cast<std::string>(constraint.vector2.z()) + "]],";
		result += "\"VecSense\":" + boost::lexical_cast<std::string>(constraint.is_inverse ? -1 : 1);
		result += ",\"Param\":" + boost::lexical_cast<std::string>(constraint.param) + "}";
		break;
	}
	case AssemblyConstraintType::kVecVecCoin: {
		result += "\"VecVecCoinCons\",\"Body\":[";
		result += body1 + "," + body2;
		result += "],\"Vector\":[[";
		result += boost::lexical_cast<std::string>(constraint.vector1.x()) + "," +
			boost::lexical_cast<std::string>(constraint.vector1.y()) + "," +
			boost::lexical_cast<std::string>(constraint.vector1.z());
		result += "],[";
		result += boost::lexical_cast<std::string>(constraint.vector2.x()) + "," +
			boost::lexical_cast<std::string>(constraint.vector2.y()) + "," +
			boost::lexical_cast<std::string>(constraint.vector2.z());
		result += "]],\"VecSense\":";
		result += constraint.is_inverse ? "-1" : "1";
		result += ",\"Param\":0.0}";
		break;
	}
	case AssemblyConstraintType::kPointPointCoin: {
		result += "\"PtPtCoinCons\",";
		result += "\"Body\":[" + body1 + "," + body2 + "],\"Point\":[[";
		result += boost::lexical_cast<std::string>(constraint.point1.x()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point1.y()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point1.z()) + "],[";
		result += boost::lexical_cast<std::string>(constraint.point2.x()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point2.y()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point2.z()) + "]]}";
		break;
	}
	case AssemblyConstraintType::kPointLineCoin: {
		result += "\"PtLnCoinCons\",";
		result += "\"Body\":[" + body1 + "," + body2 + "],\"Point\":[";
		result += boost::lexical_cast<std::string>(constraint.point1.x()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point1.y()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point1.z()) + "]";
		result += ",\"LineOrigin\":[";
		result += boost::lexical_cast<std::string>(constraint.point2.x()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point2.y()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point2.z()) + "]";
		result += ",\"LineDirection\":[";
		result += boost::lexical_cast<std::string>(constraint.vector2.x()) + ",";
		result += boost::lexical_cast<std::string>(constraint.vector2.y()) + ",";
		result += boost::lexical_cast<std::string>(constraint.vector2.z()) + "]}";
		break;
	}
	case AssemblyConstraintType::kVecVecAngle: {
		result += "\"VecVecAngCons\",\"Body\":[";
		result += body1 + "," + body2;
		result += "],\"Vector\":[[";
		result += boost::lexical_cast<std::string>(constraint.vector1.x()) + "," +
			boost::lexical_cast<std::string>(constraint.vector1.y()) + "," +
			boost::lexical_cast<std::string>(constraint.vector1.z());
		result += "],[";
		result += boost::lexical_cast<std::string>(constraint.vector2.x()) + "," +
			boost::lexical_cast<std::string>(constraint.vector2.y()) + "," +
			boost::lexical_cast<std::string>(constraint.vector2.z());
		result += "]],\"VecSense\":";
		result += constraint.is_inverse ? "-1" : "1";
		result += ",\"Param\":";
		result += boost::lexical_cast<std::string>(constraint.param);
		result += "}";
		break;
	}
	case AssemblyConstraintType::kPointPointDistance: {
		result += "\"PtPtDistCons\",";
		result += "\"Body\":[" + body1 + "," + body2 + "],\"Point\":[[";
		result += boost::lexical_cast<std::string>(constraint.point1.x()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point1.y()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point1.z()) + "],[";
		result += boost::lexical_cast<std::string>(constraint.point2.x()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point2.y()) + ",";
		result += boost::lexical_cast<std::string>(constraint.point2.z()) + "]],";
		result += "\"Param\":" + boost::lexical_cast<std::string>(constraint.param) + "}";
		break;
	}
	default:
		break;
	}
	return result;
}

void SolveChange(const std::string& common_json,
	const std::vector<AssemblyConstraint>& constraint_items,
	const DirectoryEntry& change_file) {
	boost::filesystem::ifstream change_file_handle(change_file);
	std::string change_line;
	bool invalid_content = false;
	std::unordered_map<int, Eigen::Matrix4d> transforms;
	while (getline(change_file_handle, change_line)) {
		std::vector<std::string> content;
		boost::split(content, change_line, boost::is_any_of(" "));
		auto empty_content = content.end();
		while (content.end() !=
			(empty_content = std::find(content.begin(), content.end(), ""))) {
			content.erase(empty_content);
		}
		int id = std::stoi(content[0]);
		transforms[id] = Eigen::Matrix4d::Zero();
		transforms[id] << std::stod(content[1]), std::stod(content[2]), std::stod(content[3]), std::stod(content[4]),
			std::stod(content[5]), std::stod(content[6]), std::stod(content[7]), std::stod(content[8]),
			std::stod(content[9]), std::stod(content[10]), std::stod(content[11]), std::stod(content[12]),
			std::stod(content[13]), std::stod(content[14]), std::stod(content[15]), std::stod(content[16]);
	}
	std::vector<std::string> constraints;
	std::vector<AssemblyConstraint> updated_constraints = constraint_items;
	std::unordered_set<int> bodies;
	for (auto& constraint : updated_constraints) {
		auto transform1 = transforms.find(constraint.body1_id);
		if (transforms.end() != transform1) {
			constraint.point1 =
				transform1->second.block<3, 3>(0, 0) * constraint.point1 +
				transform1->second.block<3, 1>(0, 3);
			constraint.vector1 =
				transform1->second.block<3, 3>(0, 0) * constraint.vector1;
		}
		auto transform2 = transforms.find(constraint.body2_id);
		if (transforms.end() != transform2) {
			constraint.point2 =
				transform2->second.block<3, 3>(0, 0) * constraint.point2 +
				transform2->second.block<3, 1>(0, 3);
			constraint.vector2 =
				transform2->second.block<3, 3>(0, 0) * constraint.vector2;
		}
		auto content = GenerateConstraint(constraint);
		if (content.empty()) {
			std::cout << "Unsupported change in: " << change_file << std::endl;
			return;
		}
		constraints.push_back(content);
		bodies.insert(constraint.body1_id);
		bodies.insert(constraint.body2_id);
	}
	std::string constraint_content = boost::join(constraints, ",");
	std::string json_content = common_json + constraint_content + "]}";
	try {
		AMCAX::GCS::GCSSystem3D gcs_system;
		gcs_system.DeserializeFromJson(json_content);
		auto start = std::chrono::high_resolution_clock::now();
		auto error_type = gcs_system.Solve();
		auto end = std::chrono::high_resolution_clock::now();
		if (AMCAX::GCS::ErrorType::kNoError == error_type &&
			check_result) {
			double residual = gcs_system.Check();
			std::cout << "Solve Residual: " << residual << std::endl;
		}
		std::cout << "Solve Result: " << static_cast<int>(error_type)
			<< " For: " << change_file.path().generic_string()
			<< " Cost: " << std::chrono::duration<double>(end - start).count()
			<< " BodySize: " << bodies.size()
			<< " ConstraintSize: " << constraint_items.size()
			<< std::endl;
	}
	catch (...) {
		std::cout << "Exception while processing " << change_file << std::endl;
	}
}

void TestModel(const DirectoryEntry& constraint_file,
	const std::vector<DirectoryEntry>& change_files) {
	boost::filesystem::ifstream constraint_file_handle(constraint_file);
	std::string constraint_line;
	bool invalid_content = false;
	std::vector<int> bodies;
	std::vector<AssemblyConstraint> constraint_items;
	while (getline(constraint_file_handle, constraint_line)) {
		if (!ParseConstraintLine(constraint_items, bodies, constraint_line)) {
			invalid_content = true;
			break;
		}
	}
	if (invalid_content || constraint_items.empty()) {
		std::cout << "Invalid content: " << constraint_file << std::endl;
		return;
	}
	std::cout << "Test data from: " << constraint_file.path().generic_string()
		<< std::endl;
	std::sort(bodies.begin(), bodies.end());
	bodies.erase(std::unique(bodies.begin(), bodies.end()), bodies.end());
	int max_body_id = bodies.back();
	bodies.clear();
	std::vector<std::string> params;
	std::vector<std::string> entities;
	std::vector<std::string> rigid_bodies;
	for (int i = 0; i < max_body_id; i++) {
		bodies.push_back(i);
	}
	int max_param_id = 0;
	int max_entity_id = 0;
	for (int i = 0; i <= max_body_id; i++) {
		params.push_back(GenerateParam(i * 7 + 1, 10, 0));
		params.push_back(GenerateParam(i * 7 + 2, 10, 0));
		params.push_back(GenerateParam(i * 7 + 3, 10, 0));
		params.push_back(GenerateParam(i * 7 + 4, 11, 1));
		params.push_back(GenerateParam(i * 7 + 5, 11, 0));
		params.push_back(GenerateParam(i * 7 + 6, 11, 0));
		params.push_back(GenerateParam(i * 7 + 7, 11, 0));
		entities.push_back(GenerateEntity(i));
		rigid_bodies.push_back(GenerateRigidBody(i));
		max_param_id = std::max(max_param_id, i * 7 + 7);
		max_entity_id = std::max(max_entity_id, i + 1);
	}
	std::string param_content = boost::join(params, ",");
	std::string entity_content = boost::join(entities, ",");
	std::string rigid_body_content = boost::join(rigid_bodies, ",");
	std::string json_content =
		"{\"SS_Param_Number\":" + std::to_string(max_param_id + 1) +
		",\"SS_Params\":[" + param_content +
		"],\"SS_Entity_Number\":" + std::to_string(max_entity_id + 1) +
		",\"SS_Entities\":[" + entity_content +
		"],\"SS_Constraints\":[],\"RigidBody\":[" + rigid_body_content +
		"],\"Constraint\":[";
	for (auto& change_file : change_files) {
		SolveChange(json_content, constraint_items, change_file);
	}
}

bool RunData(const boost::filesystem::directory_entry& data_path,
	const std::string& auxiliary_path) {
	if (!data_path.is_directory()) {
		return false;
	}
	std::vector<DirectoryEntry> files;
	for (auto file : boost::filesystem::directory_iterator(data_path)) {
		if (file.is_regular_file() &&
			boost::ends_with(file.path().string(), ".txt")) {
			files.push_back(file);
		}
	}
	std::sort(files.begin(), files.end());
	if (files.empty()) {
		return false;
	}
	std::unordered_map<std::string, DirectoryEntry> model_constraints;
	std::unordered_map<std::string, std::vector<DirectoryEntry>> model_changes;
	for (auto file : files) {
		auto file_name = file.path().filename().string();
		if (file_name.find("change") > file_name.length()) {
			std::vector<std::string> model_part;
			boost::split(model_part, file_name, boost::is_any_of("."));
			auto model_uid(model_part[0]);
			model_constraints[model_uid] = file;
		}
		else {
			std::vector<std::string> model_part;
			boost::split(model_part, file_name, boost::is_any_of("_"));
			auto model_uid(model_part[0]);
			if (model_part.size() == 1 || model_uid.length() <= 6) {
				continue;
			}
			model_uid.resize(model_uid.length() - 6);
			std::string auxiliary_file_path = auxiliary_path + "/" +
				file.path().filename().generic_string();
			if (boost::filesystem::exists(auxiliary_file_path) &&
				boost::filesystem::is_regular_file(auxiliary_file_path)) {
				model_changes[model_uid].push_back(DirectoryEntry(auxiliary_file_path));
			}
			else {
				model_changes[model_uid].push_back(file);
			}
		}
	}
	for (auto constraint : model_constraints) {
		if (model_changes.end() == model_changes.find(constraint.first)) {
			continue;
		}
		TestModel(constraint.second, model_changes[constraint.first]);
	}
	return true;
}

void RunDataset(const std::string& dataset_path, const std::string& auxiliary_data_set_path) {
	try {
		auto auxiliary_data_set = boost::filesystem::directory_entry(auxiliary_data_set_path);
		bool use_auxiliary = boost::filesystem::exists(auxiliary_data_set_path) &&
			boost::filesystem::is_directory(auxiliary_data_set);
		for (auto path : boost::filesystem::directory_iterator(dataset_path)) {
			if (!path.is_directory()) {
				continue;
			}
			std::string auxiliary_path("");
			if (use_auxiliary) {
				auxiliary_path = auxiliary_data_set.path().generic_string() + "/" +
					path.path().filename().generic_string();
			}
			bool is_empty = true;
			for (auto data_path : boost::filesystem::directory_iterator(path)) {
				std::string ap("");
				if (use_auxiliary) {
					ap = auxiliary_path + "/" + data_path.path().filename().generic_string();
				}
				if (RunData(data_path, ap)) {
					is_empty = false;
				}
			}
			if (is_empty) {
				RunData(path, auxiliary_path);
			}
		}
	}
	catch (std::exception ex) {
		std::cout << "RunDataset Exception: " << ex.what() << std::endl;
	}
	catch (...) {
		std::cout << "RunDataset General Exception" << std::endl;
	}
}

void RunChangeFile(const std::string& change_file) {
	std::vector<std::string> path_part;
	boost::split(path_part, change_file, boost::is_any_of("/\\"));
	std::string file_name = path_part.back();
	size_t change_index = file_name.find("change");
	if (change_index >= file_name.length()) {
		return;
	}
	std::string uid = file_name.substr(0, change_index);
	path_part.back() = uid + ".txt";
	DirectoryEntry constraint_file(boost::join(path_part, "/"));
	TestModel(constraint_file, { DirectoryEntry(change_file) });
}

int main(int argc, char* argv[]) {
	std::string data_set_path("");
	std::string auxiliary_data_set_path("");
	std::string change_file_path("");
	std::string multiple_change_file_path("");
	for (int i = 1; i < argc; i++) {
		if (!boost::starts_with(argv[i], "-")) {
			continue;
		}
		if (0 == strcmp("-a", argv[i])) {
			auxiliary_data_set_path = argv[i + 1];
			continue;
		}
		if (0 == strcmp("-c", argv[i])) {
			change_file_path = argv[i + 1];
			continue;
		}
		if (0 == strcmp("-d", argv[i])) {
			data_set_path = argv[i + 1];
			continue;
		}
		if (0 == strcmp("-mc", argv[i])) {
			multiple_change_file_path = argv[i + 1];
			continue;
		}
		if (0 == strcmp("--check", argv[i])) {
			check_result = true;
		}
	}
	if (data_set_path.empty() &&
		change_file_path.empty() &&
		multiple_change_file_path.empty()) {
		RunDataset(DATASET_PATH, auxiliary_data_set_path);
	}
	else if (!change_file_path.empty()) {
		RunChangeFile(change_file_path);
	}
	else if (!multiple_change_file_path.empty()) {
		boost::filesystem::ifstream multiple_file_handle(multiple_change_file_path);
		std::string constraint_line;
		while (getline(multiple_file_handle, constraint_line)) {
			RunChangeFile(constraint_line);
		}
	}
	else {
		RunDataset(data_set_path, auxiliary_data_set_path);
	}
	std::cout << "END" << std::endl;
	return 0;
}
