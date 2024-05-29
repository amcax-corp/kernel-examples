#pragma once
#include <iostream>
#include <fstream>
#include <regex>

#include "GCSWrapper.h"
#include "Constraint.h"
#include "CommonConfig.h"

BEGIN_GCS_NAMESPACE
BEGIN_GCS_EXPERIMENTAL_NAMESPACE

double ptpt_dist(Point3d p1, Point3d p2) {
	return pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2);
}

double vec_norm(Vector3d t) {
	return sqrt(t.x * t.x + t.y * t.y + t.z * t.z);
}

double ang_vec(Vector3d v1, Vector3d v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) / vec_norm(v1) / vec_norm(v2);
}

void normalize(Vector3d& t) {
	double a = vec_norm(t);
	t.x = t.x / a;
	t.y = t.y / a;
	t.z = t.z / a;
}

double lnln_dist(Line3d a, Line3d b) {
	double x = a.origin.x - b.origin.x;
	double y = a.origin.y - b.origin.y;
	double z = a.origin.z - b.origin.z;

	normalize(a.direction);
	double dot = x* a.direction.x + y * a.direction.y + z * a.direction.z;
	x = x - dot * a.direction.x;
	y = y - dot * a.direction.y;
	z = z - dot * a.direction.z;
	return x * x + y * y + z * z;
}

double ptPtDist3d(const Point3d& pt1, Point3d& pt2)
{
	double dx = pt1.x - pt2.x;
	double dy = pt1.y - pt2.y;
	double dz = pt1.z - pt2.z;
	double dist = std::sqrt(dx * dx + dy * dy + dz * dz);
	printf("pt(%lf, %lf, %lf) - pt(%lf, %lf, %lf) = dist: %lf\n", pt1.x, pt1.y, pt1.z, pt2.x, pt2.y, pt2.z, dist);
	return dist;
};

double ptLnDist3d(const Point3d& pt, const Line3d& line)
{
	Eigen::Vector3d p( pt.x,pt.y,pt.z );
	Eigen::Vector3d ori{ line.origin.x,line.origin.y,line.origin.z };
	Eigen::Vector3d dir{ line.direction.x, line.direction.y, line.direction.z };
	dir.normalize();
	double dist = ((p - ori).cross(dir)).norm();
	printf("pt(%lf, %lf, %lf) - line(orig(%lf, %lf, %lf); dir(%lf, %lf, %lf)) = dist: %lf\n", pt.x, pt.y, pt.z, line.origin.x, line.origin.y, line.origin.z, line.direction.x, line.direction.y, line.direction.z, dist);
	return dist;
}

double ptPlDist3d(const Point3d& pt, const Plane& line)
{
	Eigen::Vector3d p( pt.x,pt.y,pt.z );
	Eigen::Vector3d ori( line.origin.x,line.origin.y,line.origin.z );
	Eigen::Vector3d norm( line.normal.x, line.normal.y, line.normal.z );
	double dist = (p - ori).dot(norm)/norm.norm();
	//printf("%lf\n", norm.MagSquared());
	//printf("pt(%lf, %lf, %lf) - plane(orig(%lf, %lf, %lf); norm(%lf, %lf, %lf)) = dist: %lf\n", pt.x, pt.y, pt.z, line.origin.x, line.origin.y, line.origin.z, line.normal.x, line.normal.y, line.normal.z, dist);
	printf("pt(%lf, %lf, %lf) - plane(orig(%lf, %lf, %lf); norm(%lf, %lf, %lf)) = dist: %lf\n", pt.x, pt.y, pt.z, line.origin.x, line.origin.y, line.origin.z, norm.x(), norm.y(), norm.z(), dist);

	return dist;
}

void ptpt33() {
	GCSWSystem sys;
	auto gcsBody1 = sys.CreateRigidBody(0);
	auto gcsBody2 = sys.CreateRigidBody(1);

	GCSWConHandle conHandle;
	GCSWVariable gcsvar;
	GCSConEqMode mode{ GCSConEqMode::kGCSEQ };
	VecSense sense{ VecSense::kParallel };

	gcsBody1.SetGrounded(true);
	Vector3d a1{ 0,0,1 };
	Vector3d a2{ 1,0,0 };
	Vector3d a3{ 0,1,0 };

	Point3d pt11{ 0,0,0 };
	Point3d pt12{ 3,4,0 };
	Point3d pt13{ 0,0,5 };
	Point3d pt14{ 0,0,0 };
	Line3d l1{ pt11, a1 };

	Line3d l2{ pt12, a2 };
	Line3d l21{ pt12, a3 };
	Plane pl{ pt12, a1 };
	Plane pl2{ pt12, a2 };
	GCSWExtGeometry e1;
	GCSWExtGeometry e2;
	sys.Create3dDistPtPt(conHandle, gcsBody1, gcsBody2, pt12, pt11, e1, e2, 0, mode, gcsvar);
	sys.Create3dDistPtPt(conHandle, gcsBody1, gcsBody2, pt14, pt13, e1, e2, 0, mode, gcsvar);
	Status res = sys.Solve();

	// res = sys.Solve();
	if (res == Status::kSolved) {
		pt11 = sys.UpdatePoint3dPosition(gcsBody2, pt11);
		ptPtDist3d(pt11, pt12);
		pt13 = sys.UpdatePoint3dPosition(gcsBody2, pt13);
		ptPtDist3d(pt13, pt14);
	}
	else {
		std::cout << "something wrong" << std::endl;
	}
	return;
}

void plpl01()
{
	GCSWSystem sys;
	auto gcsBody1 = sys.CreateRigidBody(0);
	auto gcsBody2 = sys.CreateRigidBody(1);

	GCSWConHandle conHandle;
	GCSWVariable gcsvar;
	GCSConEqMode mode{ GCSConEqMode::kGCSEQ };
	VecSense sense{ VecSense::kCodirectional };

	gcsBody1.SetGrounded(true);
	Vector3d a1{ 0,0,1 };
	Vector3d a2{ 1,0,0 };
	Vector3d a3{ 0,1,0 };

	Point3d pt11{ 0,0,0 };
	Point3d pt12{ 0,0,10 };
	Line3d l1{ pt11, a1 };

	Line3d l2{ pt12, a2 };
	Line3d l21{ pt12, a3 };
	Plane pl{ pt12, a1 };
	Plane pl2{ pt12, a2 };
	Plane p13{ pt12, a3 };
	GCSWExtGeometry e1;
	GCSWExtGeometry e2;
	//constrain to 01
	sys.Create3dDistPlPl(conHandle, false, pt11, pt11, gcsBody1, gcsBody2, pl, pl2, e1, e2, sense, 0, mode, gcsvar);
	sys.Create3dDistPlPl(conHandle, false, pt11, pt11, gcsBody1, gcsBody2, pl2, p13, e1, e2, sense, 0, mode, gcsvar);
	//constrain to 00
	// sys.Create3dDistLnLn(conHandle, false, pt11, pt11, gcsBody1, gcsBody2, l2, l1, true, 0, mode, gcsvar);

	//false
	// sys.Create3dDistPtPl(conHandle, false, pt11, gcsBody2, gcsBody1, pt12, pl, 10, mode, gcsvar);
	//bu work
	//sys.Create3dDistPtPl(conHandle, false, pt11, gcsBody2, gcsBody2, pt12, pl, 0, mode, gcsvar);

	Status res = sys.Solve();

	// res = sys.Solve();
	if (res == Status::kSolved) {
		pl2 = sys.UpdatePlanePosition(gcsBody2, pl2);
//		std::cout << "new pl2" << pl2 << std::endl;
	}
	else {
		std::cout << "something wrong" << std::endl;
	}
	return;
}

void lnln33() {
	GCSWSystem sys;
	auto gcsBody0 = sys.CreateRigidBody(0);
	gcsBody0.SetGrounded(true);
	auto gcsBody1 = sys.CreateRigidBody(0);
	auto gcsBody2 = sys.CreateRigidBody(1);

	GCSWConHandle conHandle;
	GCSWVariable gcsvar;
	GCSConEqMode mode{ GCSConEqMode::kGCSEQ };
	VecSense sense{ VecSense::kParallel };

	
	Vector3d a1{ 0,0,1 };
	Vector3d a2{ 1,0,0 };
	Vector3d a3{ 0,1,0 };
	Point3d pt11{ 0,0,0 };
	Point3d pt12{ 0,0,10 };
	Point3d cent11{ -20.265516000000005, -5.499999999999995, -3.105072 };
	Vector3d dir{ 0,-1,0 };
	Point3d cent12{ -20.265516, -2.5, -3.105072 };
	Point3d cent21{ -17.305949000000005, -5.499999999999994, -9.448649 };
	Point3d cent22{ -20.265516, -2.5, 3.894927 };
	Line3d l1{ cent11, a3 };
	Line3d l2{ cent12, a3 };
	Line3d l3{ cent21, a3 };
	Line3d l4{ cent22, a3 };
	Plane pl{ pt11, a1 };
	Plane pl2{ pt12, a1 };
	GCSWExtGeometry e1;
	GCSWExtGeometry e2;
	sys.Create3dDistLnLn(conHandle, false, pt11, pt11, gcsBody1, gcsBody2, l1, l2, e1, e2, true, 0, sense, mode, gcsvar);
	auto gcsBody3 = sys.CreateRigidBody(0);
	auto gcsBody4 = sys.CreateRigidBody(1);
	sys.Create3dDistLnLn(conHandle, false, pt11, pt11, gcsBody3, gcsBody4, l3, l4, e1, e2, true, 0, sense, mode, gcsvar);
	Status res = sys.Solve();

	// res = sys.Solve();
	if (res == Status::kSolved) {
		auto ll3 = sys.UpdateLine3dPosition(gcsBody2, l3);
		auto ll4 = sys.UpdateLine3dPosition(gcsBody2, l4);
		std::cout << "res";
		std::cout << lnln_dist(l1, ll3) << std::endl;
		std::cout << lnln_dist(l2, ll4) << std::endl;
	}
	else {
		std::cout << "something wrong" << std::endl;
	}
	return;
}

void test3dDistPtLn()
{
	GCSWSystem gcs;
	int Bodyid = 1;
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	Point3d pt1 { 0,1,1 };
	Point3d pt2 { 1100,1,1 };
	Vector3d vc2 { 1,1,1 };
	Line3d pl{ pt2,vc2 };
	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();

	auto status1 = gcs.Create3dDistPtLn(conHandle, false, pt1, body1, body2, pt1, pl, extG1, extG2, 0.0, GCSConEqMode::kGCSEQ, dummyVar);
	auto isOk = gcs.Solve();
	double dist1;
	if (isOk == Status::kSolved){
		pt1 = gcs.UpdatePoint3dPosition(body1, pt1);
		pl = gcs.UpdateLine3dPosition(body2, pl);
		ptLnDist3d(pt1, pl);
	}
}

void test3dDistPtPt()
{
	GCSWSystem gcs;
	int Bodyid = 1;
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body3 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	Point3d pt0{ -6.141370, -4.246129, 15.000000 };
	Point3d pt1{ -6.141370, 6.221053, 15.000000 };
	Point3d pt2{ -18.445035, 6.221053, 15.000000 };
	Point3d pt3{ -15.112721, 4.856190, 15.000000 };
	Vector3d vc4{ 1, 1, 1 };
	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();
	auto status2 = gcs.Create3dDistPtPt(conHandle, body1, body2, pt0, pt0, extG1, extG2, 0, kGCSEQ, dummyVar);
	auto status4 = gcs.Create3dDistPtPt(conHandle, body2, body3, pt1, pt1, extG1, extG2, 0, kGCSEQ, dummyVar);
//	auto status3 = gcs.Create3dDistPtPt(conHandle, body3, body1, pt2, pt3, extG1, extG2, 0, kGCSEQ, dummyVar);
//	body2.SetCOR({ 40,10,5 });
	body2.SetGrounded(true);
	auto isOk = gcs.Solve();
}

void test3dDistPtPt_1()
{
	GCSWSystem gcs;
	int Bodyid = 1;
	GCSWRigidBody body11 = gcs.CreateRigidBody(Bodyid);
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body3 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	Point3d pt0{ 0, 10, 10 };
	Point3d pt1{ 78, 10, 0 };
	Point3d pt2{ 78, 0, 0 };
	//Point3d pt3{ 78, 10, 0 };

	Point3d pt3{ 870.237053, -99.803801, 17.423460 };

	Point3d pt4{ pt0.x + 0, pt0.y + 2, pt0.z + 5 };
	Vector3d vc4{ 1, 1, 1 };
	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();
	auto status2 = gcs.Create3dDistPtPt(conHandle, body1, body2, pt1, pt3, extG1, extG2, 800.0, kGCSEQ, dummyVar);
	auto status1 = gcs.Create3dDistPtPt(conHandle, body1, body2, pt0, pt2, extG1, extG2, 900.0, kGCSEQ, dummyVar);

	auto status3 = gcs.Create3dDistPtPt(conHandle, body3, body2, pt4, pt3, extG1, extG2, 2000.0, kGCSEQ, dummyVar);
//	auto status4 = gcs.Create3dDistPtPt(conHandle, body3, body1, pt4, pt1, extG1, extG2, 1500.0, kGCSEQ, dummyVar);
	body2.SetCOR({ 40,10,5 });
	body11.SetGrounded(true);
	//	GCSWVectorBody bodies = { body2 };
	//	gcs.prioritizedDrag(bodies, pt0, pt4, vc4, 1, 1);
	auto isOk = gcs.Solve();
	double dist1;
	if (isOk == Status::kSolved)
	{
		pt0 = gcs.UpdatePoint3dPosition(body1, pt0);

		pt1 = gcs.UpdatePoint3dPosition(body1, pt1);
		pt2 = gcs.UpdatePoint3dPosition(body2, pt2);
		pt3 = gcs.UpdatePoint3dPosition(body2, pt3);
		pt4 = gcs.UpdatePoint3dPosition(body3, pt4);
		ptPtDist3d(pt0, pt2);
		ptPtDist3d(pt1, pt3);
		ptPtDist3d(pt1, pt4);
		ptPtDist3d(pt3, pt4);
	}
}

void test3dDistPtLn_1()
{
	GCSWSystem gcs;
	int Bodyid = 0;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	Point3d pt11{ -27.206721, 1.134394, 30.000000 };
	Point3d pt12{ -27.206721, -3.865606, 10.000001 };
	Point3d pt1{ -16.323315, -11.476539, 30.000000 };
	Vector3d vc1{ -0.653350, 0.757056, 0.000000 };

	Point3d pt2{ -19.747397, -7.508951, 15.000000 };
	Vector3d vc2{ 0.000000, 0.000000, 1.000000 };
	Line3d pl{ pt1,vc1 };

	Line3d p2{ pt2,vc2 };
	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();

	auto status1 = gcs.Create3dDistPtLn(conHandle, false, pt1, body1, body2, pt11, pl, extG1, extG2, 0.0, GCSConEqMode::kGCSEQ, dummyVar);
	auto status2 = gcs.Create3dDistPtLn(conHandle, false, pt1, body1, body2, pt12, p2, extG1, extG2, 0.0, GCSConEqMode::kGCSEQ, dummyVar);

	auto isOk = gcs.Solve();
	double dist1;
	if (isOk == Status::kSolved) {
		pt11 = gcs.UpdatePoint3dPosition(body1, pt11);
		pt12 = gcs.UpdatePoint3dPosition(body1, pt12);
		pl = gcs.UpdateLine3dPosition(body2, pl);
		p2 = gcs.UpdateLine3dPosition(body2, p2);
		ptLnDist3d(pt11, pl);
		ptLnDist3d(pt12, p2);
	}
}

void test3dDistlnlnplpl_1()
{
	GCSWSystem gcs;
	int Bodyid = 0;
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	Point3d pt11{ -27.206721, 1.134394, 30.000000 };
	Point3d pt12{ -27.206721, -3.865606, 10.000001 };
	Point3d pt1{ -14.186668, 17.163420, 3.895018 };
	Vector3d vc1{ -0.707062, -0.707152, 0.000000 };
	Point3d pt2{ -28.174955, 28.328232, -6.159527 };
	Vector3d vc2{ 0.707157, 0.707057, -0.000000 };
	Line3d pl{ pt1,vc1 };
	Line3d p2{ pt2,vc2 };


	Point3d pt3{ -0.578223, 7.092011, 0.598536 };
	Vector3d vc3{ 0.707062, 0.707152, -0.000000 };
	Point3d pt4{ -24.697491, 31.214685, -10.000292 };
	Vector3d vc4{ 0.707157, 0.707057, -0.000000 };

	Plane pl3{ pt3,vc3 };
	Plane pl4{ pt4,vc4 };

	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();

	auto status1 = gcs.Create3dDistPlPl(conHandle, true, pt1, pt2, body1, body2, pl3, pl4, extG1, extG2, VecSense::kCodirectional, 0., GCSConEqMode::kGCSEQ, dummyVar);
	auto status2 = gcs.Create3dDistLnLn(conHandle, true, pt1, pt2, body1, body2, pl, p2, extG1, extG2,true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);

	auto isOk = gcs.Solve();
	double dist1;
	if (isOk == Status::kSolved) {
		pl3 = gcs.UpdatePlanePosition(body1, pl3);
		pl4 = gcs.UpdatePlanePosition(body2, pl4);
		pl = gcs.UpdateLine3dPosition(body1, pl);
		p2 = gcs.UpdateLine3dPosition(body2, p2);
		ptLnDist3d(pt11, pl);
		ptLnDist3d(pt12, p2);
	}
}

void test3dDistlnlnplpl_2()
{
	GCSWSystem gcs;
	int Bodyid = 1;
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body3 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;

	Point3d pt11{ -27.206721, 1.134394, 30.000000 };
	Point3d pt12{ -27.206721, -3.865606, 10.000001 };
	Point3d pt1{ -14.186668, 17.163420, 3.895018 };
	Vector3d vc1{ -0.707062, -0.707152, 0.000000 };
	Point3d pt2{ -28.174955, 28.328232, -6.159527 };
	Vector3d vc2{ 0.707157, 0.707057, -0.000000 };

	Plane pl1{ {-46.747491, 49.730694, 14.338047}, {0.156472, 0.977668, -0.140293} };
	Plane p12{ {-21.670066, 38.780385, -34.002339}, {-0.156472, -0.977668, 0.140293} };

	Plane p21{ {-16.640556, 68.102703, -37.890882}, {0.156472, 0.977668, -0.140293} };
	Plane p22{ {-8.419151, 69.959250, -15.783577}, {0.156472, 0.977668, -0.140293} };

	Plane p31{ {-24.482078, 69.212428, -21.083540}, {0.939642, -0.103592, 0.326102} };
	Plane p32{ {-19.166476, 63.874787, -38.095694}, {-0.939642, 0.103592, -0.326102} };

	Line3d p41{ {-20.231477, 64.514767, -34.823662}, {0.156472, 0.977668, -0.140293} };
	Line3d p42{ {-25.547080, 69.852408, -17.811507}, {-0.156472, -0.977668, 0.140293} };

	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();

	auto status1 = gcs.Create3dDistPlPl(conHandle, true, pt1, pt2, body1, body2, pl1, p12, extG1, extG2, VecSense::kOpposed, 0., GCSConEqMode::kGCSEQ, dummyVar);
	auto status2 = gcs.Create3dDistPlPl(conHandle, true, pt1, pt2, body2, body3, p21, p22, extG1, extG2, VecSense::kCodirectional, 0., GCSConEqMode::kGCSEQ, dummyVar);
	auto status3 = gcs.Create3dDistPlPl(conHandle, true, pt1, pt2, body3, body2, p31, p32, extG1, extG2, VecSense::kOpposed, 0., GCSConEqMode::kGCSEQ, dummyVar);
	auto status4 = gcs.Create3dDistLnLn(conHandle, true, pt1, pt2, body2, body3, p41, p42, extG1, extG2, true, 0.0, VecSense::kOpposed, GCSConEqMode::kGCSEQ, dummyVar);

	auto isOk = gcs.Solve();
	double dist1;
	if (isOk == Status::kSolved) {
		pl1 = gcs.UpdatePlanePosition(body1, pl1);
		p12 = gcs.UpdatePlanePosition(body2, p12);

		p21 = gcs.UpdatePlanePosition(body2, p21);
		p22 = gcs.UpdatePlanePosition(body3, p22);

		p31 = gcs.UpdatePlanePosition(body3, p31);
		p32 = gcs.UpdatePlanePosition(body2, p32);

		p41 = gcs.UpdateLine3dPosition(body2, p41);
		p42 = gcs.UpdateLine3dPosition(body3, p42);
		ptPlDist3d(pt11, pl1);
		ptPlDist3d(pt11, p12);
		ptPlDist3d(pt11, p21);
		ptPlDist3d(pt11, p22);
		ptPlDist3d(pt11, p31);
		ptPlDist3d(pt11, p32);
		ptLnDist3d(pt12, p41);
		ptLnDist3d(pt12, p42);
	}
}

void test3dDistlnlnplpl_3()
{
	GCSWSystem gcs;
	int Bodyid = 0;
	GCSWRigidBody body0 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;

	Point3d pt11{ -27.206721, 1.134394, 30.000000 };
	Point3d pt12{ -27.206721, -3.865606, 10.000001 };
	Point3d pt1{ -14.186668, 17.163420, 3.895018 };
	Vector3d vc1{ -0.707062, -0.707152, 0.000000 };
	Point3d pt2{ -28.174955, 28.328232, -6.159527 };
	Vector3d vc2{ 0.707157, 0.707057, -0.000000 };

	Line3d p41{ {5.500000, 44.997553, -9.843617}, {1.000000, 0.000000, 0.000000} };
	Line3d p42{ {7.500000, 44.997553, -9.843617}, {1.000000, -0.000000, -0.000000} };


	Plane pl1{ {10.000000, 61.741980, -6.140343}, {1.000000, -0.000000, -0.000000} };
	Plane p12{ {10.000000, 40.000000, -10.000159}, {1.000000, 0.000000, 0.000000} };

	Plane p21{ {-20.000000, 39.978518, -9.999291}, {-1.000000, 0.000000, 0.000000} };
	Plane p22{ {6.724768, 32.816282, 15.000000}, {0.000000, 1.000000, 0.000000} };


	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();

	auto status4 = gcs.Create3dDistLnLn(conHandle, true, pt1, pt2, body0, body1, p41, p42, extG1, extG2, true, 0.0, VecSense::kCodirectional, GCSConEqMode::kGCSEQ, dummyVar);
	auto status1 = gcs.Create3dDistPlPl(conHandle, true, pt1, pt2, body1, body0, pl1, p12, extG1, extG2, VecSense::kCodirectional, 0., GCSConEqMode::kGCSEQ, dummyVar);
	auto status2 = gcs.Create3dDistPlPl(conHandle, true, pt1, pt2, body0, body2, p21, p22, extG1, extG2, VecSense::kCodirectional, 0., GCSConEqMode::kGCSEQ, dummyVar);

	auto isOk = gcs.Solve();
	double dist1;
	if (isOk == Status::kSolved) {
		pl1 = gcs.UpdatePlanePosition(body1, pl1);
		p12 = gcs.UpdatePlanePosition(body0, p12);

		p21 = gcs.UpdatePlanePosition(body0, p21);
		p22 = gcs.UpdatePlanePosition(body2, p22);

		p41 = gcs.UpdateLine3dPosition(body0, p41);
		p42 = gcs.UpdateLine3dPosition(body1, p42);

		ptLnDist3d(pt12, p41);
		ptLnDist3d(pt12, p42);

		ptPlDist3d(pt11, pl1);
		ptPlDist3d(pt11, p12);
		ptPlDist3d(pt11, p21);
		ptPlDist3d(pt11, p22);

	}
}

void test_drag1()
{
	//---------------create3dDistPtPt--------------//
	GCSWSystem gcs;
	GCSWRigidBody body1 = gcs.CreateRigidBody(1);
	GCSWRigidBody body2 = gcs.CreateRigidBody(2);
	Point3d pt1{ -6.141370, -4.246129, 15.000000 };
	Point3d pt2{ -173.014522, -21.943189, 238.469093 };
	Point3d pt3{ -6.141370, -4.246129, 15.000000 };
	Point3d pt4{ -173.014522, -21.943189, 238.469093 };
	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();
	auto status2 = gcs.Create3dDistPtPt(conHandle, body1, body2, pt1, pt3, extG1, extG2, 0.0, kGCSEQ, dummyVar);
//	auto status3 = gcs.Create3dDistPtPt(conHandle, body3, body2, pt4, pt2, extG1, extG2, 0.0, kGCSEQ, dummyVar);
//	auto status4 = gcs.Create3dDistPtPt(conHandle, body3, body1, pt4, pt1, extG1, extG2, 1500.0, kGCSEQ, dummyVar);
// 	body3.SetCOR({ 40,10,5 });
	body1.SetGrounded(true);
	Point3d oldPos{ 2.742717, -3.185548, 12.082583 };
	Point3d newPos{ 2.829537, -3.364398, 11.816913 };

//	Point3d newPos{ -107.028405, -25.452895, 284.352798 }; 
	Vector3d view{ -0.577350, 0.577350, -0.577350 };
	int mode = 0;
	gcs.PrioritizedDrag(body2, oldPos, newPos, view, mode, 1);
	//auto isOk = gcs.Solve(GCSWSolveMode::kNormal, false);
	auto isOk = gcs.Solve();
	double dist1;
	//if (isOk == Status::kSolved || isOk == Status::kSolvedWithoutDOFAndRedundancyAnalysis) 
	{
		pt1 = gcs.UpdatePoint3dPosition(body1, pt1);
		oldPos = gcs.UpdatePoint3dPosition(body2, oldPos);
		pt3 = gcs.UpdatePoint3dPosition(body2, pt3);
		pt2 = gcs.UpdatePoint3dPosition(body2, pt2);
		// pt4 = gcs.UpdatePoint3dPosition(body3, pt4);
		ptPtDist3d(pt1, pt3);
		ptPtDist3d(newPos, oldPos);
		ptPtDist3d(pt2, pt4);
		Eigen::Vector3d ab(oldPos.x - newPos.x, oldPos.y - newPos.y, oldPos.z - newPos.z);
		Eigen::Vector3d v(view.x, view.y, view.z);
		std::cout << ab.cross(v) << std::endl;

	}
}

void test_drag2()
{
	//---------------create3dDistPtPt--------------//
	GCSWSystem gcs;
	int Bodyid = 1;
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;

	Point3d pt1{ -171.362216, -72.794267, 179.683660 };
	Point3d pt3{ -171.362216, -72.794267, 179.683660 };
	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();
	auto status2 = gcs.Create3dDistPtPt(conHandle, body1, body2, pt1, pt3, extG1, extG2, 0.0, kGCSEQ, dummyVar);
	body2.SetGrounded(true);
	Point3d oldPos{ -184.000073, -33.418462, 131.081890 }; 
	Point3d newPos{ -184.511738, -33.930127, 131.081890 }; 
	Vector3d view{ -0.577350, 0.577350, -0.577350 }; 
	int mode = 0;
	gcs.PrioritizedDrag(body1, oldPos, newPos, view, mode, 1);
	//auto isOk = gcs.Solve(GCSWSolveMode::kNormal, false);
	auto isOk = gcs.Solve();

	//if (isOk == Status::kSolved || isOk == Status::kSolvedWithoutDOFAndRedundancyAnalysis) 
	{
		pt1 = gcs.UpdatePoint3dPosition(body1, pt1);
		pt3 = gcs.UpdatePoint3dPosition(body2, pt3);

		oldPos = gcs.UpdatePoint3dPosition(body1, oldPos);
		ptPtDist3d(pt1, pt3);
		ptPtDist3d(newPos, oldPos);

		Eigen::Vector3d ab(oldPos.x - pt1.x, oldPos.y - pt1.y, oldPos.z - pt1.z);
		Eigen::Vector3d ac(newPos.x - pt1.x, newPos.y - pt1.y, newPos.z - pt1.z);

		std::cout << ab.cross(ac) << std::endl;

	}
}

void test_drag3()
{
	GCSWSystem gcs;
	int Bodyid = 1;
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body3 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	Point3d pt1{ -173.014522, -21.943189, 238.469093 };
	Point3d pt2{ -202.232790, -93.575968, 246.171502 };
	Point3d pt3{ -173.014522, -21.943189, 238.469093 };
	Point3d pt4{ -202.232790, -93.575968, 246.171502 };
	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();
	auto status2 = gcs.Create3dDistPtPt(conHandle, body1, body2, pt1, pt3, extG1, extG2, 0.0, kGCSEQ, dummyVar);
	auto status3 = gcs.Create3dDistPtPt(conHandle, body3, body2, pt4, pt2, extG1, extG2, 0.0, kGCSEQ, dummyVar);
	//	auto status4 = gcs.Create3dDistPtPt(conHandle, body3, body1, pt4, pt1, extG1, extG2, 1500.0, kGCSEQ, dummyVar);
	body2.SetCOR({ 40,10,5 });
	body1.SetGrounded(true);
	Point3d oldPos{ -166.110599, -74.161633, 235.009647 }; 
	Point3d newPos{ -165.819588, -73.998193, 234.360289 }; 
	Vector3d view{ -0.896694, 0.298705, -0.326672 }; 
	int mode = 1;
	gcs.PrioritizedDrag(body2, oldPos, newPos, view, mode, 1);
	//auto isOk = gcs.Solve(GCSWSolveMode::kNormal, false);
	auto isOk = gcs.Solve();
	//if (isOk == Status::kSolved || isOk == Status::kSolvedWithoutDOFAndRedundancyAnalysis) 
	{
		pt1 = gcs.UpdatePoint3dPosition(body1, pt1);
		oldPos = gcs.UpdatePoint3dPosition(body2, oldPos);
		pt3 = gcs.UpdatePoint3dPosition(body2, pt3);
		pt2 = gcs.UpdatePoint3dPosition(body2, pt2);
		pt4 = gcs.UpdatePoint3dPosition(body3, pt4);
		ptPtDist3d(pt1, pt3);
		ptPtDist3d(newPos, oldPos);
		ptPtDist3d(pt2, pt4);

		Eigen::Vector3d ab(oldPos.x - pt1.x, oldPos.y - pt1.y, oldPos.z - pt1.z);
		Eigen::Vector3d ac(newPos.x - pt1.x, newPos.y - pt1.y, newPos.z - pt1.z);

		std::cout << ab.cross(ac) << std::endl;
	}
}

void test_drag4()
{
	//---------------create3dDistPtPt--------------//
	GCSWSystem gcs;
	int Bodyid = 1;
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;

	Point3d pt1{ -12.399862, -49.858607, 57.259574 };
	Point3d pt3{ -12.399862, -49.858607, 57.259574 };
	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();
	auto status2 = gcs.Create3dDistPtPt(conHandle, body1, body2, pt1, pt3, extG1, extG2, 0.0, kGCSEQ, dummyVar);
	body2.SetGrounded(true);
	Point3d oldPos{ 13.074907, -49.858607, 48.877561 }; 
	Point3d newPos{ 6.274083, -49.858607, 51.041083 }; 
	Vector3d view{ 0.000000, 1.000000, -0.000000 }; 
	int mode = 0;
	gcs.PrioritizedDrag(body1, oldPos, newPos, view, mode, 1);
	//auto isOk = gcs.Solve(GCSWSolveMode::kNormal, false);
	auto isOk = gcs.Solve();
	//if (isOk == Status::kSolved || isOk == Status::kSolvedWithoutDOFAndRedundancyAnalysis) 
	{
		pt1 = gcs.UpdatePoint3dPosition(body1, pt1);
		pt3 = gcs.UpdatePoint3dPosition(body2, pt3);

		oldPos = gcs.UpdatePoint3dPosition(body1, oldPos);
		ptPtDist3d(pt1, pt3);
		ptPtDist3d(newPos, oldPos);

		Eigen::Vector3d ab(oldPos.x - pt1.x, oldPos.y - pt1.y, oldPos.z - pt1.z);
		Eigen::Vector3d ac(newPos.x - pt1.x, newPos.y - pt1.y, newPos.z - pt1.z);

		std::cout << ab.cross(ac) << std::endl;

	}
}

void test_drag5()
{
	//---------------create3dDistPtPt--------------//
	GCSWSystem gcs;
	int Bodyid = 1;
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;

	Point3d pt1{ -12.399862, -49.858607, 57.259574 };
	Point3d pt3{ -12.399862, -49.858607, 57.259574 };
	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();
	auto status2 = gcs.Create3dDistPtPt(conHandle, body1, body2, pt1, pt3, extG1, extG2, 0.0, kGCSEQ, dummyVar);
	body2.SetGrounded(true);
	Point3d oldPos{ -1.259550, -45.274790, 50.703079 };
	Point3d newPos{ -7.789866, -49.812967, 52.695218 };
	Vector3d view{ -0.577350, 0.577350, -0.577350 };
	int mode = 1;
	gcs.PrioritizedDrag(body1, oldPos, newPos, view, mode, 1);
	//auto isOk = gcs.Solve(GCSWSolveMode::kNormal, false);
	auto isOk = gcs.Solve();
	//if (isOk == Status::kSolved || isOk == Status::kSolvedWithoutDOFAndRedundancyAnalysis) 
	{
		pt1 = gcs.UpdatePoint3dPosition(body1, pt1);
		pt3 = gcs.UpdatePoint3dPosition(body2, pt3);

		oldPos = gcs.UpdatePoint3dPosition(body1, oldPos);
		ptPtDist3d(pt1, pt3);
		ptPtDist3d(newPos, oldPos);

		Eigen::Vector3d ab(oldPos.x - pt1.x, oldPos.y - pt1.y, oldPos.z - pt1.z);
		Eigen::Vector3d ac(newPos.x - pt1.x, newPos.y - pt1.y, newPos.z - pt1.z);

		std::cout << ab.cross(ac) << std::endl;

	}
}

void ttt()
{
	GCSWSystem gcs;
	int Bodyid = 0;
	GCSWRigidBody body0 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body3 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
Line3d line11{ {96.594196, 4.953802, 165.862241}, {-1.000000, 0.000000, 0.000000} }; 
Line3d line12{ {76.461769, 4.953802, 165.862241}, {1.000000, 0.000000, 0.000000} }; 

Line3d line21{ {-61.559755, -102.097001, 266.844742}, {-1.000000, 0.000000, 0.000000} }; 
Line3d line22{ {-146.074911, -63.999045, 192.651741}, {-1.000000, -0.000000, 0.000000} }; 


	Point3d pt3{ -0.578223, 7.092011, 0.598536 };

	body0.SetGrounded(true);
	body1.SetGrounded(true);

	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();
	gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, body2, body0, line11, line12, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);

	gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, body3, body1, line21, line22, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);

	auto isOk = gcs.Solve();
	double dist1;
	if (isOk == Status::kSolved) {
		line11 = gcs.UpdateLine3dPosition(body2, line11);
		line12 = gcs.UpdateLine3dPosition(body0, line12);
		line21 = gcs.UpdateLine3dPosition(body3, line21);
		line22 = gcs.UpdateLine3dPosition(body1, line22);
	}
}

void test_drag6()
{
	//---------------create3dDistPtPt--------------//
	GCSWSystem gcs;
	int Bodyid = 1;
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;

	Line3d line1{ {-12.399862, -39.858607, 57.259574}, {0.000000, -1.000000, 0.000000} }; 
	Line3d line2{ {-12.399861, -95.529272, 57.259575}, {-0.000000, 1.000000, -0.000000} };
	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();
	Point3d pt3{ -0.578223, 7.092011, 0.598536 };

	gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, body1, body2, line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	body1.SetGrounded(true);
	Point3d oldPos{ 9.121111, -96.565152, 49.594960 }; 
	Point3d newPos{ 9.076420, -94.731941, 49.472861 }; 
	Vector3d view{ -0.577350, 0.577350, -0.577350 }; 
	int mode = 0;
	gcs.PrioritizedDrag(body2, oldPos, newPos, view, mode, 1);
	//auto isOk = gcs.Solve(GCSWSolveMode::kNormal, false);
	auto isOk = gcs.Solve();
	//if (isOk == Status::kSolved || isOk == Status::kSolvedWithoutDOFAndRedundancyAnalysis) 
	{
		line1 = gcs.UpdateLine3dPosition(body1, line1);
		line2 = gcs.UpdateLine3dPosition(body2, line2);

		oldPos = gcs.UpdatePoint3dPosition(body2, oldPos);
		ptPtDist3d(newPos, oldPos);


	}
}

void test_drag7()
{
	//---------------create3dDistPtPt--------------//
	GCSWSystem gcs;
	int Bodyid = 1;
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	Point3d pt1{ -6.141370, -4.246129, 15.000000 };
	Point3d pt3{ -6.141370, -4.246129, 15.000000 };
	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();
	auto status2 = gcs.Create3dDistPtPt(conHandle, body1, body2, pt1, pt3, extG1, extG2, 0.0, kGCSEQ, dummyVar);
	body1.SetGrounded(true);
	Point3d oldPos{ -9.550696, -16.623015, 6.670807 };
	Point3d newPos{ -9.615470, -16.687789, 6.670807 };
	Vector3d view{ -0.577350, 0.577350, -0.577350 };
	int mode = 0;
	gcs.PrioritizedDrag(body2, oldPos, newPos, view, mode, 1);
	//auto isOk = gcs.Solve(GCSWSolveMode::kNormal, false);
	auto isOk = gcs.Solve();
	double dist1;
	{
		pt1 = gcs.UpdatePoint3dPosition(body1, pt1);
		oldPos = gcs.UpdatePoint3dPosition(body2, oldPos);
		pt3 = gcs.UpdatePoint3dPosition(body2, pt3);
		ptPtDist3d(pt1, pt3);
		ptPtDist3d(newPos, oldPos);
		Eigen::Vector3d ab(oldPos.x - newPos.x, oldPos.y - newPos.y, oldPos.z - newPos.z);
		Eigen::Vector3d v(view.x, view.y, view.z);
		std::cout << ab.cross(v) << std::endl;

	}
}

void test_drag9()
{
	Point3d pt30{ -0.578223, 7.092011, 0.598536 };
	GCSWSystem gcs;
	int Bodyid = 0;

	std::vector<GCSWRigidBody> bodies(13);

	for (size_t i = 0; i < 13; i++)
	{
		bodies[i] = gcs.CreateRigidBody(Bodyid);
		Bodyid++;
	}

	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();
	Point3d pt3{ -0.578223, 7.092011, 0.598536 };

	{
		Plane plane1{ {-68.629342, -17.933808, 176.731730}, {-0.928034, -0.026307, 0.371566} };
		Plane plane2{ {-65.570004, -17.223435, 184.423132}, {-0.928034, -0.026307, 0.371565} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[1], bodies[0], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}
	
	{
		Line3d line1{ {-46.413852, 27.710027, 168.166572}, {-0.928034, -0.026307, 0.371565} }; 
		Line3d line2{ {-46.413846, 27.710027, 168.166569}, {-0.928034, -0.026307, 0.371566} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[1], bodies[0], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Plane plane1{ {-65.570004, -17.223435, 184.423132}, {-0.928034, -0.026307, 0.371565} }; 
		Plane plane2{ {-70.209680, -19.073549, 172.703957}, {0.928034, 0.026307, -0.371566} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[2], bodies[0], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Line3d line1{ {-37.963985, -60.653553, 183.015059}, {0.928034, 0.026307, -0.371565} }; 
		Line3d line2{ {-37.963990, -60.653553, 183.015060}, {-0.928034, -0.026307, 0.371566} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[2], bodies[0], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Plane plane1{ {-51.111778, 4.089035, 171.713974}, {0.079707, -0.988423, 0.129099} };
		Plane plane2{ {-45.447725, 4.180038, 168.913665}, {-0.079707, 0.988423, -0.129099} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[3], bodies[4], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Line3d line1{ {-50.929844, 4.163747, 172.173667}, {0.928034, 0.026307, -0.371566} }; 
		Line3d line2{ {-45.083857, 4.329462, 169.833052}, {0.928034, 0.026307, -0.371566} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[3], bodies[4], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Plane plane1{ {-36.798429, 4.355662, 164.918126}, {0.079707, -0.988423, 0.129099} }; 
		Plane plane2{ {-45.447725, 4.180038, 168.913665}, {-0.079707, 0.988423, -0.129099} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[4], bodies[0], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Line3d line1{ {-36.980363, 4.280950, 164.458432}, {0.928034, 0.026307, -0.371566} }; 
		Line3d line2{ {-45.811594, 4.030612, 167.994279}, {-0.928034, -0.026307, 0.371566} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[4], bodies[0], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Plane plane1{ {56.516238, -113.222017, 388.356642}, {0.079707, -0.988423, 0.129099} }; 
		Plane plane2{ {45.178018, -111.891174, 405.546361}, {0.079707, -0.988423, 0.129099} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[5], bodies[6], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);

	}

	{
		Line3d line1{ {59.219179, -81.477380, 397.355092}, {-0.079707, 0.988423, -0.129099} }; 
		Line3d line2{ {59.219179, -81.477379, 397.355092}, {-0.079707, 0.988423, -0.129099} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[5], bodies[6], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}

	///////////////

	{
		Plane plane1{ {36.004465, -115.620366, 382.658307}, {0.079707, -0.988423, 0.129099} }; 
		Plane plane2{ {56.516238, -113.222017, 388.356642}, {0.079707, -0.988423, 0.129099} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[7], bodies[6], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Line3d line1{ {49.030870, -85.661268, 371.612261}, {-0.079707, 0.988423, -0.129099} }; 
		Line3d line2{ {49.030870, -85.661267, 371.612260}, {-0.079707, 0.988423, -0.129099} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[7], bodies[6], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}


	///////////////

	{
		Plane plane1{ {24.397602, -82.683296, 404.494276}, {-0.928034, -0.026307, 0.371566} }; 
		Plane plane2{ {21.603987, -83.995848, 397.423935}, {-0.928034, -0.026307, 0.371566} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[8], bodies[6], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Line3d line1{ {56.827968, -51.824686, 393.482125}, {-0.928034, -0.026307, 0.371566} }; 
		Line3d line2{ {41.051390, -52.271901, 399.798748}, {-0.928034, -0.026307, 0.371566} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[8], bodies[6], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}

	///////////////

	{
		Plane plane1{ {21.603987, -83.995848, 397.423935}, {-0.928034, -0.026307, 0.371566} }; 
		Plane plane2{ {15.884837, -86.803108, 382.940868}, {-0.928034, -0.026307, 0.371566} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[9], bodies[6], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Line3d line1{ {46.639654, -56.008574, 367.739295}, {-0.928034, -0.026307, 0.371566} }; 
		Line3d line2{ {30.863081, -56.455788, 374.055916}, {0.928034, 0.026307, -0.371566} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[9], bodies[6], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}

	///////////////

	{
		Plane plane1{ {75.804508, -58.786436, 386.559356}, {0.363868, 0.149425, 0.919387} };
		Plane plane2{ {73.948441, -58.839050, 387.302488}, {-0.363868, -0.149425, -0.919387} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[10], bodies[6], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Line3d line1{ {73.868734, -57.850627, 387.173389}, {-0.928034, -0.026307, 0.371566} }; 
		Line3d line2{ {75.724801, -57.798013, 386.430257}, {0.928034, 0.026307, -0.371566} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[10], bodies[6], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}

	///////////////

	{
		Plane plane1{ {77.000116, -73.612783, 388.495839}, {0.363868, 0.149425, 0.919387} }; 
		Plane plane2{ {75.144048, -73.665397, 389.238971}, {-0.363868, -0.149425, -0.919387} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[11], bodies[6], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Line3d line1{ {76.920408, -72.624360, 388.366740}, {0.928034, 0.026307, -0.371566} }; 
		Line3d line2{ {75.064341, -72.676973, 389.109871}, {-0.928034, -0.026307, 0.371566} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[11], bodies[6], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}
	///////////////

	{
		Plane plane1{ {91.105911, -112.270003, 374.289492}, {0.079707, -0.988423, 0.129099} };
		Plane plane2{ {56.516238, -113.222017, 388.356642}, {0.079707, -0.988423, 0.129099} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[12], bodies[6], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Line3d line1{ {83.071527, -99.417453, 361.463323}, {-0.079707, 0.988423, -0.129099} };
		Line3d line2{ {82.812479, -96.205077, 361.043751}, {-0.079707, 0.988423, -0.129099} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[12], bodies[6], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}

	////////////////	
	{
		Plane plane1{ {86.566352, -82.154375, 371.414319}, {0.928034, 0.026307, -0.371566} }; 
		Plane plane2{ {84.812794, -60.409066, 368.574144}, {-0.928034, -0.026307, 0.371566} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[6], bodies[0], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Plane plane1{ {86.008402, -75.235414, 370.510627}, {-0.928034, -0.026307, 0.371566} }; 
		Plane plane2{ {86.566352, -82.154375, 371.414319}, {0.928034, 0.026307, -0.371566} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[6], bodies[0], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	//{
	//	Plane plane1{ {21.603987, -83.995848, 397.423935}, {-0.928034, -0.026307, 0.371566} }; 
	//	Plane plane2{ {-63.115742, -107.043206, 184.193755}, {0.928034, 0.026307, -0.371566} };
	//	gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[5], bodies[2], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	//}

	//{
	//	Plane plane1{ {56.516238, -113.222017, 388.356642}, {0.079707, -0.988423, 0.129099} }; 
	//	Plane plane2{ {-24.502757, -147.557320, 175.496401}, {-0.079707, 0.988423, -0.129099} };
	//	gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[5], bodies[2], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	//}

	Point3d oldPos{ 37.450907, -52.006854, 324.145403 }; 
	Point3d newPos{ 37.550764, -51.672222, 324.958980 }; 
	Vector3d view{ 0.880273, -0.466967, 0.084024 }; 
	int mode = 0;

	bodies[0].SetGrounded(true);
	// bodies[6].SetGrounded(true);

	bodies[8].SetCOR(pt3);


	gcs.PrioritizedDrag(bodies[8], oldPos, newPos, view, mode, 1);
	//auto isOk = gcs.Solve(GCSWSolveMode::kNormal, false);
	auto isOk = gcs.Solve();
}

void test_drag10()
{
	Point3d pt30{ -0.578223, 7.092011, 0.598536 };
	GCSWSystem gcs;
	int Bodyid = 0;

	std::vector<GCSWRigidBody> bodies(8);

	for (size_t i = 0; i < 8; i++)
	{
		bodies[i] = gcs.CreateRigidBody(Bodyid);
		Bodyid++;
	}

	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();
	Point3d pt3{ -0.578223, 7.092011, 0.598536 };

	{
		Plane plane1{ {100.038345, 26.422527, 208.610593}, {-0.472837, -0.828512, -0.299987} }; 
		Plane plane2{ {101.860781, 23.801777, 212.976138}, {0.472837, 0.828512, 0.299987} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[0], bodies[1], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Line3d line1{ {99.617428, 26.584625, 208.826354}, {0.260266, -0.456579, 0.850763} }; 
		Line3d line2{ {101.018945, 24.125972, 213.407659}, {0.260266, -0.456579, 0.850763} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[0], bodies[1], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Plane plane1{ {105.608005, 17.804411, 223.633465}, {-0.472837, -0.828512, -0.299987} };
		Plane plane2{ {101.860781, 23.801777, 212.976138}, {0.472837, 0.828512, 0.299987} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[2], bodies[1], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Line3d line1{ {106.028922, 17.642313, 223.417705}, {0.260266, -0.456579, 0.850763} }; 
		Line3d line2{ {102.702616, 23.477581, 212.544616}, {-0.260266, 0.456579, -0.850763} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[2], bodies[1], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Plane plane1{ {77.049235, 20.395520, 189.353069}, {-0.260266, 0.456579, -0.850762} }; 
		Plane plane2{ {73.231008, 21.629653, 191.183469}, {-0.260266, 0.456579, -0.850763} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[4], bodies[3], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Line3d line1{ {100.864375, 47.558797, 226.030657}, {-0.260266, 0.456579, -0.850762} }; 
		Line3d line2{ {100.864375, 47.558797, 226.030657}, {-0.260266, 0.456579, -0.850763} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[4], bodies[3], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Plane plane1{ {77.049235, 20.395520, 189.353069}, {-0.260266, 0.456579, -0.850762} };
		Plane plane2{ {50.682146, -59.252105, 154.674766}, {0.260266, -0.456579, 0.850763} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[4], bodies[1], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Line3d line1{ {65.366102, -29.349117, 195.616098}, {0.260266, -0.456579, 0.850762} }; 
		Line3d line2{ {65.366102, -29.349117, 195.616098}, {-0.260266, 0.456579, -0.850763} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[4], bodies[1], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Plane plane1{ {-142.946681, -125.342539, 197.862393}, {0.041666, -0.998917, 0.020724} }; 
		Plane plane2{ {-126.675916, -124.113373, 178.702606}, {0.071705, -0.992844, 0.095498} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[5], bodies[6], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);

	}

	{
		Line3d line1{ {-128.800160, -94.882375, 190.032688}, {-0.041666, 0.998917, -0.020724} }; 
		Line3d line2{ {-129.273699, -93.020283, 189.769280}, {-0.071705, 0.992844, -0.095498} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[5], bodies[6], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}

	///////////////

	{
		Plane plane1{ {-144.972704, -129.641656, 134.009640}, {0.121852, -0.991906, 0.035712} }; 
		Plane plane2{ {-126.675916, -124.113373, 178.702606}, {0.071705, -0.992844, 0.095498} };
		gcs.Create3dDistPlPl(conHandle, true, pt30, pt30, bodies[7], bodies[6], plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Line3d line1{ {-128.380413, -95.635844, 161.906027}, {-0.071705, 0.992844, -0.095498} }; 
		Line3d line2{ {-132.855437, -98.167385, 126.812971}, {-0.121852, 0.991906, -0.035712} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, bodies[6], bodies[7], line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}


	Point3d oldPos{ -160.176077, -83.256575, 204.064244 }; 
	Point3d newPos{ -160.197216, -83.406869, 204.111356 }; 
	Vector3d view{ 0.882944, -0.248958, -0.398033 }; 
	int mode = 1;

	bodies[1].SetGrounded(true);
	bodies[6].SetGrounded(true);
	bodies[5].SetCOR(pt3);
	gcs.PrioritizedDrag(bodies[5], oldPos, newPos, view, mode, 1);
	//auto isOk = gcs.Solve(GCSWSolveMode::kNormal, false);
	auto isOk = gcs.Solve();
	{
		Plane plane1{ {-142.946681, -125.342539, 197.862393}, {0.041666, -0.998917, 0.020724} };
		Plane plane2{ {-126.675916, -124.113373, 178.702606}, {0.071705, -0.992844, 0.095498} };
		plane1 = gcs.UpdatePlanePosition(bodies[5], plane1);
		plane2 = gcs.UpdatePlanePosition(bodies[6], plane2);
		int a = 1;
	}

}

void test_drag11()
{
	//---------------create3dDistPtPt--------------//
	GCSWSystem gcs;
	int Bodyid = 1;
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;	
	GCSWRigidBody body3 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;

	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();
	Point3d pt33{ -0.578223, 7.092011, 0.598536 };

	{
		Point3d pt1{ -64.657922, 160.284023, -63.888994 };
		Point3d pt3{ -64.657922, 160.284023, -63.888994 };
		gcs.Create3dDistPtPt(conHandle, body1, body2, pt1, pt3, extG1, extG2, 0.0, kGCSEQ, dummyVar);
	}
	{
		Point3d pt1{ -83.354665, 125.254379, -59.056207 };
		Point3d pt3{ -83.354665, 125.254379, -59.056207 };
		gcs.Create3dDistPtPt(conHandle, body3, body1, pt1, pt3, extG1, extG2, 0.0, kGCSEQ, dummyVar);
	}
	{
		Point3d pt1{ -72.251067, 142.061271, -139.085834 };
		Point3d pt3{ -72.251067, 142.061271, -139.085834 };
		gcs.Create3dDistPtPt(conHandle, body3, body2, pt1, pt3, extG1, extG2, 0.0, kGCSEQ, dummyVar);
	}

	Point3d oldPos{ -69.430807, 146.578856, -54.811972 }; 
	Point3d newPos{ -69.339007, 146.800634, -54.847155 }; 
	Vector3d view{ -0.813408, 0.403206, 0.419276 }; 
	int mode = 0;
	gcs.PrioritizedDrag(body1, oldPos, newPos, view, mode, 1);
	//auto isOk = gcs.Solve(GCSWSolveMode::kNormal, false);
	auto isOk = gcs.Solve();
	oldPos = gcs.UpdatePoint3dPosition(body1, oldPos);

}

void test_drag12()
{
	//---------------create3dDistPtPt--------------//
	GCSWSystem gcs;
	int Bodyid = 1;
	GCSWRigidBody body1 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;
	GCSWRigidBody body2 = gcs.CreateRigidBody(Bodyid);
	Bodyid++;

	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	auto conHandle = GCSWConHandle();
	Point3d pt3{ -0.578223, 7.092011, 0.598536 };

	{
		Plane plane1{ {-6.504680, 73.453802, 160.362241}, {0.000000, -1.000000, 0.000000} }; 
		Plane plane2{ {63.461771, 73.089209, 159.976697}, {0.000000, 1.000000, -0.000000} }; 
		gcs.Create3dDistPlPl(conHandle, true, pt3, pt3, body1, body2, plane1, plane2, extG1, extG2, VecSense::kParallel, 0., GCSConEqMode::kGCSEQ, dummyVar);
	}

	{
		Line3d line1{ {-6.504679, 73.453802, 160.862241}, {1.000000, 0.000000, 0.000000} }; 
		Line3d line2{ {63.461771, 73.089208, 160.976697}, {1.000000, -0.000000, -0.000000} };
		gcs.Create3dDistLnLn(conHandle, true, pt3, pt3, body1, body2, line1, line2, extG1, extG2, true, 0.0, VecSense::kParallel, GCSConEqMode::kGCSEQ, dummyVar);
	}

	Point3d oldPos{ 27.942267, 82.309638, 162.243067 }; 
	Point3d newPos{ 28.232683, 82.298836, 162.255014 }; 
	Vector3d view{ 0.036871, -0.107523, -0.993519 }; 
	int mode = 0;

	gcs.PrioritizedDrag(body1, oldPos, newPos, view, mode, 1);
	//auto isOk = gcs.Solve(GCSWSolveMode::kNormal, false);
	auto isOk = gcs.Solve();
	oldPos = gcs.UpdatePoint3dPosition(body1, oldPos);

}

void test_from_log(std::string dir) {
	std::ifstream inputFile(dir);
	if (!inputFile.is_open()) {
		std::cerr << "Failed to open the input file." << std::endl;
		return ;
	}

	std::regex commandRegex(R"(\b(\w+)\b)");
	std::regex numberRegex(R"(([-+]?[0-9]*\.?[0-9]+(?:[eE][-+]?[0-9]+)?))");

	std::string line;
	GCSWSystem gcs;

	while (std::getline(inputFile, line)) {
		if (line.empty()) {
			// to let the system go and make a new system
			//auto isOk = gcs.Solve(GCSWSolveMode::kNormal, false);
			auto isOk = gcs.Solve();
			gcs.Check();
			gcs.Reset();
			continue;
		}
		std::smatch match;

		if (std::regex_search(line, match, commandRegex)) {
			std::string command = match[1].str();
			std::cout << "Command: " << command << std::endl;
			if (command.substr(0, 4) == "Body") {
				int num = std::stoi(command.substr(4));
				std::sregex_iterator iter(line.begin(), line.end(), numberRegex);
				std::sregex_iterator end;
				iter++;
				int num1 = std::stoi(iter->str());
				auto body = gcs.CreateRigidBody(num);
				if (num1 == 1) {
					body.SetGrounded(true);
				}
			}
			if (command == "ProcessDrag") {
				std::sregex_iterator iter(line.begin(), line.end(), numberRegex);
				std::sregex_iterator end;
				int num1 = std::stoi(iter->str());
				++iter; ++iter;
				double op1 = std::stod(iter->str());
				++iter;
				double op2 = std::stod(iter->str());
				++iter;
				double op3 = std::stod(iter->str());
				++iter; ++iter;
				double np1 = std::stod(iter->str());
				++iter;
				double np2 = std::stod(iter->str());
				++iter;
				double np3 = std::stod(iter->str());
				++iter; ++iter;
				double v1 = std::stod(iter->str());
				++iter;
				double v2 = std::stod(iter->str());
				++iter;
				double v3 = std::stod(iter->str());
				++iter;
				int mode = std::stoi(iter->str());
				auto body = gcs.CreateRigidBody(num1);
				Point3d pt_old{ op1,op2,op3 };
				Point3d pt_new{ np1,np2,np3 };
				Vector3d view{ v1,v2,v3 };
				gcs.PrioritizedDrag(body, pt_old, pt_new, view, mode, true);
			}
			else if (command == "PtPtCoinCons" || command == "PtPtDistCons") {
				std::sregex_iterator iter(line.begin(), line.end(), numberRegex);
				std::sregex_iterator end;
				auto body1 = gcs.CreateRigidBody(std::stoi(iter->str()));
				++iter;
				auto body2 = gcs.CreateRigidBody(std::stoi(iter->str()));
				++iter; ++iter;
				double p11 = std::stod(iter->str());
				++iter;
				double p12 = std::stod(iter->str());
				++iter;
				double p13 = std::stod(iter->str());
				++iter; ++iter;
				double p21 = std::stod(iter->str());
				++iter;
				double p22 = std::stod(iter->str());
				++iter;
				double p23 = std::stod(iter->str());
				++iter;
				double d = std::stod(iter->str());
				GCSWConHandle conHandle;
				GCSWVariable gcsvar;
				GCSConEqMode mode{ GCSConEqMode::kGCSEQ };
				Point3d p1{ p11,p12,p13 };
				Point3d p2{ p21,p22,p23 };
				auto extG1 = GCSWExtGeometry();
				auto extG2 = GCSWExtGeometry();
				gcs.Create3dDistPtPt(conHandle,body1,body2,p1,p2,extG1,extG2,d,mode,gcsvar);
			}
			else if (command == "PtLnCoinCons") {
				std::sregex_iterator iter(line.begin(), line.end(), numberRegex);
				std::sregex_iterator end;

				auto body1 = gcs.CreateRigidBody(std::stoi(iter->str()));
				++iter;
				auto body2 = gcs.CreateRigidBody(std::stoi(iter->str()));
				++iter; ++iter;
				double p11 = std::stod(iter->str());
				++iter;
				double p12 = std::stod(iter->str());
				++iter;
				double p13 = std::stod(iter->str());
				++iter; ++iter;
				double p21 = std::stod(iter->str());
				++iter;
				double p22 = std::stod(iter->str());
				++iter;
				double p23 = std::stod(iter->str());
				++iter;
				double dir1 = std::stod(iter->str());
				++iter;
				double dir2 = std::stod(iter->str());
				++iter;
				double dir3 = std::stod(iter->str());
				++iter;
				double d = std::stod(iter->str());

				GCSWConHandle conHandle;
				GCSWVariable gcsvar;
				GCSConEqMode mode{ GCSConEqMode::kGCSEQ };
				Point3d p1{ p11,p12,p13 };
				Point3d p2{ p21,p22,p23 };
				Vector3d dir{ dir1,dir2,dir3 };
				Line3d ln{ p2, dir };
				auto extG1 = GCSWExtGeometry();
				auto extG2 = GCSWExtGeometry();
				gcs.Create3dDistPtLn(conHandle, false, p1, body1, body2, p1, ln, extG1, extG2, d, mode, gcsvar);
			}
			else if (command == "PlPlDistCons") {
				std::sregex_iterator iter(line.begin(), line.end(), numberRegex);
				std::sregex_iterator end;

				auto body1 = gcs.CreateRigidBody(std::stoi(iter->str()));
				++iter;
				auto body2 = gcs.CreateRigidBody(std::stoi(iter->str()));
				++iter; ++iter;++iter;
				double p11 = std::stod(iter->str());
				++iter;
				double p12 = std::stod(iter->str());
				++iter;
				double p13 = std::stod(iter->str());
				++iter;
				double nm1 = std::stod(iter->str());
				++iter;
				double nm2 = std::stod(iter->str());
				++iter;
				double nm3 = std::stod(iter->str());
				++iter; ++iter; ++iter;
				double p21 = std::stod(iter->str());
				++iter;
				double p22 = std::stod(iter->str());
				++iter;
				double p23 = std::stod(iter->str());
				++iter;
				double dir1 = std::stod(iter->str());
				++iter;
				double dir2 = std::stod(iter->str());
				++iter;
				double dir3 = std::stod(iter->str());
				++iter;
				int sense = std::stoi(iter->str());
				++iter;
				double d = std::stod(iter->str());

				GCSWConHandle conHandle;
				GCSWVariable gcsvar;
				GCSConEqMode mode{ GCSConEqMode::kGCSEQ };
				Point3d p1{ p11,p12,p13 };
				Vector3d norm{ nm1,nm2,nm3 };
				Point3d p2{ p21,p22,p23 };
				Vector3d dir{ dir1,dir2,dir3 };
				Plane pl1{ p1,norm };
				Plane pl2{ p2,dir };
				auto extG1 = GCSWExtGeometry();
				auto extG2 = GCSWExtGeometry();
				VecSense ss;
				if (sense == -1) {
					ss = VecSense::kOpposed;
				}
				else if (sense == 0) {
					ss = VecSense::kParallel;
				}
				else {
					ss = VecSense::kCodirectional;
				}
				gcs.Create3dDistPlPl(conHandle,false, p1, p2, body1, body2, pl1, pl2, extG1, extG2, ss, d, mode, gcsvar);
			}
			else if (command == "LnLnCoinCons") {
				std::sregex_iterator iter(line.begin(), line.end(), numberRegex);
				std::sregex_iterator end;

				auto body1 = gcs.CreateRigidBody(std::stoi(iter->str()));
				++iter;
				auto body2 = gcs.CreateRigidBody(std::stoi(iter->str()));
				++iter; ++iter; ++iter;
				double p11 = std::stod(iter->str());
				++iter;
				double p12 = std::stod(iter->str());
				++iter;
				double p13 = std::stod(iter->str());
				++iter;
				double nm1 = std::stod(iter->str());
				++iter;
				double nm2 = std::stod(iter->str());
				++iter;
				double nm3 = std::stod(iter->str());
				++iter; ++iter; ++iter;
				double p21 = std::stod(iter->str());
				++iter;
				double p22 = std::stod(iter->str());
				++iter;
				double p23 = std::stod(iter->str());
				++iter;
				double dir1 = std::stod(iter->str());
				++iter;
				double dir2 = std::stod(iter->str());
				++iter;
				double dir3 = std::stod(iter->str());
				++iter;
				int sense = std::stoi(iter->str());
				++iter;
				double d = std::stod(iter->str());

				GCSWConHandle conHandle;
				GCSWVariable gcsvar;
				GCSConEqMode mode{ GCSConEqMode::kGCSEQ };
				Point3d p1{ p11,p12,p13 };
				Vector3d norm{ nm1,nm2,nm3 };
				Point3d p2{ p21,p22,p23 };
				Vector3d dir{ dir1,dir2,dir3 };
				Line3d l1{ p1,norm };
				Line3d l2{ p2,dir };
				auto extG1 = GCSWExtGeometry();
				auto extG2 = GCSWExtGeometry();
				VecSense ss;
				if (sense == -1) {
					ss = VecSense::kOpposed;
				}
				else if (sense == 0) {
					ss = VecSense::kParallel;
				}
				else {
					ss = VecSense::kCodirectional;
				}
				gcs.Create3dDistLnLn(conHandle, false, p1, p2, body1, body2, l1, l2, extG1, extG2, true, d, ss, mode, gcsvar);
			}
			std::cout << std::endl;
		}
	}

	inputFile.close();

	return ;
}

END_GCS_EXPERIMENTAL_NAMESPACE
END_GCS_NAMESPACE