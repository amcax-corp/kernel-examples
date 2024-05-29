#ifndef TEST_SOLVER_H_
#define TEST_SOLVER_H_

#include <cmath>
#include <iostream>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include "se3.hpp"

#define M_PI 3.1415926

auto randfun = []()->double {return (rand() % 101) / 100.0 * 2. - 1.; };

class TestADMM {
public:
	void ADMMSolver() {
		Eigen::Quaterniond quaternion1(0., 0., 0., 1.);
		quaternion1.normalize();
		Eigen::Vector3d translate1(2., 2., 2.);
		//transform1
		Sophus::SE3d transform1(quaternion1, translate1);
		
		Eigen::Quaterniond quaternion2(0., 0., 0., 1.);
		quaternion2.normalize();
		Eigen::Vector3d translate2(0., 0., 0.);
		//transform2
		Sophus::SE3d transform2(quaternion2, translate2);

		Eigen::Vector3d dir1(1, 1, 1);
		dir1.normalize();
		Eigen::Vector3d d1ir1(0, 1, 0);
		d1ir1.normalize();

		Eigen::Vector3d ori1(0, 0, 0);
		Eigen::Vector3d o1ri1(1, 1, 10);

		Eigen::Vector3d dir2(0, 1, 0);
		dir2.normalize();
		Eigen::Vector3d d2ir2(1, 1, 1);
		d2ir2.normalize();

		Eigen::Vector3d ori2(1, 1, 10);
		Eigen::Vector3d o2ri2(0, 0, 0);

		Eigen::Vector3d direction1 = transform1.rotationMatrix().inverse() * dir1;
		Eigen::Vector3d plane2_normal = transform2.rotationMatrix().inverse() * dir2;

		Eigen::Vector3d direction2 = transform1.rotationMatrix().inverse() * d1ir1;
		Eigen::Vector3d plane1_normal = transform2.rotationMatrix().inverse() * d2ir2;

		Eigen::Vector3d point1 = transform1.inverse() * ori1;
		Eigen::Vector3d point2 = transform1.inverse() * o1ri1;
		Eigen::Vector3d plane2_origin = transform2.inverse() * ori2;
		Eigen::Vector3d plane1_origin = transform2.inverse() * o2ri2;

		//dot(dir1,dir2)+1=0;
		int iter = 0;

		int cons_num = 4;
		std::vector<Sophus::SE3d> aux1, aux2;
		aux1.resize(cons_num, transform1);
		aux2.resize(cons_num, transform2);

		std::vector<Eigen::Vector<double, 6>> dual1, dual2;
		dual1.resize(cons_num, Eigen::Vector<double, 6>::Zero());
		dual2.resize(cons_num, Eigen::Vector<double, 6>::Zero());

		//init satisfy constraint
		{
			VecVecCoinOpt(aux1[0], aux2[0], direction1, plane1_normal, true);
			VecVecCoinOpt(aux1[1], aux2[1], direction2, plane2_normal, true);
			PtPlDistOpt(aux1[2], aux2[2], point1, plane1_origin, plane1_normal, kTargetDistanceForC3);
			PtPlDistOpt(aux1[3], aux2[3], point2, plane2_origin, plane2_normal, 0);
		}

		while (iter < 200) {
			double prev_e = 0;
			{
				double redisual1 = (transform1.so3() * direction1).dot(transform2.so3() * plane1_normal) + 1.;
				double redisual2 = (transform1.so3() * direction2).dot(transform2.so3() * plane2_normal) + 1.;
				double redisual3 = (transform1 * point1 - transform2 * plane1_origin).dot(transform2.so3() * plane1_normal) - kTargetDistanceForC3;
				double redisual4 = (transform1 * point2 - transform2 * plane2_origin).dot(transform2.so3() * plane2_normal);

				Eigen::VectorXd b(4);
				b[0] = -redisual1;
				b[1] = -redisual2;
				b[2] = -redisual3;
				b[3] = -redisual4;
				
				double lala = 0.;
				for (size_t i = 0; i < cons_num; i++) {
					Eigen::Vector<double, 6> new1 = transform1.log() - aux1[i].log() + dual1[i];
					Eigen::Vector<double, 6> new2 = transform2.log() - aux2[i].log() + dual2[i];
					lala += new1.squaredNorm();
					lala += new2.squaredNorm();
					lala -= dual1[i].squaredNorm();
					lala -= dual2[i].squaredNorm();
				}
				prev_e = b.squaredNorm();
				std::cout << lala << " vs " << iter << " vs " << b.transpose() << " vs " << b.squaredNorm() << std::endl;
				if (iter == 4) {
					for (size_t i = 0; i < cons_num; i++) {
						dual1[i] = Eigen::Vector<double, 6>::Zero();
						dual2[i] = Eigen::Vector<double, 6>::Zero();
					}
				}
			}

			iter++;
			Sophus::SE3d prev_transform1 = transform1;
			Sophus::SE3d prev_transform2 = transform2;
			//done
			//update A B
			{
				Eigen::Vector<double, 6> new_omega_theta1 = Eigen::Vector<double, 6>::Zero();
				Eigen::Vector<double, 6> new_omega_theta2 = Eigen::Vector<double, 6>::Zero();
				for (size_t i = 0; i < cons_num; i++) {
					new_omega_theta1 += (aux1[i].log() - dual1[i]);
					new_omega_theta2 += (aux2[i].log() - dual2[i]);
				}
				new_omega_theta1 /= cons_num;
				new_omega_theta2 /= cons_num;
				transform1 = Sophus::SE3d::exp(new_omega_theta1);
				transform2 = Sophus::SE3d::exp(new_omega_theta2);
			}

			double cur_e = 0;
			{
				double redisual1 = (transform1.so3() * direction1).dot(transform2.so3() * plane1_normal) + 1.;
				double redisual2 = (transform1.so3() * direction2).dot(transform2.so3() * plane2_normal) + 1.;
				double redisual3 = (transform1 * point1 - transform2 * plane1_origin).dot(transform2.so3() * plane1_normal) - kTargetDistanceForC3;
				double redisual4 = (transform1 * point2 - transform2 * plane2_origin).dot(transform2.so3() * plane2_normal);
				Eigen::VectorXd b(4);
				b[0] = -redisual1;
				b[1] = -redisual2;
				b[2] = -redisual3;
				b[3] = -redisual4;
				cur_e = b.squaredNorm();
				std::cout << " cur " << cur_e << " prev " << prev_e << std::endl;
				if (cur_e > prev_e) {
					transform1 = prev_transform1;
					transform2 = prev_transform2;
					for (size_t i = 0; i < cons_num; i++) {
						dual1[i] = Eigen::Vector<double, 6>::Zero();
						dual2[i] = Eigen::Vector<double, 6>::Zero();
						aux1[i] = prev_transform1;
						aux2[i] = prev_transform2;
					}
				}
			}
			//update Ai Bi
			{
				double lala1 = 0.;
#pragma omp parallel for
				for (int i = 0; i < cons_num; i++) {
					Eigen::Vector<double, 6> new1 = transform1.log() - aux1[i].log() + dual1[i];
					Eigen::Vector<double, 6> new2 = transform2.log() - aux2[i].log() + dual2[i];
					lala1 += new1.squaredNorm();
					lala1 += new2.squaredNorm();
				}
#pragma omp parallel for
				for (int i = 0; i < cons_num; i++) {
					//Eigen::Vector<double, 12> ddir, tang;
					//ddir.topRows(6) = -2. * (aux1[i].log() - transform1.log() - dual1[i]);
					//ddir.bottomRows(6) = -2. * (aux2[i].log() - transform2.log() - dual2[i]);
					//if (i == 0) {
					//	tang.topRows(6) = aux1[i].jacobian_mult_vector_exact(direction1, true).transpose() * (aux2[i].so3() * plane1_normal);
					//	tang.bottomRows(6) = aux2[i].jacobian_mult_vector_exact(plane1_normal, true).transpose() * (aux1[i].so3() * direction1);
					//}
					//else if (i == 1) {
					//	tang.topRows(6) = aux1[i].jacobian_mult_vector_exact(direction2, true).transpose() * (aux2[i].so3() * plane2_normal);
					//	tang.bottomRows(6) = aux2[i].jacobian_mult_vector_exact(plane2_normal, true).transpose() * (aux1[i].so3() * direction2);
					//}
					//else if (i == 2) {
					//	tang.topRows(6) = aux1[i].jacobian_mult_vector_exact(point1).transpose() * (aux2[i].so3() * plane1_normal);
					//	tang.bottomRows(6) = aux2[i].jacobian_mult_vector_exact(plane1_normal, true).transpose() * (aux1[i] * point1 - aux2[i] * plane1_origin) - aux2[i].jacobian_mult_vector_exact(plane1_origin).transpose() * (aux2[i].so3() * plane1_normal);
					//}
					//else if (i == 3) {
					//	tang.topRows(6) = aux1[i].jacobian_mult_vector_exact(point2).transpose() * (aux2[i].so3() * plane2_normal);
					//	tang.bottomRows(6) = aux2[i].jacobian_mult_vector_exact(plane2_normal, true).transpose() * (aux1[i] * point2 - aux2[i] * plane2_origin) - aux2[i].jacobian_mult_vector_exact(plane2_origin).transpose() * (aux2[i].so3() * plane2_normal);
					//}

					//tang.normalize();
					//ddir = ddir - ddir.dot(tang) * tang;

					////line search to init the Ai Bi
					//Eigen::Vector<double, 12> residualAB;
					//residualAB.topRows(6) = transform1.log() + dual1[i] - aux1[i].log();
					//residualAB.bottomRows(6) = transform2.log() + dual2[i] - aux2[i].log();

					////todo rewrite the linesearch
					//double step = ddir.dot(residualAB) / ddir.squaredNorm();
					//if (ddir.squaredNorm() < 1e-10) {
					//	step = 0.;
					//}
					//Eigen::Vector<double, 6> new_omega_theta1 = aux1[i].log() + step * ddir.topRows(6);
					//Eigen::Vector<double, 6> new_omega_theta2 = aux2[i].log() + step * ddir.bottomRows(6);
					//aux1[i] = Sophus::SE3d::exp(new_omega_theta1);
					//aux2[i] = Sophus::SE3d::exp(new_omega_theta2);

					//solve the C(Ai, Bi) = 0
					switch (i) {
					case 0: {
						VecVecCoinOpt(aux1[0], aux2[0], direction1, plane1_normal, true);
						break;
					}
					case 1: {
						VecVecCoinOpt(aux1[1], aux2[1], direction2, plane2_normal, true);
						break;
					}
					case 2: {
						PtPlDistOpt(aux1[2], aux2[2], point1, plane1_origin, plane1_normal, kTargetDistanceForC3);
						break;
					}
					case 3: {
						PtPlDistOpt(aux1[3], aux2[3], point2, plane2_origin, plane2_normal, 0);
						break;
					}
					default:
						break;
					}
				}

				double lala2 = 0.;
				for (size_t i = 0; i < cons_num; i++) {
					Eigen::Vector<double, 6> new1 = transform1.log() - aux1[i].log() + dual1[i];
					Eigen::Vector<double, 6> new2 = transform2.log() - aux2[i].log() + dual2[i];
					lala2 += new1.squaredNorm();
					lala2 += new2.squaredNorm();
				}
				std::cout << lala1 << " > " << lala2 << " istrue: " << (lala1 > lala2) << std::endl;
			}

			//update dual
			for (size_t i = 0; i < cons_num; i++) {
				dual1[i] += (transform1.log() - aux1[i].log());
				dual2[i] += (transform2.log() - aux2[i].log());
			}
		}
	}

private:
    const double kTargetDistanceForC3 = 1000;

	//显示求解
	//inverse parallel
	bool VecVecCoinOpt(Sophus::SE3d& transform1, Sophus::SE3d& transform2, const Eigen::Vector3d& direction1, const Eigen::Vector3d& direction2, bool is_inverse) {
		double target = is_inverse ? -1 : 1;
		double redisual = (transform1.so3() * direction1).dot(transform2.so3() * direction2) - target;
		auto vector1 = transform1.so3() * direction1;
		auto vector2 = transform2.so3() * direction2;
		double cos_theta = vector1.dot(vector2);
		if (std::abs(redisual) < 1e-7) {
			return true;
		}
		double angle;
		if (cos_theta >= 1.0) {
			angle = 0.;
		}
		else if (cos_theta <= -1.0) {
			angle = M_PI;
		}
		else {
			angle = std::acos(cos_theta);
		}
		auto normal_vector = vector2.cross(vector1);
		if (normal_vector.norm() < 1e-6) {
			if (std::abs(vector1.x()) > std::abs(vector1.y())) {
				normal_vector = Eigen::Vector3d(-vector1.z(), 0., vector1.x());
			}
			else {
				normal_vector = Eigen::Vector3d(0., -vector1.z(), vector1.y());
			}
		}
		normal_vector.normalize();
		double angle1 = -angle / 2;
		double angle2 = angle / 2;
		if (is_inverse) {
			angle1 = (M_PI - angle) / 2.;
			angle2 = -(M_PI - angle) / 2.;
		}
		Eigen::AngleAxisd angle_axis1(angle1, normal_vector);
		Eigen::Quaterniond quaternion1 = Eigen::Quaterniond(angle_axis1);
		quaternion1 = quaternion1 * transform1.unit_quaternion();
		quaternion1.normalize();
		transform1 = Sophus::SE3d(quaternion1, transform1.translation());
		Eigen::AngleAxisd angle_axis2(angle2, normal_vector);
		Eigen::Quaterniond quaternion2 = Eigen::Quaterniond(angle_axis2);
		quaternion2 = quaternion2 * transform2.unit_quaternion();
		quaternion2.normalize();
		transform2 = Sophus::SE3d(quaternion2, transform2.translation());
		redisual = (transform1.so3() * direction1).dot(transform2.so3() * direction2) - target;
		return std::abs(redisual) < 1e-7;
	}

	bool PtPlDistOpt(Sophus::SE3d& transform1, Sophus::SE3d& transform2, const Eigen::Vector3d& point, const Eigen::Vector3d& plane_origin, const Eigen::Vector3d& plane_normal, double param) {
		double residual = (transform1 * point - transform2 * plane_origin).dot(transform2.so3() * plane_normal) - param;
		if (std::abs(residual) < 1e-7) {
			return true;
		}
		auto p = transform1 * point;
		auto origin = transform2 * plane_origin;
		auto normal = transform2.so3() * plane_normal;
		normal.normalize();
		Eigen::Vector3d projection = ((p - origin).dot(normal)) * normal;
		double distance = projection.norm();
		if (projection.norm() < 1e-7) {
			projection = normal;
			projection.normalize();
		}
		else {
			projection.normalize();
		}
		double move = (distance - param) / 2.;
		auto point_move = -move * projection;
		auto plane_move = move * projection;
		transform1 = Sophus::SE3d(transform1.unit_quaternion(), transform1.translation() + point_move);
		transform2 = Sophus::SE3d(transform2.unit_quaternion(), transform2.translation() + plane_move);
		residual = (transform1 * point - transform2 * plane_origin).dot(transform2.so3() * plane_normal) - param;
		return std::abs(residual) < 1e-7;
	}

	bool opt11(Sophus::SE3d& lc1, Sophus::SE3d& lc2, const Eigen::Vector3d& direction1, const Eigen::Vector3d& direction2) {
		double redisual1 = (lc1.so3() * direction1).dot(lc2.so3() * direction2) + 1.;
		Eigen::VectorXd b(1);
		b[0] = -redisual1;
		auto vector1 = lc1.so3() * direction1;
		auto vector2 = lc2.so3() * direction2;
		double cos_theta = vector1.dot(vector2);
		if (std::abs(redisual1) < 1e-7) {
			return true;
		}
		double angle;
		if (cos_theta >= 1.0) {
			angle = 0.;
		}
		else if (cos_theta <= -1.0) {
			angle = M_PI;
		}
		else {
			angle = std::acos(cos_theta);
		}
		auto normal_vector = vector2.cross(vector1);
		if (normal_vector.norm() < 1e-6) {
			if (std::abs(vector1.x()) > std::abs(vector1.y())) {
				normal_vector = Eigen::Vector3d(-vector1.z(), 0., vector1.x());
			}
			else {
				normal_vector = Eigen::Vector3d(0., -vector1.z(), vector1.y());
			}
		}
		normal_vector.normalize();
		angle = (M_PI - angle) / 2.;
		Eigen::AngleAxisd angle_axisd1(angle, normal_vector);
		Eigen::Quaterniond quaternion1 = Eigen::Quaterniond(angle_axisd1);
		quaternion1 = quaternion1 * lc1.unit_quaternion();
		quaternion1.normalize();
		lc1 = Sophus::SE3d(quaternion1, lc1.translation());
		Eigen::AngleAxisd angle_axisd2(-angle, normal_vector);
		Eigen::Quaterniond quaternion2 = Eigen::Quaterniond(angle_axisd2);
		quaternion2 = quaternion2 * lc2.unit_quaternion();
		quaternion2.normalize();		
		lc2 = Sophus::SE3d(quaternion2, lc2.translation());

		redisual1 = (lc1.so3() * direction1).dot(lc2.so3() * direction2) + 1.;
		return std::abs(redisual1) < 1e-7;
	}

	//解方程
	bool opt1(Sophus::SE3d& lc1, Sophus::SE3d& lc2, const Eigen::Vector3d& direction1, const Eigen::Vector3d& direction2) {
		//Eigen::Vector3d new_omega1 = lc1.so3().log() + Eigen::Vector3d(randfun(), randfun(), randfun()) * 1e-5;
		//lc1.so3() = Sophus::SO3d::exp(new_omega1);
		Eigen::Vector3d new_omega2 = lc2.so3().log() + Eigen::Vector3d(randfun(), randfun(), randfun()) * 1e-5;
		lc2.so3() = Sophus::SO3d::exp(new_omega2);

		int iter = 0;
		while (iter < 100) {
			double redisual1 = (lc1.so3() * direction1).dot(lc2.so3() * direction2) + 1.;
			Eigen::VectorXd b(1);
			b[0] = -redisual1;
			iter++;
			if (std::abs(redisual1) < 1e-8) {
				return true;
			}
			Eigen::SparseMatrix<double> jacobian;
			jacobian.setZero();
			jacobian.resize(1, 12);
			auto jacobian0 = lc1.jacobian_mult_vector_exact(direction1, true).transpose() * (lc2.so3() * direction2);
			auto jacobian1 = lc2.jacobian_mult_vector_exact(direction2, true).transpose() * (lc1.so3() * direction1);
			for (size_t i = 0; i < 6; i++) {
				jacobian.insert(0, i) = jacobian0[i];
				jacobian.insert(0, 6 + i) = jacobian1[i];
			}
			Eigen::SparseMatrix<double> AAt = jacobian * jacobian.transpose();
			Eigen::SparseQR<Eigen::SparseMatrix<double>, Eigen::COLAMDOrdering<int>> solver;
			solver.compute(AAt);
			Eigen::VectorXd z = solver.solve(b);
			Eigen::VectorXd x = jacobian.transpose() * z;
			Eigen::Vector<double, 6> new_omega_theta1 = lc1.log() + x.topRows(6);
			Eigen::Vector<double, 6> new_omega_theta2 = lc2.log() + x.bottomRows(6);
			lc1 = Sophus::SE3d::exp(new_omega_theta1);
			lc2 = Sophus::SE3d::exp(new_omega_theta2);
		}

		return false;
	}

	//inverse parallel
	bool opt22(Sophus::SE3d& lc1, Sophus::SE3d& lc2, const Eigen::Vector3d& direction1, const Eigen::Vector3d& direction2) {
		double redisual2 = (lc1.so3() * direction1).dot(lc2.so3() * direction2) + 1.;
		Eigen::VectorXd b(1);
		b[0] = -redisual2;
		auto vector1 = lc1.so3() * direction1;
		auto vector2 = lc2.so3() * direction2;
		double cos_theta = vector1.dot(vector2);
		if (std::abs(redisual2) < 1e-7) {
			return true;
		}
		double angle;
		if (cos_theta >= 1.0) {
			angle = 0.;
		}
		else if (cos_theta <= -1.0) {
			angle = M_PI;
		}
		else {
			angle = std::acos(cos_theta);
		}
		auto normal_vector = vector2.cross(vector1);
		if (normal_vector.norm() < 1e-6) {
			if (std::abs(vector1.x()) > std::abs(vector1.y())) {
				normal_vector = Eigen::Vector3d(-vector1.z(), 0., vector1.x());
			}
			else {
				normal_vector = Eigen::Vector3d(0., -vector1.z(), vector1.y());
			}
		}
		normal_vector.normalize();
		angle = (M_PI - angle) / 2.;
		Eigen::AngleAxisd angle_axisd1(angle, normal_vector);
		Eigen::Quaterniond quaternion1 = Eigen::Quaterniond(angle_axisd1) * lc1.unit_quaternion();
		quaternion1.normalize();
		lc1 = Sophus::SE3d(quaternion1, lc1.translation());
		Eigen::AngleAxisd angle_axisd2(-angle, normal_vector);
		Eigen::Quaterniond quaternion2 = Eigen::Quaterniond(angle_axisd2) * lc2.unit_quaternion();
		quaternion2.normalize();
		lc2 = Sophus::SE3d(quaternion2, lc2.translation());

		redisual2 = (lc1.so3() * direction1).dot(lc2.so3() * direction2) + 1.;
		return std::abs(redisual2) < 1e-7;
	}

	bool opt2(Sophus::SE3d& lc1, Sophus::SE3d& lc2, const Eigen::Vector3d& direction1, const Eigen::Vector3d& direction2){
		//Eigen::Vector3d new_omega1 = lc1.so3().log() + Eigen::Vector3d(randfun(), randfun(), randfun()) * 1e-5;
		//lc1.so3() = Sophus::SO3d::exp(new_omega1);
		Eigen::Vector3d new_omega2 = lc2.so3().log() + Eigen::Vector3d(randfun(), randfun(), randfun()) * 1e-5;
		lc2.so3() = Sophus::SO3d::exp(new_omega2);
		int iter = 0;
		while (iter < 100)		{
			double redisual2 = (lc1.so3() * direction1).dot(lc2.so3() * direction2) + 1.;
			Eigen::VectorXd b(1);
			b[0] = -redisual2;
			iter++;
			if (std::abs(redisual2) < 1e-8) {
				return true;
			}
			Eigen::SparseMatrix<double> jacobian;
			jacobian.setZero();
			jacobian.resize(1, 12);
			auto jacobian0 = lc1.jacobian_mult_vector_exact(direction1, true).transpose() * (lc2.so3() * direction2);
			auto jacobian1 = lc2.jacobian_mult_vector_exact(direction2, true).transpose() * (lc1.so3() * direction1);
			for (size_t i = 0; i < 6; i++){
				jacobian.insert(0, i) = jacobian0[i];
				jacobian.insert(0, 6 + i) = jacobian1[i];
			}
			Eigen::SparseMatrix<double> AAt = jacobian * jacobian.transpose();
			Eigen::SparseQR<Eigen::SparseMatrix<double>, Eigen::COLAMDOrdering<int>> solver;
			solver.compute(AAt);
			Eigen::VectorXd z = solver.solve(b);
			Eigen::VectorXd x = jacobian.transpose() * z;
			Eigen::Vector<double, 6> new_omega_theta1 = lc1.log() + x.topRows(6);
			Eigen::Vector<double, 6> new_omega_theta2 = lc2.log() + x.bottomRows(6);
			lc1 = Sophus::SE3d::exp(new_omega_theta1);
			lc2 = Sophus::SE3d::exp(new_omega_theta2);
		}
		return false;

	}

	//distance from point to plane?
	bool opt33(Sophus::SE3d& lc1, Sophus::SE3d& lc2, const Eigen::Vector3d& point, const Eigen::Vector3d& plane_origin, const Eigen::Vector3d& plane_normal) {
		double residual3 = (lc1 * point - lc2 * plane_origin).dot(lc2.so3() * plane_normal) - kTargetDistanceForC3;
		Eigen::VectorXd b(1);
		b[0] = -residual3;
		if (std::abs(residual3) < 1e-7) {
			return true;
		}
		auto p = lc1 * point;
		auto origin = lc2 * plane_origin;
		auto normal = lc2.so3() * plane_normal;
		normal.normalize();
		Eigen::Vector3d dd = ((p - origin).dot(normal)) * normal;
		Eigen::Vector3d d1, d2;
		double ddnorm = (p - origin).dot(normal);
		if (ddnorm < kTargetDistanceForC3)		{
			double mvm = (kTargetDistanceForC3 - ddnorm) / 2.;
			d1 = mvm * normal;
			d2 = -mvm * normal;
		}
		else {
			double mvm = (ddnorm - kTargetDistanceForC3) / 2.;
			d1 = -mvm * normal;
			d2 = mvm * normal;
		}
		lc1 = Sophus::SE3d(lc1.unit_quaternion(), lc1.translation() + d1);
		lc2 = Sophus::SE3d(lc2.unit_quaternion(), lc2.translation() + d2);
		residual3 = (lc1 * point - lc2 * plane_origin).dot(lc2.so3() * plane_normal) - kTargetDistanceForC3;
		return std::abs(residual3) < 1e-7;
	}

	bool opt3(Sophus::SE3d& lc1, Sophus::SE3d& lc2, const Eigen::Vector3d& point, const Eigen::Vector3d& plane_origin, const Eigen::Vector3d& plane_normal) {
		int iter = 0;
		while (iter < 100) {
			double residual3 = (lc1 * point - lc2 * plane_origin).dot(lc2.so3() * plane_normal) - kTargetDistanceForC3;
			Eigen::VectorXd b(1);
			b[0] = -residual3;
			iter++;
			if (std::abs(residual3) < 1e-8) {
				return true;
			}
			Eigen::SparseMatrix<double> jacobian;
			jacobian.setZero();
			jacobian.resize(1, 12);
			Eigen::Vector<double, 6> jacobian0 = lc1.jacobian_mult_vector_exact(point).transpose() * (lc2.so3() * plane_normal);
			Eigen::Vector<double, 6> jacobian1 = lc2.jacobian_mult_vector_exact(plane_normal, true).transpose() * (lc1 * point - lc2 * plane_origin) - lc2.jacobian_mult_vector_exact(plane_origin).transpose() * (lc2.so3() * plane_normal);
			for (size_t i = 0; i < 6; i++){
				jacobian.insert(0, i) = jacobian0[i];
				jacobian.insert(0, 6 + i) = jacobian1[i];
			}
			Eigen::SparseMatrix<double> AAt = jacobian * jacobian.transpose();
			Eigen::SparseQR<Eigen::SparseMatrix<double>, Eigen::COLAMDOrdering<int>> solver;
			solver.compute(AAt);
			Eigen::VectorXd z = solver.solve(b);
			Eigen::VectorXd x = jacobian.transpose() * z;
			Eigen::Vector<double, 6> new_omega_theta1 = lc1.log() + x.topRows(6);
			Eigen::Vector<double, 6> new_omega_theta2 = lc2.log() + x.bottomRows(6);
			lc1 = Sophus::SE3d::exp(new_omega_theta1);
			lc2 = Sophus::SE3d::exp(new_omega_theta2);
		}
		return false;
	}

	bool opt44(Sophus::SE3d& lc1, Sophus::SE3d& lc2, const Eigen::Vector3d& point, const Eigen::Vector3d& plane_origin, const Eigen::Vector3d& plane_normal) {
		double residual4 = (lc1 * point - lc2 * plane_origin).dot(lc2.so3() * plane_normal);
		Eigen::VectorXd b(1);
		b[0] = -residual4;
		if (std::abs(residual4) < 1e-7) {
			return true;
		}
		auto pa = lc1 * point;
		auto pf = lc2 * plane_origin;
		auto nf = lc2.so3() * plane_normal;
		nf.normalize();
		Eigen::Vector3d dd = ((pa - pf).dot(nf)) * nf;
		Eigen::Vector3d d1, d2;
		double ddnorm = (pa - pf).dot(nf);
		if (ddnorm < 0) {
			double mvm = (0. - ddnorm) / 2.;
			d1 = mvm * nf;
			d2 = -mvm * nf;
		}
		else {
			double mvm = (ddnorm - 0.) / 2.;
			d1 = -mvm * nf;
			d2 = mvm * nf;
		}
		lc1 = Sophus::SE3d(lc1.unit_quaternion(), lc1.translation() + d1);
		lc2 = Sophus::SE3d(lc2.unit_quaternion(), lc2.translation() + d2);
		residual4 = (lc1 * point - lc2 * plane_origin).dot(lc2.so3() * plane_normal);
		if (std::abs(residual4) < 1e-7) {
			return true;
		}
		else {
			return false;
		}
	}

	bool opt4(Sophus::SE3d& lc1, Sophus::SE3d& lc2, const Eigen::Vector3d& o1lc1, const Eigen::Vector3d& olc2, const Eigen::Vector3d& plane_normal) {
		//Eigen::Vector3d new_omega1 = lc1.so3().log() + Eigen::Vector3d(randfun(), randfun(), randfun()) * 1e-5;
		//lc1.so3() = Sophus::SO3d::exp(new_omega1);
		Eigen::Vector3d new_omega2 = lc2.so3().log() + Eigen::Vector3d(randfun(), randfun(), randfun()) * 1e-5;
		lc2.so3() = Sophus::SO3d::exp(new_omega2);
		int iter = 0;
		while (iter < 100)		{
			double residual4 = (lc1 * o1lc1 - lc2 * olc2).dot(lc2.so3() * plane_normal);
			Eigen::VectorXd b(1);
			b[0] = -residual4;
			iter++;
			if (std::abs(residual4) < 1e-8) {
				return true;
			}
			Eigen::SparseMatrix<double> jacobian;
			jacobian.setZero();
			jacobian.resize(1, 12);
			auto jacobian0 = lc1.jacobian_mult_vector_exact(o1lc1).transpose() * (lc2.so3() * plane_normal);
			auto jacobian1 = lc2.jacobian_mult_vector_exact(plane_normal, true).transpose() * (lc1 * o1lc1 - lc2 * olc2) - lc2.jacobian_mult_vector_exact(olc2).transpose() * (lc2.so3() * plane_normal);
			for (size_t i = 0; i < 6; i++) {
				jacobian.insert(0, i) = jacobian0[i];
				jacobian.insert(0, 6 + i) = jacobian1[i];
			}
			Eigen::SparseMatrix<double> AAt = jacobian * jacobian.transpose();
			Eigen::SparseQR<Eigen::SparseMatrix<double>, Eigen::COLAMDOrdering<int>> solver;
			solver.compute(AAt);
			Eigen::VectorXd z = solver.solve(b);
			Eigen::VectorXd x = jacobian.transpose() * z;
			Eigen::Vector<double, 6> new1 = lc1.log() + x.topRows(6);
			Eigen::Vector<double, 6> new2 = lc2.log() + x.bottomRows(6);
			lc1 = Sophus::SE3d::exp(new1);
			lc2 = Sophus::SE3d::exp(new2);
		}
		return false;
	}
};

#endif // TEST_SOLVER_H_
