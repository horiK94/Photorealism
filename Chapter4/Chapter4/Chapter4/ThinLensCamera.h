#ifndef THIN_LENS_CAMERA_H
#define THIN_LENS_CAMERA_H

#include "Camera.h"
#include "Vector3.h"
#include "Ray.h"
#include "Random.h"

class ThinLensCamera : public Camera
{
public:
	double a;		//イメージセンサーからレンズ中心までの距離
	double b;		//レンズ中心からピントの合う平面までの距離
	double f;		//焦点距離
	double lensRadius;		//レンズの半径
	Vec3 lensCenter;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_camaraPos">カメラの中心位置</param>
	/// <param name="_cameraForward"></param>
	/// <param name="focusPoint">ピントの合う位置</param>
	/// <param name="_a">aの値</param>
	/// <param name="_lensRadius">レンズの半径</param>
	ThinLensCamera(const Vec3& _camaraPos, const Vec3& _cameraForward, const Vec3& focusPoint, double _a, double _lensRadius) : Camera(_camaraPos, _cameraForward), a(_a), lensRadius(_lensRadius)
	{
		double cos = dot(_cameraForward, normalize(focusPoint - cameraPos));
		//cos * (focusPoint - camPos).length() はcameraForwardに平行なイメージセンサーから焦平面までの距離(a + b)
		b = cos * (focusPoint - cameraPos).length() - a;
		//レンズの公式より
		f = 1 / (1 / a + 1 / b);
		lensCenter = cameraPos + a * cameraForward;
	}

	Ray getRay(double u, double v) const 
	{
		//イメージセンサー上の点
		Vec3 sensorPos = cameraPos + u * cameraRight + v * cameraUp;
		//イメージセンサーからレンズ中心へ向かう方向
		Vec3 r = normalize(lensCenter - sensorPos);
		//ピントの合う位置
		Vec3 pf = sensorPos + (a + b) / dot(cameraForward, r) * r;

		//レンズ上の点をサンプリング
		double x, y;
		sampleDisk(x, y);
		Vec3 l = lensCenter + lensRadius * (x * cameraRight + y * cameraUp);

		return Ray(l, normalize(pf - l));
	}
};

#endif