#ifndef LIGHT_H
#define LIGHT_H
#include "Vector3.h"

#pragma once
class Light
{
public:
	Vec3 color;		//光源の色
	Light(const Vec3& _color) : color(_color)
	{

	}

	//レンダリング方程式のLeに対応する部分
	//すべての方向に等しく放射輝度を返すので単純に保持している色だけ返す
	Vec3 Le() const
	{
		return color;
	}
};

#endif