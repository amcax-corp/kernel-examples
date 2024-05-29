#ifndef GCS_2D_DOT_NET_H_
#define GCS_2D_DOT_NET_H_

#include <memory>
#include <unordered_map>

#ifdef AMCAX_GCS_JS
#define AMCAX_GCS_API
#else
#ifndef AMCAX_GCS_API
#ifdef _MSC_VER
#define AMCAX_GCS_API __declspec(dllexport)
#else
#define AMCAX_GCS_API
#endif  // MSC_VER
#endif  // AMCAX_GCS_API
#endif  // AMCAX_GCS_JS

#ifndef BEGIN_GCS_NAMESPACE
#define BEGIN_GCS_NAMESPACE \
  namespace AMCAX {         \
  namespace GCS {
#endif // !BEGIN_GCS_NAMESPACE

#ifndef END_GCS_NAMESPACE
#define END_GCS_NAMESPACE \
  }                       \
  }
#endif // !END_GCS_NAMESPACE

BEGIN_GCS_NAMESPACE

extern "C" {
	struct AMCAX_GCS_API Point2d {
		double x;
		double y;
	};

	struct AMCAX_GCS_API Line2d {
		Point2d point0;
		Point2d point1;
	};

	struct AMCAX_GCS_API Circle2d {
		Point2d center;
		double radius;
	};

	struct AMCAX_GCS_API Arc {
		Circle2d shape;
		double start;
		double end;
	};

	class GCSSystem;
	class GCSVarGeomHandle;
	class AMCAX_GCS_API AMCAXGCSSystem2D {
	public:
		AMCAXGCSSystem2D();
		uint32_t Create2dPoint(const Point2d& point);
		bool GetPoint2d(uint32_t h_point, Point2d& point);
		uint32_t Create2dLine(uint32_t h_point0, uint32_t h_point1);
		bool GetLine2d(uint32_t h_line, Line2d& line);
		uint32_t Create2dCircle(uint32_t h_center, double radius);
		bool GetCircle2d(uint32_t h_circle, Circle2d& circle);
		bool CreateConstraint(uint32_t h_entity0, uint32_t h_entity1, int type,
			int vec_sense, double param);
		bool Solve();
		void Check();

	private:
		std::unique_ptr<GCSSystem> gcs_system_;
		std::unordered_map<uint32_t, std::shared_ptr<GCSVarGeomHandle>>
			var_geom_handles_;
	};

	extern AMCAX_GCS_API AMCAXGCSSystem2D* CreateGCSSystem2D() {
		return new AMCAXGCSSystem2D();
	}

	extern AMCAX_GCS_API void DisposeGCSSystem2D(AMCAXGCSSystem2D* gcs_system) {
		if (nullptr != gcs_system) {
			delete gcs_system;
			gcs_system = nullptr;
		}
	}

	extern AMCAX_GCS_API uint32_t Create2dPoint(AMCAXGCSSystem2D* gcs_system,
		double x, double y) {
		return gcs_system->Create2dPoint({ x, y });
	}

	extern AMCAX_GCS_API bool GetPoint2d(AMCAXGCSSystem2D* gcs_system,
		uint32_t h_point, Point2d* point) {
		return gcs_system->GetPoint2d(h_point, *point);
	}

	extern AMCAX_GCS_API uint32_t Create2dLine(AMCAXGCSSystem2D* gcs_system,
		uint32_t h_point0,
		uint32_t h_point1) {
		return gcs_system->Create2dLine(h_point0, h_point1);
	}

	extern AMCAX_GCS_API uint32_t Create2dCircle(AMCAXGCSSystem2D* gcs_system,
		uint32_t h_center, double radius) {
		return gcs_system->Create2dCircle(h_center, radius);
	}

	extern AMCAX_GCS_API bool GetCircle2d(AMCAXGCSSystem2D* gcs_system,
		uint32_t h_circle,
		Circle2d* circle) {
		gcs_system->GetCircle2d(h_circle, *circle);
		return true;
	}

	extern AMCAX_GCS_API bool CreateConstraint(AMCAXGCSSystem2D* gcs_system,
		uint32_t h_entity1,
		uint32_t h_entity2, int type,
		int vec_sense, double param) {
		return gcs_system->CreateConstraint(h_entity1, h_entity2, type, vec_sense,
			param);
	}

	extern AMCAX_GCS_API bool Solve(AMCAXGCSSystem2D* gcs_system) {
		bool result = gcs_system->Solve();
		gcs_system->Check();
		return result;
	}
}

END_GCS_NAMESPACE

#endif  // GCS_2D_DOT_NET_H_