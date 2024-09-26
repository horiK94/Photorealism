#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Hit.h"
#include "Light.h"
#include "Material.h"

/// <summary>
/// 球クラス
/// </summary>
static int idCounter;

class Hit;
class Shape
{
public:
	virtual ~Shape() = default;
	int id;
	std::shared_ptr<Light> light;		//Le
	std::shared_ptr<Material> material;		//BRDF

	Shape(const std::shared_ptr<Material>& _material, const std::shared_ptr<Light>& _light) : material(_material), light(_light)
	{
		id = ++idCounter;
	}

	///rayと交差しているか. 交差している場合は衝突情報をresに格納
	virtual bool intersect(const Ray& ray, Hit& res) const = 0;
	///表面上の点を一様に取得
	virtual Vec3 areaSampling(Vec3 hitPos) const = 0;

	static void ResetId()
	{
		idCounter = 0;
	}
};

