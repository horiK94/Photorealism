#include "PinholeCamera.h"

Ray PinholeCamera::getRay(double u, double v) const
{
	Vec3 pinholePos = cameraPos + pinhioleDist * cameraForward;
	Vec3 sensorPos = cameraPos + u * cameraRight + v * cameraUp;

	return Ray(sensorPos, normalize(pinholePos - sensorPos));
}
