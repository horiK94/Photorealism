#ifndef PINHOLE_CAMERA_H
#define PINHOLE_CAMERA_H

#include "Camera.h"
class PinholeCamera : public Camera
{
public:
	double pinhioleDist;	//イメージセンサーの中心からピンホールまでの距離

	PinholeCamera(const Vec3& _camPos, const Vec3& _cameraForward, double _pinholeDistance) : Camera(_camPos, _cameraForward), pinhioleDist(_pinholeDistance)
	{

	}

	Ray getRay(double u, double v) const;
};
#endif

