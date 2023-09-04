#include <iostream>
#include <fstream>
#include <random>		//random_deviceを用いるのに必要
#include "Vector3.h"
#include "Ray.h"
#include "Image.h"
#include "Sphere.h"
#include "PinholeCamera.h"
#include "Aggregate.h"
using namespace std;
random_device rnd_dev;		//シードを決めるデバイス乱数
mt19937 mt(rnd_dev());		//メルセンヌ・ツイスタ
//http://vivi.dyndns.org/tech/cpp/random.html#range
uniform_real_distribution<> dist(0, 1);		//[0, 1]の一様乱数

inline double rnd()
{
	return dist(mt);
}

//34秒近くかかる
void ssaa()
{
	//サンプリング数
	const int N = 100;

	Image img(512, 512);
	PinholeCamera cam(Vec3(0), Vec3(0, 0, -1), 1);

	Aggregate aggregate;
	aggregate.add(make_shared<Sphere>(Sphere(Vec3(0, 0, -3), 1)));
	aggregate.add(make_shared<Sphere>(Sphere(Vec3(10001, 0, 0), 10000)));

	Vec3 sunDir = normalize(Vec3(-1, -1, 1));

	for (int k = 0; k < N; k++)
	{
		//乱数分だけ各ピクセルで取得する

		for (int i = 0; i < img.width; i++)
		{
			for (int j = 0; j < img.height; j++)
			{
				//(u, v)を計算
				//(i, j) ～ (i+1, j+1)のどこかの点を取得する
				double u = (2.0 * (i + rnd()) - img.width) / img.width;
				double v = (2.0 * (j + rnd()) - img.height) / img.height;

				//レイを生成
				Ray ray = cam.getRay(-u, -v);

				//球と当たった場合は法線を色にして書き込む
				Vec3 col;
				Hit res;

				if (aggregate.intersect(ray, res))
				{
					Ray shadowRay(res.hitPos + res.hitNormal * 0.001, sunDir);
					Hit res_temp;

					if (!aggregate.intersect(shadowRay, res_temp))
					{
						//光源方向へ飛ばしたレイが衝突しない = 光源が面までたどり着いている = 色がついている
						col = max(0.0, dot(res.hitNormal, sunDir)) * Vec3(1);
					}
				}

				img.addPixel(i, j, col);
			}
		}
	}

	img.divide(N);
	img.ppm_output("ssaa_shadow.ppm");
}

int main()
{
	//Vec3 v1(1, 2, 3);
	//Vec3 v2(4, 5, 6);

	//std::cout << v1 + v2 << std::endl;
	//std::cout << v1 - v2 << std::endl;
	//std::cout << v1 * v2 << std::endl;
	//std::cout << v1 / v2 << std::endl;

	//std::cout << v1 + 1 << std::endl;
	//std::cout << v1 - 1 << std::endl;
	//std::cout << v1 * 2 << std::endl;
	//std::cout << v1 / 2 << std::endl;

	//std::cout << dot(v1, v2) << std::endl;
	//std::cout << cross(v1, v2) << std::endl;

	//std::cout << v1.length() << std::endl;


	//Ray r(Vec3(0, 0, 0), Vec3(0, 0, 1));
	//cout << r << endl;
	//cout << r(10) << endl;


	//PPM画像のファイル形式
	/*
	P3  #PPM画像であることを示す
	2 2 #横幅 #縦幅
	255 #階調数
	#色データ (0, 0), (1, 0), (0, 1), (1, 1)と並ぶ
	*/
	//ofstream 出力ファイルストリームの機能を提供
	//ofstream file("ppm_test.ppm");
	//file << "P3" << endl;
	//file << 512 << " " << 512 << endl;
	//file << 255 << endl;
	//for (int i = 0; i < 512; i++)
	//{
	//	for (int j = 0; j < 512; j++)
	//	{
	//		int r = i / 512.0 * 255;
	//		int g = j / 512.0 * 255;
	//		int b = 255;

	//		file << r << " " << g << " " << b << endl;
	//	}
	//}
	//file.close();

	//Image img(512, 512);
	//for (int i = 0; i < img.width; i++)
	//{
	//	for (int j = 0; j < img.height; j++)
	//	{
	//		img.setPixel(i, j, Vec3(i / double(img.width), j / double(img.height), 1));
	//	}
	//}
	//img.ppm_output("image_test.ppm");

	//Sphere s(Vec3(0, 0, 0), 1);
	//Ray ray(Vec3(0, 0, -3), Vec3(0, 0, 1));
	//Hit res;

	//if (s.intersect(ray, res))
	//{
	//	cout << res.hitPos << endl;
	//}

	//Image image(512, 512);
	//PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1);

	//for (int i = 0; i < image.width; i++)
	//{
	//	for (int j = 0; j < image.height; j++)
	//	{
	//		double u = (2.0 * i - image.width) / image.width;
	//		double v = (2.0 * j - image.height) / image.height;

	//		//レイの作成
	//		Ray ray = cam.getRay(-u, -v);
	//		//ピクセルに書き込む色
	//		Vec3 col = (ray.direction + 1.0) / 2.0;

	//		image.setPixel(i, j, col);
	//	}
	//}

	//image.ppm_output("pinhole_test.ppm");

	//Image img(512, 512);

	//PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1.0);

	//Sphere sphere(Vec3(0, 0, -3), 1);

	//for (int i = 0; i < img.width; i++)
	//{
	//	for (int j = 0; j < img.height; j++)
	//	{
	//		//(u, v)を計算
	//		double u = (2.0 * i - img.width) / img.width;
	//		double v = (2.0 * j - img.height) / img.height;

	//		//レイを生成
	//		Ray ray = cam.getRay(-u, -v);

	//		//球と当たった場合は法線を色にして書き込む
	//		Vec3 col;
	//		Hit res;

	//		if (sphere.intersect(ray, res))
	//		{
	//			img.setPixel(i, j, (res.hitNormal + 1) / 2);
	//		}
	//		else
	//		{
	//			img.setPixel(i, j, Vec3(0, 0, 0));
	//		}
	//	}
	//}

	//img.ppm_output("single_sphere_tracing.ppm");

	//Image image(512, 512);
	//PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1);

	//Aggregate aggregate;

	////shared_ptrで所有権をシェアするには make_shared<T> を用いる
	//aggregate.add(make_shared<Sphere>(Sphere(Vec3(0, 0, -3), 1)));
	////擬似的な床として使用
	//aggregate.add(make_shared<Sphere>(Sphere(Vec3(10001, 0, 0), 10000)));


	//for (int i = 0; i < image.width; i++)
	//{
	//	for (int j = 0; j < image.height; j++)
	//	{
	//		//(u, v)を計算
	//		double u = (2.0 * i - image.width) / image.width;
	//		double v = (2.0 * j - image.height) / image.height;

	//		//レイを生成
	//		Ray ray = cam.getRay(-u, -v);

	//		//球と当たった場合は法線を色にして書き込む
	//		Vec3 col;
	//		Hit res;

	//		if (aggregate.intersect(ray, res))
	//		{
	//			image.setPixel(i, j, (res.hitNormal + 1) / 2);
	//		}
	//		else
	//		{
	//			image.setPixel(i, j, Vec3(0));
	//		}
	//	}
	//}

	//image.ppm_output("aggregate_test.ppm");

	//Image img(512, 512);
	//PinholeCamera cam(Vec3(0), Vec3(0, 0, -1), 1);

	//Aggregate aggregate;
	//aggregate.add(make_shared<Sphere>(Sphere(Vec3(0, 0, -3), 1)));
	//aggregate.add(make_shared<Sphere>(Sphere(Vec3(10001, 0, 0), 10000)));

	//Vec3 sunDir = normalize(Vec3(-1, -1, 1));

	//for (int i = 0; i < img.width; i++)
	//{
	//	for (int j = 0; j < img.height; j++)
	//	{
	//		//(u, v)を計算
	//		double u = (2.0 * i - img.width) / img.width;
	//		double v = (2.0 * j - img.height) / img.height;

	//		//レイを生成
	//		Ray ray = cam.getRay(-u, -v);

	//		//球と当たった場合は法線を色にして書き込む
	//		Vec3 col;
	//		Hit res;

	//		if (aggregate.intersect(ray, res))
	//		{
	//			Ray shadowRay(res.hitPos + res.hitNormal * 0.001, sunDir);
	//			Hit res_temp;

	//			if (!aggregate.intersect(shadowRay, res_temp))
	//			{
	//				//光源方向へ飛ばしたレイが衝突しない = 光源が面までたどり着いている = 色がついている
	//				col = max(0.0, dot(res.hitNormal, sunDir)) * Vec3(1);
	//			}
	//		}

	//		img.setPixel(i, j, col);
	//	}
	//}

	//img.ppm_output("draw_shadow.ppm");

	ssaa();
}
