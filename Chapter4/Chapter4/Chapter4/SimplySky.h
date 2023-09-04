#ifndef SIMPLY_SKY_H
#define SIMPLY_SKY_H
#include "Sky.h"

class SimplySky :public Sky
{
public:
	Vec3 color;		//空の色
	SimplySky()
	{
			
	}

	/// <summary>
	/// 受け取ったレイの方から来る空の放射輝度の値を返す
	/// </summary>
	/// <param name="ray"></param>
	/// <returns></returns>
	Vec3 getRadiance(const Ray& ray) const
	{
		//directionは正規化済みなので、-1 ～ 1の範囲. tは0～1に変換される
		double t = (ray.direction.y + 1) / 2;
		//下の方は1, 上の方は(0.7, 0.8, 1)となるようにlerpされる
		return (1 - t) * Vec3(1) + t * Vec3(0.7, 0.8, 1);
	}
};

#endif