#pragma once
#include <iostream>
#include <cmath>

class Vec3
{
public:
	double x;
	double y;
	double z;

	Vec3() { x = y = z = 0; };
	Vec3(double _x) { x = y = z = _x; };
	Vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};

	double length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	};

	double length2() const
	{
		return x * x + y * y + z * z;
	};

	Vec3 operator-() const
	{
		return Vec3(-x, -y, -z);
	}

	Vec3& operator +=(const Vec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vec3& operator -=(const Vec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	Vec3& operator *=(const Vec3& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}
	Vec3& operator /=(const Vec3& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}
};

inline Vec3 operator+(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
inline Vec3 operator-(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
inline Vec3 operator*(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
inline Vec3 operator/(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

//ベクトルとスカラーの演算
inline Vec3 operator+(const Vec3& v, double k)
{
	return Vec3(v.x + k, v.y + k, v.z + k);
}

inline Vec3 operator+(double k, const Vec3& v)
{
	return v + k;
}
inline Vec3 operator-(const Vec3& v, double k)
{
	return Vec3(v.x - k, v.y - k, v.z - k);
}
inline Vec3 operator-(double k, const Vec3& v)
{
	return Vec3(k - v.x, k - v.y, k - v.z);
}
inline Vec3 operator*(const Vec3& v, double k)
{
	return Vec3(v.x * k, v.y * k, v.z * k);
}
inline Vec3 operator*(double k, const Vec3& v)
{
	return v * k;
}
inline Vec3 operator/(const Vec3& v, double k)
{
	return Vec3(v.x / k, v.y / k, v.z / k);
}
inline Vec3 operator/(double k, const Vec3& v)
{
	return Vec3(k / v.x, k / v.y, k / v.z);
}

//内積
inline double dot(const Vec3& v1, const Vec3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

//ワールド座標系からローカル座標系に変換する
//s, n, tは正規直交基底
inline Vec3 worldToLocal(const Vec3& v, const Vec3& s, const Vec3& n, const Vec3& t)
{
	return Vec3(dot(v, s), dot(v, n), dot(v, t));
}

//ローカル座標系からワールド座標系に変換する
//s, n, tは正規直交基底
inline Vec3 localToWorld(const Vec3& v, const Vec3& s, const Vec3& n, const Vec3& t)
{
	Vec3 a = Vec3(s.x, n.x, t.x);
	Vec3 b = Vec3(s.y, n.y, t.y);
	Vec3 c = Vec3(s.z, n.z, t.z);

	return Vec3(dot(v, a), dot(v, b), dot(v, c));
}

inline Vec3 cross(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

//正規化
inline Vec3 normalize(const Vec3& v)
{
	return v / v.length();
}

//正規直交基底を作り出す
inline void orthonormalBasis(const Vec3& v1, Vec3& v2, Vec3& v3)
{
	if (std::abs(v1.x) > 0.9)
	{
		//v1がx軸方向のベクトルの可能性があるので、別方向に向けておく
		v2 = Vec3(0, 1, 0);
	}
	else
	{
		v2 = Vec3(1, 0, 0);
	}

	v2 = normalize(v2 - dot(v1, v2) * v1);
	v3 = cross(v1, v2);
}

//コンソール出力
inline std::ostream& operator<<(std::ostream& stream, const Vec3& v)
{
	stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return stream;
}

#endif