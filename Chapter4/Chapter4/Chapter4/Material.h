#pragma once
#include "Vector3.h"
class Material
{
public:
	/// <summary>
	/// BRDFから方向をサンプリングすると同時にBRDFの値を計算して返す
	/// </summary>
	/// <param name="wo"></param>
	/// <param name="wi">サンプリングされた方向</param>
	/// <param name="pdf">サンプリングされた方向の確率密度関数の値</param>
	/// <returns>BRDFの値</returns>
	virtual Vec3 sample(const Vec3& wo, Vec3& wi, double& pdf) const = 0;
	virtual Vec3 sampleFixInput(const Vec3& wo, const Vec3& wi) const = 0;
};

/// <summary>
/// ローカル座標系のベクトルからcosThetaを計算する
/// </summary>
/// <returns></returns>
static double cosTheta(const Vec3& v)
{
	//法線(0, 1, 0)とのなす角θを用いて求められるcosθは内積から求められる
	return v.y;
}

static double absCosTheta(const Vec3& v)
{
	return std::abs(v.y);
}

/// <summary>
/// フレネル反射率を返す
/// </summary>
/// <param name="v">入射ベクトル</param>
/// <param name="n"></param>
/// <param name="n1"></param>
/// <param name="n2"></param>
/// <returns></returns>
static double fresnel(const Vec3& v, const Vec3& n, double n1, double n2)
{
	double f0 = std::pow((n1 - n2) / (n1 + n2), 2);
	double cos = absCosTheta(v);
	return f0 + (1 - f0) * std::pow(1 - cos, 5);
}

/// <summary>
/// 屈折方向の計算
/// 全反射が起きたらfalseを返す
/// </summary>
/// <param name="v"></param>
/// <param name="r"></param>
/// <param name="n"></param>
/// <param name="n1"></param>
/// <param name="n2"></param>
/// <returns></returns>
static bool refract(const Vec3& v, Vec3& r, const Vec3& n, double n1, double n2)
{
	double cos = absCosTheta(v);
	double sin = std::sqrt(std::max(1 - cos * cos, 0.0));		//vが長さ1ならmaxなくても大丈夫だと思うが、計算誤差で負の値が出た事も考えて念のため
	double alpha = n1 / n2 * sin;

	if (alpha * alpha > 1)
	{
		//全反射
		return false;
	}

	//屈折ベクトル
	r = n1 / n2 * (dot(v, n) * n - v) - n * std::sqrt(1 - alpha * alpha);
	return true;
}