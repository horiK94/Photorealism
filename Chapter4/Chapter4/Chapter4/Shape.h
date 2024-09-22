#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Hit.h"

/// <summary>
/// 球クラス
/// </summary>
static int idCounter;

class Shape
{
public:
	int id;

	Shape() {
		id = ++idCounter;
	}

	///rayと交差しているか. 交差している場合は衝突情報をresに格納
	virtual bool intersect(const Ray& ray, Hit& res) const = 0;
	///表面上の点を一様に取得
	virtual Vec3 areaSamling(Vec3 hitPos) const = 0;
	static void ResetId()
	{
		idCounter = 0;
	}
};

