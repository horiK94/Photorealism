#ifndef HIT_H
#define HIT_H
#include "Shape.h"
#include "Vector3.h"

//�v���g�^�C�v�錾. �z�Q�ƂɂȂ邽��
class Shape;

class Hit
{
public:
	double t;		//�Փˋ���
	Vec3 hitPos;	//�Փˈʒu
	Vec3 hitNormal;	//�Փ˖@��

	const Shape* hitShape;		//�Փ˕���

	Hit()
	{
		t = 10000;
	}
};

#endif