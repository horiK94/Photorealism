#ifndef SPHERE_H
#define SPHERE_H

#include "Vector3.h"
#include "Ray.h"
#include "Hit.h"
#include "Material.h"
#include "Light.h"
#include "Random.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace  std;

/// <summary>
/// 球クラス
/// </summary>
static int idCounter;

class Sphere
{
private:
public:
	Vec3 center;		//中心位置
	double radius;		//半径
	int id;

	shared_ptr<Material> material;		//BRDF
	shared_ptr<Light> light;		//Le
	Sphere(const Vec3& _center, double _radius,
		const shared_ptr<Material>& _material, const shared_ptr<Light>& _light)
		: center(_center), radius(_radius), material(_material), light(_light)
	{
		id = ++idCounter;
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

	//表面上の点を一様に取得
	Vec3 areaSamling(Vec3 lightPos) const
	{
		double u = rnd();
		double v = rnd();

		// https://tapioca.hatenablog.jp/entry/2017/02/19/015556
		//zの値を決定
		double z = -1 + 2 * u;
		// θの値決定
		double theta = 2 * M_PI * v;

		double x = sqrt(1 - z * z) * cos(theta);
		double y = sqrt(1 - z * z) * sin(theta);

		Vec3 normal = Vec3(x, y, z);
		return center + radius * normalize(normal);
	}

	static void ResetId()
	{
		idCounter = 0;
	}
};

#endif