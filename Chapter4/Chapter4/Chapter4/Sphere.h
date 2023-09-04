#ifndef SPHERE_H
#define SPHERE_H
#include "Vector3.h"
#include "Ray.h"
#include "Hit.h"
#include "Material.h"
#include "Light.h"
using namespace  std;

/// <summary>
/// ‹…ƒNƒ‰ƒX
/// </summary>
class Sphere
{
public:
	Vec3 center;		//’†SˆÊ’u
	double radius;		//”¼Œa

	shared_ptr<Material> material;		//BRDF
	shared_ptr<Light> light;		//Le
	Sphere(const Vec3& _center, double _radius,
		const shared_ptr<Material>& _material, const shared_ptr<Light>& _light)
		: center(_center), radius(_radius), material(_material), light(_light)
	{
	}

	//ray‚ÆŒğ·‚µ‚Ä‚¢‚é‚©. Œğ·‚µ‚Ä‚¢‚éê‡‚ÍÕ“Ëî•ñ‚ğres‚ÉŠi”[
	bool intersect(const Ray& ray, Hit& res) const
	{
		//‚QŸ•û’ö®‚ÌŒW”
		double b = dot(ray.direction, ray.origin - center);
		double c = (ray.origin - center).length2() - radius * radius;

		//”»•Ê®
		double D = b * b - c;

		//‰ğ‚ÌŒó•â‚Ì‹——£
		double t1 = -b - std::sqrt(D);
		double t2 = -b + std::sqrt(D);

		if (t1 > 10000 || t2 < ray.tmin)
		{
			//‰“‚·‚¬‚é‚©AŒğ·‚ª‚Ç‚¿‚ç‚àè‘O‚É‚ ‚é‚È‚çŒğ·‚µ‚È‚¢
			return false;
		}

		double t = t1;
		if (t < ray.tmin)
		{
			//t1‚Íè‘O‚È‚Ì‚Åt2‚ğ—p‚¢‚é
			t = t2;
			if (t2 > 10000)
			{
				//‰“‚·‚¬‚È‚Ì‚ÅŒğ·‚µ‚È‚¢‚Æ‚·‚é
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