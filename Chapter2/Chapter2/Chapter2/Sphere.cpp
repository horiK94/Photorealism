#include "Sphere.h"

bool Sphere::intersect(const Ray& ray, Hit& res) const
{
	//�Q���������̌W��
	double b = dot(ray.direction, ray.origin - center);
	double c = (ray.origin - center).length2() - radius * radius;

	//���ʎ�
	double D = b * b - c;

	//���̌��̋���
	double t1 = -b - std::sqrt(D);
	double t2 = -b + std::sqrt(D);

	if (t1 > 10000 || t2 < 0)
	{
		//�������邩�A�������ǂ������O�ɂ���Ȃ�������Ȃ�
		return false;
	}

	double t = t1;
	if (t < 0)
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
