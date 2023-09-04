#ifndef SPHERE_H
#define SPHERE_H
#include "Vector3.h"
#include "Ray.h"
#include "Hit.h"
#include "Material.h"
#include "Light.h"
using namespace  std;

/// <summary>
/// ���N���X
/// </summary>
class Sphere
{
public:
	Vec3 center;		//���S�ʒu
	double radius;		//���a

	shared_ptr<Material> material;		//BRDF
	shared_ptr<Light> light;		//Le
	Sphere(const Vec3& _center, double _radius,
		const shared_ptr<Material>& _material, const shared_ptr<Light>& _light)
		: center(_center), radius(_radius), material(_material), light(_light)
	{
	}

	//ray�ƌ������Ă��邩. �������Ă���ꍇ�͏Փˏ���res�Ɋi�[
	bool intersect(const Ray& ray, Hit& res) const
	{
		//�Q���������̌W��
		double b = dot(ray.direction, ray.origin - center);
		double c = (ray.origin - center).length2() - radius * radius;

		//���ʎ�
		double D = b * b - c;

		//���̌��̋���
		double t1 = -b - std::sqrt(D);
		double t2 = -b + std::sqrt(D);

		if (t1 > 10000 || t2 < ray.tmin)
		{
			//�������邩�A�������ǂ������O�ɂ���Ȃ�������Ȃ�
			return false;
		}

		double t = t1;
		if (t < ray.tmin)
		{
			//t1�͎�O�Ȃ̂�t2��p����
			t = t2;
			if (t2 > 10000)
			{
				//�������Ȃ̂Ō������Ȃ��Ƃ���
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