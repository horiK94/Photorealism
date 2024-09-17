#pragma once
#include "Vec3.hpp"
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
};