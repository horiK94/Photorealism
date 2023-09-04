#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Ray.h"
class Camera
{
public:
	Vec3 cameraPos;		//カメラの位置
	Vec3 cameraForward;		//カメラの前方向
	Vec3 cameraRight;		//カメラの右方向
	Vec3 cameraUp;			//カメラの上方向

	Camera(const Vec3& _camPos, const Vec3& _cameraForward) : cameraPos(_camPos), cameraForward(_cameraForward)
	{
		orthnormalBasis(cameraForward, cameraRight, cameraUp);

		std::cout << "cameraPos: " << cameraPos << std::endl;
		std::cout << "cameraForward: " << cameraForward << std::endl;
		std::cout << "cameraRight: " << cameraRight << std::endl;
		std::cout << "cameraUp: " << cameraUp << std::endl;
	};

	/// <summary>
	/// 正規直交基底を作り出す
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <param name="v3"></param>
	void orthnormalBasis(const Vec3& v1, Vec3& v2, Vec3& v3);

	/// <summary>
	/// (u, v)座標に対応するレイを返す
	/// </summary>
	/// <param name="u"></param>
	/// <param name="v"></param>
	/// <returns></returns>
	virtual Ray getRay(double u, double v) const = 0;
};
#endif
