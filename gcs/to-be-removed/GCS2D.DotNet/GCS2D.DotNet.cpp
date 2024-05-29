#include "GCS2D.DotNet.h"

#include "GCSSystem.h"
#include "GCSVarGeomHandle.h"

BEGIN_GCS_NAMESPACE

AMCAXGCSSystem2D::AMCAXGCSSystem2D() {
	gcs_system_ = std::make_unique<GCSSystem>();
}

uint32_t AMCAXGCSSystem2D::Create2dPoint(const Point2d& point) {
	GCSVarGeomHandlePtr handle = std::make_shared<GCSVarGeomHandle>();
	gcs_system_->Create2dPoint(handle, point.x, point.y);
	uint32_t id = var_geom_handles_.size();
	var_geom_handles_[id] = handle;
	return id;
}

bool AMCAXGCSSystem2D::GetPoint2d(uint32_t h_point, Point2d& point) {
	if (var_geom_handles_.end() == var_geom_handles_.find(h_point)) {
		return false;
	}
	Eigen::Vector2d pt(0, 0);
	gcs_system_->GetPoint2d(var_geom_handles_[h_point], pt);
	point = { pt.x(), pt.y() };
	return true;
}

uint32_t AMCAXGCSSystem2D::Create2dLine(uint32_t h_point0, uint32_t h_point1) {
	GCSVarGeomHandlePtr handle = std::make_shared<GCSVarGeomHandle>();
	gcs_system_->Create2dLine(handle, var_geom_handles_[h_point0],
		var_geom_handles_[h_point1]);
	uint32_t id = var_geom_handles_.size();
	var_geom_handles_[id] = handle;
	return id;
}

bool AMCAXGCSSystem2D::GetLine2d(uint32_t h_line, Line2d& line) {
	if (var_geom_handles_.end() == var_geom_handles_.find(h_line)) {
		return false;
	}
	Eigen::Vector2d start(0, 0);
	Eigen::Vector2d end(0, 0);
	gcs_system_->GetLine2d(var_geom_handles_[h_line], start, end);
	line.point0 = { start.x(), start.y() };
	line.point1 = { end.x(), end.y() };
	return true;
}

uint32_t AMCAXGCSSystem2D::Create2dCircle(uint32_t h_center, double radius) {
	GCSVarGeomHandlePtr handle = std::make_shared<GCSVarGeomHandle>();
	Eigen::Vector2d center(0, 0);
	gcs_system_->GetPoint2d(var_geom_handles_[h_center], center);
	gcs_system_->Create2dCircle(handle, var_geom_handles_[h_center], radius);
	uint32_t id = var_geom_handles_.size();
	var_geom_handles_[id] = handle;
	return id;
}

bool AMCAXGCSSystem2D::GetCircle2d(uint32_t h_circle,
	Circle2d& circle) {
	Eigen::Vector2d center(0, 0);
	double radius = 0;
	gcs_system_->GetCircle2d(var_geom_handles_[h_circle], center, radius);
	circle.center = { center.x(), center.y() };
	circle.radius = radius;
	return true;
}

bool AMCAXGCSSystem2D::CreateConstraint(uint32_t h_entity1, uint32_t h_entity2,
	int type, int vec_sense, double param) {
	if (type <= (int)BaseCons2D::Type::kFirstValue ||
		type >= (int)BaseCons2D::Type::kLastValue) {
		return false;
	}
	if (std::abs(vec_sense) > 1) {
		return false;
	}
	gcs_system_->Create2dConstraint(var_geom_handles_[h_entity1],
		var_geom_handles_[h_entity2],
		static_cast<BaseCons2D::Type>(type),
		static_cast<GCSVecSense>(vec_sense), param);
	return true;
}

bool AMCAXGCSSystem2D::Solve() {
	auto error_type = gcs_system_->Solve();
	return ErrorType::kNoError == error_type;
}

void AMCAXGCSSystem2D::Check() { gcs_system_->Check(); }

END_GCS_NAMESPACE