#pragma once
#include "Vector3.h"
class Material
{
public:
	/// <summary>
	/// BRDF����������T���v�����O����Ɠ�����BRDF�̒l���v�Z���ĕԂ�
	/// </summary>
	/// <param name="wo"></param>
	/// <param name="wi">�T���v�����O���ꂽ����</param>
	/// <param name="pdf">�T���v�����O���ꂽ�����̊m�����x�֐��̒l</param>
	/// <returns>BRDF�̒l</returns>
	virtual Vec3 sample(const Vec3& wo, Vec3& wi, double& pdf) const = 0;
	virtual Vec3 sampleFixInput(const Vec3& wo, const Vec3& wi) const = 0;
};

/// <summary>
/// ���[�J�����W�n�̃x�N�g������cosTheta���v�Z����
/// </summary>
/// <returns></returns>
static double cosTheta(const Vec3& v)
{
	//�@��(0, 1, 0)�Ƃ̂Ȃ��p�Ƃ�p���ċ��߂���cos�Ƃ͓��ς��狁�߂���
	return v.y;
}

static double absCosTheta(const Vec3& v)
{
	return std::abs(v.y);
}

/// <summary>
/// �t���l�����˗���Ԃ�
/// </summary>
/// <param name="v">���˃x�N�g��</param>
/// <param name="n"></param>
/// <param name="n1"></param>
/// <param name="n2"></param>
/// <returns></returns>
static double fresnel(const Vec3& v, const Vec3& n, double n1, double n2)
{
	double f0 = std::pow((n1 - n2) / (n1 + n2), 2);
	double cos = absCosTheta(v);
	return f0 + (1 - f0) * std::pow(1 - cos, 5);
}

/// <summary>
/// ���ܕ����̌v�Z
/// �S���˂��N������false��Ԃ�
/// </summary>
/// <param name="v"></param>
/// <param name="r"></param>
/// <param name="n"></param>
/// <param name="n1"></param>
/// <param name="n2"></param>
/// <returns></returns>
static bool refract(const Vec3& v, Vec3& r, const Vec3& n, double n1, double n2)
{
	double cos = absCosTheta(v);
	double sin = std::sqrt(std::max(1 - cos * cos, 0.0));		//v������1�Ȃ�max�Ȃ��Ă����v���Ǝv�����A�v�Z�덷�ŕ��̒l���o�������l���ĔO�̂���
	double alpha = n1 / n2 * sin;

	if (alpha * alpha > 1)
	{
		//�S����
		return false;
	}

	//���܃x�N�g��
	r = n1 / n2 * (dot(v, n) * n - v) - n * std::sqrt(1 - alpha * alpha);
	return true;
}