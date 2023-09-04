#ifndef UNIFORM_SKY_H
#define UNIFORM_SKY_H
#include "Sky.h"

/// <summary>
/// 単一色な空を表現するクラス
/// </summary>
class UniformSky : public Sky
{
public:
	Vec3 color;		//空の色
	UniformSky(Vec3 color) : color(color)
	{

	}

	/// <summary>
	/// 受け取ったレイの方から来る空の放射輝度の値を返す
	/// </summary>
	/// <param name="ray"></param>
	/// <returns></returns>
	Vec3 getRadiance(const Ray& ray) const
	{
		return color;
	}
};

#endif