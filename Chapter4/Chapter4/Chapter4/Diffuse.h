#ifndef DIFFUSE_H
#define DIFFUSE_H
#include "Material.h"
#include "Vector3.h"
#include "Random.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Diffuse : public Material
{
public:
	Vec3 baseColor;		//反射率
	Diffuse(const Vec3& _rho) : baseColor(_rho) {};
	Vec3 sample(const Vec3& wo, Vec3& wi, double& pdf) const
	{
		//一様乱数 (球面座標系取得)
		double u = rnd();
		double v = rnd();

		//(theta, phi)の計算
		double theta = 0.5 * acos(1 - 2 * u);
		double phi = 2 * M_PI * v;

		//(x, y, z)を求める
		double x = cos(phi) * sin(theta);
		double y = cos(theta);
		double z = sin(phi) * sin(theta);
		//サンプリングされた入力方向
		wi = Vec3(x, y, z);

		//確率密度関数の値
		pdf = cos(theta) / M_PI;

		return baseColor / M_PI;
	}

	Vec3 sampleFixInput(const Vec3& wo, const Vec3& wi) const
	{
		return baseColor / M_PI;
	}

	Vec3 getAlbedo() const
	{
		return baseColor;
	}
};
#endif