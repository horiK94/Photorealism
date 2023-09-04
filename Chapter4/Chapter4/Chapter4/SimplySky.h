#ifndef SIMPLY_SKY_H
#define SIMPLY_SKY_H
#include "Sky.h"

class SimplySky :public Sky
{
public:
	Vec3 color;		//��̐F
	SimplySky()
	{
			
	}

	/// <summary>
	/// �󂯎�������C�̕����痈���̕��ˋP�x�̒l��Ԃ�
	/// </summary>
	/// <param name="ray"></param>
	/// <returns></returns>
	Vec3 getRadiance(const Ray& ray) const
	{
		//direction�͐��K���ς݂Ȃ̂ŁA-1 �` 1�͈̔�. t��0�`1�ɕϊ������
		double t = (ray.direction.y + 1) / 2;
		//���̕���1, ��̕���(0.7, 0.8, 1)�ƂȂ�悤��lerp�����
		return (1 - t) * Vec3(1) + t * Vec3(0.7, 0.8, 1);
	}
};

#endif