#ifndef IBL_H
#define IBL_H
#include "Sky.h"
#include <algorithm>
#include "Distribution2D.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "Random.h"

class IBL : public Sky
{
	//360°画像を用いる
public:
	int width;
	int height;
	float* hdr_img;		//HDR画像(通常の画像だと0～1までしか取得できないため)
	Distribution2D distribution;

	IBL(const std::string fileName)
	{
		int n;		//画像が構成している色チャネル数っぽい
		hdr_img = stbi_loadf(fileName.c_str(), &width, &height, &n, 0);

		//2次元分布関数を作成
		vector<vector<float>> luminances;
		for (int i = 0; i < width; i++)
		{
			vector<float> luminance;
			for (int j = 0; j < height; j++)
			{
				luminance.push_back(GetLuminance(getColor(i, j)));
			}
			luminances.push_back(luminance);
		}
		distribution = Distribution2D(width, height, luminances);
	}

	~IBL()
	{
		stbi_image_free(hdr_img);
	}

	/// <summary>
	/// 方向から放射輝度を取得する
	/// </summary>
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

		return getColor(i, j);
	}

	/// <summary>
	/// 重み付けした乱数サンプリングを行う
	/// </summary>
	Vec3 sampling(Ray& sample, double& pdf) const
	{
		std::pair<double, double> uv = distribution.getSample(std::make_pair(rnd(), rnd()), pdf);
		double theta = uv.first * M_PI;		//0～π
		double phi = uv.second * 2 * M_PI;		//0～2π. 重点サンプリングの方法と揃える

		pdf /= (2 * M_PI * M_PI / sin(theta));

		//画像のどの点を取得するか決定(i, j)
		int i = (int)(phi / (2 * M_PI) * width) % width;
		int j = (int)(theta / M_PI * height) % height;
		return getColor(i, j);
	}

	Vec3 getColor(int u, int v) const
	{
		//(i, j)の配列内におけるインデックスを計算
		//画像データは R, G, B, R, G, B...という感じで格納されている
		int index = 3 * u + width * 3 * v;

		return Vec3(hdr_img[index], hdr_img[index + 1], hdr_img[index + 2]);
	}

	static float GetLuminance(const Vec3& color)
	{
		//グレースケール変換したものを輝度として扱う
		return 0.299 * color.x + 0.587 * color.y + 0.114 * color.z;
	}
};

#endif