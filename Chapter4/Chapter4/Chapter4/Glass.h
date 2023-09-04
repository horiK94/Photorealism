#ifndef GLASS_H
#define GLASS_H
#include "Material.h"
#include "Random.h"
#include "Vector3.h"
class Glass : public Material
{
public:
	double ior;		//���ܗ�

	Glass(double _ior) : ior(_ior)
	{

	}

	//���˃x�N�g����Ԃ�
	//v: ���˂�����x�N�g��
	//n: �@���x�N�g��
	Vec3 reflect(const Vec3& v, const Vec3& n) const {
		return -v + 2 * dot(v, n) * n;
	}

	/// <summary>
	/// BRDF����������T���v�����O����Ɠ�����BRDF�̒l���v�Z���ĕԂ�
	/// </summary>
	/// <param name="wo"></param>
	/// <param name="wi">�T���v�����O���ꂽ����</param>
	/// <param name="pdf">�T���v�����O���ꂽ�����̊m�����x�֐��̒l</param>
	/// <returns>BRDF�̒l</returns>
	Vec3 sample(const Vec3& wo, Vec3& wi, double& pdf) const
	{
		//�K���X�ɓ��˂��Ă��邩
		bool isEnter = cosTheta(wo) > 0;

		double n1;		//���ˑ����ܗ�
		double n2;		//�o�ˑ����ܗ�
		Vec3 normal;	//�@��. ���˂Əo�˂œ���ւ���K�v������̂�
		//��C�̋��ܗ���1.000292
		if (isEnter)
		{
			n1 = 1.000292;
			n2 = ior;
			normal = Vec3(0, 1, 0);
		}
		else
		{
			n1 = ior;
			n2 = 1.000292;
			normal = Vec3(0, -1, 0);
		}

		//�t���l�����˗�
		double fr = fresnel(wo, normal, n1, n2);

		if (rnd() < fr)
		{
			//����. Mirror�̏������Q�l
			wi = reflect(wo, normal);
			pdf = fr;
			return fr / absCosTheta(wi) * Vec3(1);
		}
		else
		{
			//����
			if (refract(wo, wi, normal, n1, n2))
			{
				pdf = 1.0 - fr;
				return std::pow(n1/n2, 2.0) * (1 - fr) / absCosTheta(wi) * Vec3(1);
			}
			else
			{
				//�S���� = ���ׂĂ̌������˂���
				wi = reflect(wo, normal);
				pdf = 1.0 - fr;
				return (1 - fr) / absCosTheta(wi) * Vec3(1);
			}
		}
	}
};
#endif
