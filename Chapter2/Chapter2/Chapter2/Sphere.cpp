#include "Sphere.h"

bool Sphere::intersect(const Ray& ray, Hit& res) const
{
	//２次方程式の係数
	double b = dot(ray.direction, ray.origin - center);
	double c = (ray.origin - center).length2() - radius * radius;

	//判別式
	double D = b * b - c;

	//解の候補の距離
	double t1 = -b - std::sqrt(D);
	double t2 = -b + std::sqrt(D);

	if (t1 > 10000 || t2 < 0)
	{
		//遠すぎるか、交差がどちらも手前にあるなら交差しない
		return false;
	}

	double t = t1;
	if (t < 0)
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
