#include "Camera.h"

void Camera::orthnormalBasis(const Vec3& v1, Vec3& v2, Vec3& v3)
{
	if (std::abs(v1.x) > 0.9)
	{
		//(1, 0, 0)‚Ì‰Â”\«‚ª‚ ‚é‚Ì‚ÅAv2‚ğ•Ê•ûŒü‚É•Ï‚¦‚é
		v2 = Vec3(0, 1, 0);
	}
	else
	{
		v2 = Vec3(1, 0, 0);
	}

	v2 = normalize(v2 - dot(v1, v2) * v1);
	v3 = cross(v1, v2);
}
