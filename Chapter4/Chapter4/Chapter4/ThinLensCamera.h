#ifndef THIN_LENS_CAMERA_H
#define THIN_LENS_CAMERA_H

#include "Camera.h"
#include "Vector3.h"
#include "Ray.h"
#include "Random.h"

class ThinLensCamera : public Camera
{
public:
	double a;		//�C���[�W�Z���T�[���烌���Y���S�܂ł̋���
	double b;		//�����Y���S����s���g�̍������ʂ܂ł̋���
	double f;		//�œ_����
	double lensRadius;		//�����Y�̔��a
	Vec3 lensCenter;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_camaraPos">�J�����̒��S�ʒu</param>
	/// <param name="_cameraForward"></param>
	/// <param name="focusPoint">�s���g�̍����ʒu</param>
	/// <param name="_a">a�̒l</param>
	/// <param name="_lensRadius">�����Y�̔��a</param>
	ThinLensCamera(const Vec3& _camaraPos, const Vec3& _cameraForward, const Vec3& focusPoint, double _a, double _lensRadius) : Camera(_camaraPos, _cameraForward), a(_a), lensRadius(_lensRadius)
	{
		double cos = dot(_cameraForward, normalize(focusPoint - cameraPos));
		//cos * (focusPoint - camPos).length() ��cameraForward�ɕ��s�ȃC���[�W�Z���T�[����ŕ��ʂ܂ł̋���(a + b)
		b = cos * (focusPoint - cameraPos).length() - a;
		//�����Y�̌������
		f = 1 / (1 / a + 1 / b);
		lensCenter = cameraPos + a * cameraForward;
	}

	Ray getRay(double u, double v) const 
	{
		//�C���[�W�Z���T�[��̓_
		Vec3 sensorPos = cameraPos + u * cameraRight + v * cameraUp;
		//�C���[�W�Z���T�[���烌���Y���S�֌���������
		Vec3 r = normalize(lensCenter - sensorPos);
		//�s���g�̍����ʒu
		Vec3 pf = sensorPos + (a + b) / dot(cameraForward, r) * r;

		//�����Y��̓_���T���v�����O
		double x, y;
		sampleDisk(x, y);
		Vec3 l = lensCenter + lensRadius * (x * cameraRight + y * cameraUp);

		return Ray(l, normalize(pf - l));
	}
};

#endif