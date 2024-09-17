#pragma once
#include "Vec3.hpp"
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
};