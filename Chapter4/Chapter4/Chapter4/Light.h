#ifndef LIGHT_H
#define LIGHT_H
#include "Vector3.h"

#pragma once
class Light
{
public:
	Vec3 color;		//�����̐F
	Light(const Vec3& _color) : color(_color)
	{

	}

	//�����_�����O��������Le�ɑΉ����镔��
	//���ׂĂ̕����ɓ��������ˋP�x��Ԃ��̂ŒP���ɕێ����Ă���F�����Ԃ�
	Vec3 Le() const
	{
		return color;
	}
};

#endif