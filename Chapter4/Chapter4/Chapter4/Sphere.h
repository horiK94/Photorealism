#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "Random.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Light.h"

using namespace std;

class Sphere : public Shape
{
public:
	Vec3 center;		//中心位置
	double radius;		//半径

	Sphere(const Vec3& _center, double _radius,
		const shared_ptr<Material>& _material, const shared_ptr<Light>& _light)
		: Shape(_material, _light), center(_center), radius(_radius)
	{
	}

	//rayと交差しているか. 交差している場合は衝突情報をresに格納
	bool intersect(const Ray& ray, Hit& res) const override
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
		res.hitShape = this;

		return true;
	}

	//表面上の点を一様に取得
	Vec3 areaSampling(Vec3 hitPos) const override
	{
		//中心から現在の光源の衝突位置への向きベクトルを中心とする
		Vec3 n = normalize(hitPos - center);

		//法線を1線とした正規直交基底ベクトルを作成
		Vec3 s, t;
		orthonormalBasis(n, s, t);

		double u = rnd();
		double v = rnd();

		// https://tapioca.hatenablog.jp/entry/2017/02/19/015556
		//zの値を決定
		double z = u;
		// θの値決定
		double theta = 2 * M_PI * v;

		double x = sqrt(1 - z * z) * cos(theta);
		double y = sqrt(1 - z * z) * sin(theta);

		Vec3 normal = localToWorld(Vec3(x, y, z), s, t, n);
		return center + radius * normalize(normal);
	}
};

#endif