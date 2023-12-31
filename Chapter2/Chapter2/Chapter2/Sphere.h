#ifndef SPHERE_H
#define SPHERE_H
#include "Vector3.h"
#include "Ray.h"
#include "Hit.h"
class Sphere
{
public:
	Vec3 center;
	double radius;
	Sphere(const Vec3& _center, double _radius) : center(_center), radius(_radius)
	{
	}

	//rayと交差しているか. 交差している場合は衝突情報をresに格納
	bool intersect(const Ray& ray, Hit& res) const;
};

#endif