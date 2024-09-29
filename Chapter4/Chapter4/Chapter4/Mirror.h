#ifndef MIRROR_H
#define MIRROR_H
#pragma once
#include "Vector3.h"
#include "Material.h"

class Mirror : public Material
{
public:
	Mirror()
	{

	}

	/// <summary>
	/// ���˃x�N�g����Ԃ�
	/// </summary>
	/// <param name="v">���˂�����x�N�g��</param>
	/// <param name="n">�@���x�N�g��</param>
	/// <returns></returns>
	Vec3 reflect(const Vec3& v, const Vec3& n) const
	{
		return -v + 2 * dot(v, n) * n;
	}

	Vec3 sample(const Vec3& wo, Vec3& wi, double& pdf) const
	{
		//���[�J�����W�́A�@��n�������鐳�K�����K��(s, n, t)�����Ƃ������̂Ȃ̂ŁA
		//�@���̍��W��(0, 1, 0)�ŕ\���ł���
		wi = reflect(wo, Vec3(0, 1, 0));

		//wi(���˕���) = Wr(Wo�̔��˕���)�Ȃ灇�A�Ⴄ�Ȃ�0��BRDF
		//�m�����x�֐���wi(���˕���) = Wr(Wo�̔��˕���)�Ȃ灇�A�Ⴄ�Ȃ�0
		//�܂�A���݂����E����� f/p �� 1/cos�� (�Ƃ͓��ˊp�Ɩ@���̂Ȃ��p)�ƂȂ�
		pdf = 1.0;
		return 1 / cosTheta(wi) * Vec3(1);
	}

	Vec3 sampleFixInput(const Vec3& wo, const Vec3& wi) const
	{
		throw "������";
	}

	Vec3 getAlbedo() const
	{
		//���˂̐F��Ԃ�
		throw "������";
	}
};
#endif