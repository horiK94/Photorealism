#pragma once
#include "Shape.h"

using namespace std;

class Triangle : public Shape
{
public:
	Vec3 p0, p1, p2;

	Triangle(const Vec3& _p0, const Vec3& _p1, const Vec3& _p2,
        const shared_ptr<Material>& _material, const shared_ptr<Light>& _light)
		:Shape(_material, _light), p0(_p0), p1(_p1), p2(_p2)
	{
	}

    bool intersect(const Ray& ray, Hit& res) const override
	{
        // 微小な定数([Möller97] での値)
        constexpr float kEpsilon = 1e-6f;

        Vec3 e1 = p1 - p0;
        Vec3 e2 = p2 - p0;

        Vec3 alpha = cross(ray.direction, e2);
        float det = dot(e1, alpha);

        // 三角形に対して、レイが平行に入射するような場合 det = 0 となる。
        // det が小さすぎると 1/det が大きくなりすぎて数値的に不安定になるので
        // det ≈ 0 の場合は交差しないこととする。
        if (-kEpsilon < det && det < kEpsilon) {
            return false;
        }

        float invDet = 1.0f / det;
        Vec3 r = ray.origin - p0;

        // u が 0 <= u <= 1 を満たしているかを調べる。
        float u = dot(alpha, r) * invDet;
        if (u < 0.0f || u > 1.0f) {
            return false;
        }

        Vec3 beta = cross(r, e1);

        // v が 0 <= v <= 1 かつ u + v <= 1 を満たすことを調べる。
        // すなわち、v が 0 <= v <= 1 - u をみたしているかを調べればOK。
        float v = dot(ray.direction, beta) * invDet;
        if (v < 0.0f || u + v > 1.0f) {
            return false;
        }

        // t が 0 <= t を満たすことを調べる。
        float t = dot(e2, beta) * invDet;
        if (t < 0.0f) {
            return false;
        }

        res.t = t;
        res.hitPos = ray(t);

        Vec3 n1 = normalize(cross(e1, e2));
        Vec3 n2 = normalize(cross(e2, e1));
        res.hitNormal = dot(n1, ray.direction) < 0 ? n1 : n2;
        res.hitShape = this;

        // 交差した！！！！
        return true;
	}

	Vec3 areaSampling(Vec3 hitPos) const override
	{
		return hitPos;
	}
};

