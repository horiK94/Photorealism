#ifndef IBL_H
#define IBL_H
#include "Sky.h"
#define _USE_MATH_DEFINES
#include <math.h>

class IBL : public Sky
{
	//360°画像を用いる
public:
	int width;
	int height;
	float* hdr_img;		//HDR画像(通常の画像だと0～1までしか取得できないため)

	IBL(const std::string fileName)
	{
		int n;		//画像が構成している色チャネル数っぽい
		hdr_img = stbi_loadf(fileName.c_str(), &width, &height, &n, 0);
	}

	~IBL()
	{
		stbi_image_free(hdr_img);
	}

	Vec3 getRadiance(const Ray& ray) const
	{
		//方向を球面座標系に変換
		double theta = std::acos(ray.direction.y);		//0～π
		double phi = std::atan2(ray.direction.z, ray.direction.x);		// -π～π
		if (phi < 0)
		{
			phi += 2 * M_PI;
		}

		//画像のどの点を取得するか決定(i, j)
		int i = phi / (2 * M_PI) * width;
		int j = theta / M_PI * height;

		//(i, j)の配列内におけるインデックスを計算
		//画像データは R, G, B, R, G, B...という感じで格納されている
		int index = 3 * i + width * 3 * j;

		return Vec3(hdr_img[index], hdr_img[index + 1], hdr_img[index + 2]);
	}
};

#endif