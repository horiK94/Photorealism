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

	//ray‚ÆŒğ·‚µ‚Ä‚¢‚é‚©. Œğ·‚µ‚Ä‚¢‚éê‡‚ÍÕ“Ëî•ñ‚ğres‚ÉŠi”[
	bool intersect(const Ray& ray, Hit& res) const;
};

#endif