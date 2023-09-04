#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Ray.h"
class Camera
{
public:
	Vec3 cameraPos;		//�J�����̈ʒu
	Vec3 cameraForward;		//�J�����̑O����
	Vec3 cameraRight;		//�J�����̉E����
	Vec3 cameraUp;			//�J�����̏����

	Camera(const Vec3& _camPos, const Vec3& _cameraForward) : cameraPos(_camPos), cameraForward(_cameraForward)
	{
		orthnormalBasis(cameraForward, cameraRight, cameraUp);

		std::cout << "cameraPos: " << cameraPos << std::endl;
		std::cout << "cameraForward: " << cameraForward << std::endl;
		std::cout << "cameraRight: " << cameraRight << std::endl;
		std::cout << "cameraUp: " << cameraUp << std::endl;
	};

	/// <summary>
	/// ���K�����������o��
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <param name="v3"></param>
	void orthnormalBasis(const Vec3& v1, Vec3& v2, Vec3& v3);

	/// <summary>
	/// (u, v)���W�ɑΉ����郌�C��Ԃ�
	/// </summary>
	/// <param name="u"></param>
	/// <param name="v"></param>
	/// <returns></returns>
	virtual Ray getRay(double u, double v) const = 0;
};
#endif
