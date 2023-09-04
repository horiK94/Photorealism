#ifndef SPHERE_H
#define SPHERE_H
#include "Vector3.h"
#include "Ray.h"
#include "Hit.h"
#include "Material.h"
#include "Light.h"
using namespace  std;

/// <summary>
/// 球クラス
/// </summary>
class Sphere
{
public:
	Vec3 center;		//中心位置
	double radius;		//半径

	shared_ptr<Material> material;		//BRDF
	shared_ptr<Light> light;		//Le
	Sphere(const Vec3& _center, double _radius,
		const shared_ptr<Material>& _material, const shared_ptr<Light>& _light)
		: center(_center), radius(_radius), material(_material), light(_light)
	{
	}

	//rayと交差しているか. 交差している場合は衝突情報をresに格納
	bool intersect(const Ray& ray, Hit& res) const
	{
		//２次方程式の係数
		double b = dot(ray.direction, ray.origin - center);
		double c = (ray.origin - center).length2() - radius * radius;

		//判別式
		double D = b * b - c;

		//解の候補の距離
		double t1 = -b - std::sqrt(D);
		double t2 = -b + std::sqrt(D);

		if (t1 > 10000 || t2 < ray.tmin)
		{
			//遠すぎるか、交差がどちらも手前にあるなら交差しない
			return false;
		}

		double t = t1;
		if (t < ray.tmin)
		{
			//t1は手前なのでt2を用いる
			t = t2;
			if (t2 > 10000)
			{
				//遠すぎなので交差しないとする
				return false;
			}
		}

		res.t = t;
		res.hitPos = ray(t);
		res.hitNormal = normalize(res.hitPos - center);
		res.hitSphere = this;

		return true;
	}
};

#endif