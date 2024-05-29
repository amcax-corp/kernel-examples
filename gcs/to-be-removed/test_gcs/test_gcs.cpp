#include "rapidjson/document.h"
#include <iostream>
#include <string>

#include "GCS2D.h"
#include "GCS3D.h"

#include "TestSolver.h"

#define FILE_NAME "D:/gcs_test.txt"

int main() {
	std::ifstream file_stream(FILE_NAME);
	if (!file_stream.is_open()) {
		std::cout << "failed to open the file: " << FILE_NAME << std::endl;
		return 0;
	}
	std::stringstream file_content;
	file_content << file_stream.rdbuf();
	rapidjson::Document json_document;
	json_document.Parse<rapidjson::kParseFullPrecisionFlag>(file_content.str().c_str());
	if (json_document.IsObject()) {
		bool is_2d =
			json_document.MemberEnd() != json_document.FindMember("Mode") &&
			json_document["Mode"].IsString() &&
			0 == strcmp("2D", json_document["Mode"].GetString());
		if (is_2d) {
			AMCAX::GCS::GCSSystem2D gcs_system;
			gcs_system.DeserializeFromJson(json_document);
			AMCAX::GCS::ErrorType solve_result = gcs_system.Solve();
			if (AMCAX::GCS::ErrorType::kNoError == solve_result) {
				gcs_system.Check();
			}
		}
		else {
			AMCAX::GCS::GCSSystem3D gcs_system;
			gcs_system.DeserializeFromJson(json_document);
			AMCAX::GCS::ErrorType solve_result = gcs_system.Solve();
			if (AMCAX::GCS::ErrorType::kNoError == solve_result) {
				gcs_system.Check();
			}
		}
		return 0;
	}
	auto json_array = json_document.GetArray();
	int array_size = json_array.Size();
	for (int index = 0; index < array_size; index++) {
		const auto& json_value = json_array[index];
		bool skip = json_value.MemberEnd() != json_value.FindMember("Skip") &&
			json_value["Skip"].IsBool() && json_value["Skip"].GetBool();
		if (skip) {
			continue;
		}
		auto info = json_value.FindMember("Info");
		if (json_value.MemberEnd() == info) {
			std::cout << "Invalid info" << std::endl;
		}
		else {
			std::cout << info->value.GetString() << std::endl;
		}
		auto cost = json_value.FindMember("Cost");
		if (json_value.MemberEnd() != cost) {
			const auto& cost_value = cost->value;
			for (auto value = cost_value.MemberBegin();
				value != cost_value.MemberEnd(); value++) {
				value->name;
				int size = value->value.GetArray().Size();
				double total = 0;
				for (int i = 0; i < size; i++) {
					total += value->value.GetArray()[i].GetDouble();
				}
				std::cout << value->name.GetString() << ": " << total / size
					<< std::endl;
			}
		}
		bool is_2d = json_value.MemberEnd() != json_value.FindMember("Mode") &&
			json_value["Mode"].IsString() &&
			0 == strcmp("2D", json_value["Mode"].GetString());
		auto content = json_value.FindMember("Content");
		if (is_2d) {
			AMCAX::GCS::GCSSystem2D gcs_system;
			gcs_system.DeserializeFromJson(content->value);
			AMCAX::GCS::ErrorType solve_result = gcs_system.Solve();
			if (AMCAX::GCS::ErrorType::kNoError == solve_result) {
				gcs_system.Check();
			}
		}
		else {
			AMCAX::GCS::GCSSystem3D gcs_system;
			gcs_system.DeserializeFromJson(content->value);
			AMCAX::GCS::ErrorType solve_result = gcs_system.Solve();
			if (AMCAX::GCS::ErrorType::kNoError == solve_result) {
				gcs_system.Check();
			}
		}
	}
	return 0;
}