#ifndef RAY_H
#define RAY_H

#include "Vector3.h"
class Ray
{
public:
	Vec3 origin;
	Vec3 direction;
	double tmin = 0.001;		//Å¬Õ“Ë‹——£

	Ray(const Vec3& _origin, const Vec3& _direction)
		:origin(_origin), direction(_direction) {};

	Vec3 operator()(double t) const
	{
		return origin + t * direction;
	}
};

inline std::ostream& operator<<(std::ostream& stream, const Ray& ray)
{
	stream << "original: " << ray.origin << " direction" << ray.direction;
	return stream;
}
#endif