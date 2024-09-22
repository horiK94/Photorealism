#pragma once
#include "Shape.h"

class Triangle : public Shape
{
public: 
	Vec3 p0, p1, p2;

	Triangle(const Vec3& _p0, const Vec3& _p1, const Vec3& _p2)
		:Shape(), p0(_p0), p1(_p1), p2(_p2)
	{
	}

	bool intersect(const Ray& ray, Hit& res) const
	{
		const double EPS = 1e-6;
		Vec3 e1 = p1 - p0;
		Vec3 e2 = p2 - p0;
		Vec3 s = ray.origin - p0;
		Vec3 s1 = cross(ray.direction, e2);
		Vec3 s2 = cross(s, e1);
		double d = dot(s1, e1);
		double t = dot(s2, e2) / d;
		double b1 = dot(s1, s) / d;
		double b2 = dot(s2, ray.direction) / d;
		if (t < EPS || b1 < 0 || b2 < 0 || b1 + b2 > 1)
		{
			return false;
		}
		res.t = t;
		res.hitPos = ray(t);
		res.hitNormal = normal;
		return true;
	}

	Vec3 areaSamling(Vec3 hitPos) const
	{
		return hitPos;
	}
};

