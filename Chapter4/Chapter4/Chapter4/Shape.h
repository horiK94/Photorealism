#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Hit.h"

/// <summary>
/// ���N���X
/// </summary>
static int idCounter;

class Shape
{
public:
	int id;

	Shape() {
		id = ++idCounter;
	}

	///ray�ƌ������Ă��邩. �������Ă���ꍇ�͏Փˏ���res�Ɋi�[
	virtual bool intersect(const Ray& ray, Hit& res) const = 0;
	///�\�ʏ�̓_����l�Ɏ擾
	virtual Vec3 areaSamling(Vec3 hitPos) const = 0;
	static void ResetId()
	{
		idCounter = 0;
	}
};

