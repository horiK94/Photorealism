#ifndef UNIFORM_SKY_H
#define UNIFORM_SKY_H
#include "Sky.h"

/// <summary>
/// �P��F�ȋ��\������N���X
/// </summary>
class UniformSky : public Sky
{
public:
	Vec3 color;		//��̐F
	UniformSky(Vec3 color) : color(color)
	{

	}

	/// <summary>
	/// �󂯎�������C�̕����痈���̕��ˋP�x�̒l��Ԃ�
	/// </summary>
	/// <param name="ray"></param>
	/// <returns></returns>
	Vec3 getRadiance(const Ray& ray) const
	{
		return color;
	}
};

#endif