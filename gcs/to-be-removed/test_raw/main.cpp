#include "unit_test.h"
#include <chrono>
#include <fstream>
#include "so3.hpp"
#include "Eigen/Core"
#include "geometry.hpp"

using namespace AMCAX::GCS;
using namespace AMCAX::GCS::Experimental;

void recordRuntime(std::ofstream& outputFile, const std::string& functionName, std::chrono::duration<double> runtime)
{
	outputFile << functionName << ": " << runtime.count() << " seconds\n";
}

void test_Lie() {
	Eigen::Vector3d u = { 1,1,1 };
	u.normalize();

	auto t = Eigen::AngleAxisd(0.5, u).matrix();
	Sophus::SO3d locc(t);

	Eigen::Vector3d v_tg = { 1,2,3 };


	// Assuming u is a Vector3d object
	Eigen::Matrix3d u_cross_u_transpose;
	Eigen::Matrix3d u_skew_symmetric;

	u_cross_u_transpose = u * u.transpose();

	u_skew_symmetric << 0, -u[2], u[1],
		u[2], 0, -u[0],
		-u[1], u[0], 0;

	Eigen::Vector3d rot_center = { 1,1,1 };

	auto result = locc.jacobian_mult_vector_exact(v_tg - rot_center);
	Eigen::Vector3d tt;
	tt << u(0), u(1), u(2);
	Eigen::Vector3d tc;
	tc << rot_center(0), rot_center(1), rot_center(2);
	std::cout << "Lie and particial  is:" << result * tt << std::endl;

	Eigen::AngleAxisd R(1e-10, u);
	std::cout << "true result is:" << (R * t * (v_tg - rot_center) - t * (v_tg - rot_center)) / 1e-10 << std::endl;

}

double single_test(std::string filename)
{
	std::cout << "start solving " << filename << std::endl;
	std::ifstream inf;
	inf.open(filename, std::ios::in);
	if (!inf.is_open()) {
		std::cout << "read file failed!" << std::endl;
		return 0;
	}
	std::string s;
	std::stringstream ss;
	Status solStatus;
	GCSWSystem sys;
	auto conHandle = GCSWConHandle();
	auto dummyVar = GCSWVariable();
	auto extG1 = GCSWExtGeometry();
	auto extG2 = GCSWExtGeometry();
	GCSWRigidBody EBRb1;
	GCSWRigidBody EBRb2;
	GCSConEqMode mode{ GCSConEqMode::kGCSEQ };
	VecSense sense{ kOpposed };
	Point3d pt1, pt2, bias1, bias2;
	Vector3d vc1, vc2;
	Eigen::Vector4d p1, p2, v1, v2;
	p1(3) = 1; p2(3) = 1; v1(3) = 0; v2(3) = 0;
	int maxbodyid = -1;
	int bid1, bid2;
	bool sequence = false;
	bool special = false;
	//std::vector<assconstraint*> cons;
	//std::vector<Eigen::Matrix4d> bodies;
	std::unordered_map<int, Eigen::Matrix4d> bodies;
	std::vector<Matrix3d> trans;
	while (getline(inf, s))
	{
		ss.str(s);
		std::string single;
		int type = -1;
		int i = 0;
		while (getline(ss, single, ';'))
		{
			if (i == 0) // constraint type
			{
				type = std::atoi(single.c_str());
			}
			else if (i == 1) // creat rigid body
			{
				std::istringstream iss(single);
				std::string id;
				iss >> id;
				bid1 = std::stoi(id);
				iss >> id;
				bid2 = std::stoi(id);
				maxbodyid = std::max(maxbodyid, std::max(bid1, bid2));
				EBRb1 = sys.CreateRigidBody(bid1);
				EBRb2 = sys.CreateRigidBody(bid2);
			}
			else if (i == 2)
			{
				if (type == 5 || type == 8 || type == 10)
				{
					std::istringstream iss(single);
					std::string id;
					iss >> id; pt1.x = std::stod(id);
					iss >> id; pt1.y = std::stod(id);
					iss >> id; pt1.z = std::stod(id);
					iss >> id; pt2.x = std::stod(id);
					iss >> id; pt2.y = std::stod(id);
					iss >> id; pt2.z = std::stod(id);
					iss >> id; vc2.x = std::stod(id);
					iss >> id; vc2.y = std::stod(id);
					iss >> id; vc2.z = std::stod(id);

				}
				else if (type == 4 || type == 9)
				{
					std::istringstream iss(single);
					std::string id;
					iss >> id; pt1.x = std::stod(id);
					iss >> id; pt1.y = std::stod(id);
					iss >> id; pt1.z = std::stod(id);
					iss >> id; pt2.x = std::stod(id);
					iss >> id; pt2.y = std::stod(id);
					iss >> id; pt2.z = std::stod(id);
				}
				else if (type != 3 && type != 7)
				{
					std::istringstream iss(single);
					std::string id;
					iss >> id; pt1.x = std::stod(id);
					iss >> id; pt1.y = std::stod(id);
					iss >> id; pt1.z = std::stod(id);
					iss >> id; vc1.x = std::stod(id);
					iss >> id; vc1.y = std::stod(id);
					iss >> id; vc1.z = std::stod(id);
					iss >> id; pt2.x = std::stod(id);
					iss >> id; pt2.y = std::stod(id);
					iss >> id; pt2.z = std::stod(id);
					iss >> id; vc2.x = std::stod(id);
					iss >> id; vc2.y = std::stod(id);
					iss >> id; vc2.z = std::stod(id);

				}
				else
				{
					std::istringstream iss(single);
					std::string id;
					iss >> id; vc1.x = std::stod(id);
					iss >> id; vc1.y = std::stod(id);
					iss >> id; vc1.z = std::stod(id);
					iss >> id; vc2.x = std::stod(id);
					iss >> id; vc2.y = std::stod(id);
					iss >> id; vc2.z = std::stod(id);
				}
			}
			else if (i == 3) //is filped
			{
				if (std::stoi(single))
					sense = kOpposed;
				else
					sense = kCodirectional;
			}
			i++;
		}
		ss.clear();
		// add constraint
		switch (type)
		{
		case 1:
		{
			Line3d line1{ pt1,vc1 };
			Line3d line2{ pt2,vc2 };
			sys.Create3dDistLnLn(conHandle, false, bias1, bias2, EBRb1, EBRb2, line1, line2, extG1, extG2, true, 0, sense, mode, dummyVar);
			//cons.push_back(new lnlncons(bid1, bid2, ConsType::LNLNCOIN, line1, line2,sense));
			break;
		}
		case 2:
		{
			Plane plane1{ pt1,vc1 };
			Plane plane2{ pt2,vc2 };
			sys.Create3dDistPlPl(conHandle, false, bias1, bias2, EBRb1, EBRb2, plane1, plane2, extG1, extG2, sense, 0, mode, dummyVar);
			//cons.push_back(new plplcons(bid1, bid2, ConsType::PLPLDIST, plane1, plane2,sense));
			break;
		}
		case 3:
		{
			sys.Create3dAngVecVec(conHandle, false, bias1, bias2, EBRb1, EBRb2, vc1, vc2, extG1, extG2, sense, 0, mode, EBRb1, vc1, extG1, conHandle, dummyVar);
			break;
		}
		case 4:
			sys.Create3dDistPtPt(conHandle, EBRb1, EBRb2, pt1, pt2, extG1, extG2, 0., mode, dummyVar);
			//cons.push_back(new ptptcons(bid1, bid2, ConsType::PTPTCOIN, pt1, pt2));
			break;
		case 5:
		{
			Line3d line1{ pt2,vc2 };
			sys.Create3dDistPtLn(conHandle, false, pt1, EBRb1, EBRb2, pt1, line1, extG1, extG2, 0, GCSConEqMode::kGCSEQ, dummyVar);
			//cons.push_back(new ptlncons(bid1, bid2, ConsType::PTLNCOIN, pt1, line1));
			break;
		}
		default:
			break;
		}
	}
	//resize vector
	//bodies.resize(maxbodyid + 1);
	//trans.resize(maxbodyid + 1);
	//initialize transform
	//init_trans(trans, bodies, cons,AddConsType::ANGLE, maxbodyid + 1);
	//solve
	double duration_millsecond = 0.0;
	if (!sequence) {
		//add_cons(sys, cons, trans);
		auto beforeTime = std::chrono::steady_clock::now();
		time_t t1 = clock();
		solStatus = sys.Solve();
		time_t t2 = clock();
		std::cout << "total time: " << t2 - t1 << std::endl;
		auto afterTime = std::chrono::steady_clock::now();
		duration_millsecond = std::chrono::duration<double, std::milli>(afterTime - beforeTime).count();
	}
	else {
		/*for (int i = 0; i < cons.size(); i++) {
			std::vector<assconstraint*>::const_iterator first = cons.begin();
			std::vector<assconstraint*>::const_iterator fin = cons.begin() + i;
			std::vector<assconstraint*> cons_part(first, fin);
			add_cons(sys, cons_part, trans);
			auto beforeTime = std::chrono::steady_clock::now();
			solStatus = sys.solve();
			auto afterTime = std::chrono::steady_clock::now();
			duration_millsecond += std::chrono::duration<double, std::milli>(afterTime - beforeTime).count();
			update_all_trans(sys, trans);
		}*/
	}


	if (solStatus == kSolved)
	{
		std::cout << "solve successfully" << std::endl;
	}
	else {
		std::cout << "solve failed\n";
	}
	/*else
		still_fail.push_back(filename);*/
	inf.close();
	return duration_millsecond;
}

int main() {
	// test_Lie();
	// single_test("123496_74cb10dc.txt");
	test_from_log("alog.txt");
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks();
#endif // _MSC_VER
	return 0;
}

