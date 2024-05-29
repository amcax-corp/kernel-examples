#include <chrono>
#include <iostream>
#include <string>
#include <unordered_set>

#include <Eigen/Core>
#include <Eigen/Dense>

#include "AMCAXGCS.h"

void TestTwoLinesPerpendicular() {
	AMCAX::GCS::GCSWSystem gcs_system;
	AMCAX::GCS::GCSWVarGeomHandle handle_line1_start;
	AMCAX::GCS::GCSWVarGeomHandle handle_line1_end;
	AMCAX::GCS::GCSWVarGeomHandle handle_line1;
	gcs_system.Create2dPoint(handle_line1_start,
		{ 95.2576040695179, 272.85974883679995 });
	gcs_system.Create2dPoint(handle_line1_end,
		{ 34.56167204468379, 224.60776302701413 });
	gcs_system.Create2dLine(handle_line1, handle_line1_start, handle_line1_end);
	AMCAX::GCS::GCSWVarGeomHandle handle_line2_start;
	AMCAX::GCS::GCSWVarGeomHandle handle_line2_end;
	AMCAX::GCS::GCSWVarGeomHandle handle_line2;
	gcs_system.Create2dPoint(handle_line2_start,
		{ -43.63313862260573, 447.56972057873355 });
	gcs_system.Create2dPoint(handle_line2_end,
		{ 95.25760406951785, 272.85974883679995 });
	gcs_system.Create2dLine(handle_line2, handle_line2_start, handle_line2_end);
	AMCAX::GCS::GCSWConHandle con_handle;
	gcs_system.Create2dPerpendicular(con_handle, handle_line1, handle_line2);
	AMCAX::GCS::Status solve_status = gcs_system.Solve();
	if (AMCAX::GCS::Status::kSolved == solve_status) {
		AMCAX::GCS::Line2d line1 = gcs_system.GetLine2d(handle_line1);
		AMCAX::GCS::Line2d line2 = gcs_system.GetLine2d(handle_line2);
		double dx1 = line1.end.x - line1.start.x;
		double dy1 = line1.end.y - line1.start.y;
		double length1 = std::sqrt(dx1 * dx1 + dy1 * dy1);
		double dx2 = line2.end.x - line2.start.x;
		double dy2 = line2.end.y - line2.start.y;
		double length2 = std::sqrt(dx2 * dx2 + dy2 * dy2);
		std::cout << "Line1 length: " << length1 << std::endl;
		std::cout << "Line2 length: " << length2 << std::endl;
		std::cout << "Inner product: " << (dx1 * dx2 + dy1 * dy2) / (length1 * length2) << std::endl;
	}
	else {
		std::cout << "Failed to solve line-circle tangent constraint" << std::endl;
	}
}

void TestLineCircleTangent() {
	AMCAX::GCS::GCSWSystem gcs_system;
	AMCAX::GCS::GCSWVarGeomHandle handle_point0;
	AMCAX::GCS::GCSWVarGeomHandle handle_point1;
	AMCAX::GCS::GCSWVarGeomHandle handle_line;
	gcs_system.Create2dPoint(handle_point0, { -63.296707, -22.307692 });
	gcs_system.Create2dPoint(handle_point1, { -23.956042, 37.472527 });
	gcs_system.Create2dLine(handle_line, handle_point0, handle_point1);
	AMCAX::GCS::GCSWVarGeomHandle handle_center;
	AMCAX::GCS::GCSWVarGeomHandle handle_circle;
	gcs_system.Create2dPoint(handle_center, { 23.516476, -22.087912 });
	gcs_system.Create2dCircle(handle_circle, handle_center, 39.189965);
	AMCAX::GCS::GCSWConHandle con_handle;
	gcs_system.Create2dTanLnCir(con_handle, handle_line, handle_circle, 0);
	AMCAX::GCS::Status solve_status = gcs_system.Solve();
	if (AMCAX::GCS::Status::kSolved == solve_status) {
		AMCAX::GCS::Line2d line = gcs_system.GetLine2d(handle_line);
		AMCAX::GCS::Circle2d circle = gcs_system.GetCircle2d(handle_circle);
		Eigen::Vector2d start(line.start.x, line.start.y);
		Eigen::Vector2d end(line.end.x, line.end.y);
		Eigen::Vector2d direction = (end - start).normalized();
		Eigen::Vector2d center(circle.center.x, circle.center.y);
		double distance =
			((center - start) - (center - start).dot(direction) * direction).norm();
		std::cout << "Constraint Residual: " << std::abs(distance - circle.radius)
			<< std::endl;
	}
	else {
		std::cout << "Failed to solve line-circle tangent constraint" << std::endl;
	}
}

void TestCircleCircleTangent() {
	AMCAX::GCS::GCSWSystem gcs_system;
	AMCAX::GCS::GCSWVarGeomHandle handle_center1;
	AMCAX::GCS::GCSWVarGeomHandle handle_circle1;
	gcs_system.Create2dPoint(handle_center1, { 50.974537, -67.761139 });
	gcs_system.Create2dCircle(handle_circle1, handle_center1, 94.091998);
	AMCAX::GCS::GCSWVarGeomHandle handle_center2;
	AMCAX::GCS::GCSWVarGeomHandle handle_circle2;
	gcs_system.Create2dPoint(handle_center2, { 291.736603, -105.9963 });
	gcs_system.Create2dCircle(handle_circle2, handle_center2, 88.008156);
	AMCAX::GCS::GCSWConHandle con_handle;
	gcs_system.Create2dTanCirCir(con_handle, handle_circle1, handle_circle2,
		AMCAX::GCS::VecSense::kCodirectional, 0);
	AMCAX::GCS::Status solve_status = gcs_system.Solve();
	if (AMCAX::GCS::Status::kSolved == solve_status) {
		AMCAX::GCS::Circle2d circle1 = gcs_system.GetCircle2d(handle_circle1);
		AMCAX::GCS::Circle2d circle2 = gcs_system.GetCircle2d(handle_circle2);
		Eigen::Vector2d center1(circle1.center.x, circle1.center.y);
		Eigen::Vector2d center2(circle2.center.x, circle2.center.y);
		double residual =
			(center1 - center2).norm() - circle1.radius - circle2.radius;
		std::cout << "Constarint Residual: " << std::abs(residual) << std::endl;
	}
	else {
		std::cout << "Failed to solve circle-circle tangent constraint"
			<< std::endl;
	}
}

int main(int argc, char* argv[]) {
	TestLineCircleTangent();
	TestCircleCircleTangent();
	TestTwoLinesPerpendicular();
	return 0;
}
