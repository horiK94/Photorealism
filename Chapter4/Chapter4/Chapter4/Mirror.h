#ifndef MIRROR_H
#define MIRROR_H
#pragma once
#include "Vector3.h"
#include "Material.h"

class Mirror : public Material
{
public:
	Mirror()
	{

	}

	/// <summary>
	/// 反射ベクトルを返す
	/// </summary>
	/// <param name="v">反射させるベクトル</param>
	/// <param name="n">法線ベクトル</param>
	/// <returns></returns>
	Vec3 reflect(const Vec3& v, const Vec3& n) const
	{
		return -v + 2 * dot(v, n) * n;
	}

	Vec3 sample(const Vec3& wo, Vec3& wi, double& pdf) const
	{
		//ローカル座標は、法線nから作られる正規直交規定(s, n, t)を基底としたものなので、
		//法線の座標は(0, 1, 0)で表現できる
		wi = reflect(wo, Vec3(0, 1, 0));

		//wi(入射方向) = Wr(Woの反射方向)なら∞、違うなら0のBRDF
		//確率密度関数もwi(入射方向) = Wr(Woの反射方向)なら∞、違うなら0
		//つまり、お互い相殺されて f/p は 1/cosθ (θは入射角と法線のなす角)となる
		pdf = 1.0;
		return 1 / cosTheta(wi) * Vec3(1);
	}

	Vec3 sampleFixInput(const Vec3& wo, const Vec3& wi) const
	{
		throw "未実装";
	}

	Vec3 getAlbedo() const
	{
		//反射の色を返す
		throw "未実装";
	}
};
#endif