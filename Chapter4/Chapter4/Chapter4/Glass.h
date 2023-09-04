#ifndef GLASS_H
#define GLASS_H
#include "Material.h"
#include "Random.h"
#include "Vector3.h"
class Glass : public Material
{
public:
	double ior;		//屈折率

	Glass(double _ior) : ior(_ior)
	{

	}

	//反射ベクトルを返す
	//v: 反射させるベクトル
	//n: 法線ベクトル
	Vec3 reflect(const Vec3& v, const Vec3& n) const {
		return -v + 2 * dot(v, n) * n;
	}

	/// <summary>
	/// BRDFから方向をサンプリングすると同時にBRDFの値を計算して返す
	/// </summary>
	/// <param name="wo"></param>
	/// <param name="wi">サンプリングされた方向</param>
	/// <param name="pdf">サンプリングされた方向の確率密度関数の値</param>
	/// <returns>BRDFの値</returns>
	Vec3 sample(const Vec3& wo, Vec3& wi, double& pdf) const
	{
		//ガラスに入射しているか
		bool isEnter = cosTheta(wo) > 0;

		double n1;		//入射側屈折率
		double n2;		//出射側屈折率
		Vec3 normal;	//法線. 入射と出射で入れ替える必要があるので
		//空気の屈折率は1.000292
		if (isEnter)
		{
			n1 = 1.000292;
			n2 = ior;
			normal = Vec3(0, 1, 0);
		}
		else
		{
			n1 = ior;
			n2 = 1.000292;
			normal = Vec3(0, -1, 0);
		}

		//フレネル反射率
		double fr = fresnel(wo, normal, n1, n2);

		if (rnd() < fr)
		{
			//反射. Mirrorの処理を参考
			wi = reflect(wo, normal);
			pdf = fr;
			return fr / absCosTheta(wi) * Vec3(1);
		}
		else
		{
			//屈折
			if (refract(wo, wi, normal, n1, n2))
			{
				pdf = 1.0 - fr;
				return std::pow(n1/n2, 2.0) * (1 - fr) / absCosTheta(wi) * Vec3(1);
			}
			else
			{
				//全反射 = すべての光が反射する
				wi = reflect(wo, normal);
				pdf = 1.0 - fr;
				return (1 - fr) / absCosTheta(wi) * Vec3(1);
			}
		}
	}
};
#endif
