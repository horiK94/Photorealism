﻿// Chapter4.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <memory>
#include <iostream>
#include "Vector3.h"
#include "Ray.h"
#include "Aggregate.h"
#include "Material.h"
#include "Image.h"
#include "PinholeCamera.h"
#include "ThinLensCamera.h"
#include "Random.h"
#include <omp.h>
#include "Sphere.h"
#include "Diffuse.h"
#include "Mirror.h"
#include "SimplySky.h"
#include "IBL.h"
#include "Glass.h"

Vec3 raddiance(const Ray& init_ray, const Aggregate& aggregate, const Sky& sky);

int main()
{
	const int N = 100;      //サンプリング数

	Image img(512, 512);
	//PinholeCamera cam(Vec3(0, 0, 1), Vec3(0, 0, -1), 1);
	//ThinLensCamera cam(Vec3(0, 0, 1), Vec3(0, 0, -1), Vec3(0, 0, -3), 1, 0.1);
	//コーネルボックス
	ThinLensCamera cam(Vec3(0, 0, 4), Vec3(0, 0, -1), Vec3(0, 0, 0), 1, 0.1);

	//auto mat1 = make_shared<Diffuse>(Vec3(0.9));        //白色
	////auto mat1 = make_shared<Mirror>();        //白色
	//auto mat2 = make_shared<Diffuse>(Vec3(0.2, 0.8, 0.2));        //青色
	//ガラス
	//auto mat1 = make_shared<Diffuse>(Vec3(0.9));        //白色
	//auto mat2 = make_shared<Glass>(1.5);        //青色

	//auto light1 = make_shared<Light>(Vec3(0));
	//auto light2 = make_shared<Light>(Vec3(0));
	//auto light2 = make_shared<Light>(Vec3(0.2, 0.8, 0.2));      //光の色: 青

	//コーネルボックス
	auto mat1 = make_shared<Diffuse>(Vec3(0.8));		//白
	auto mat2 = make_shared<Diffuse>(Vec3(0.8, 0.2, 0.2));		//赤
	auto mat3 = make_shared<Diffuse>(Vec3(0.2, 0.8, 0.2));		//緑][
	auto mat4 = make_shared<Glass>(1.5);

	auto light1 = make_shared<Light>(Vec3(0));
	auto light2 = make_shared<Light>(Vec3(10));

	Aggregate aggregate;
	//aggregate.add(make_shared<Sphere>(Vec3(0, -10001, 0), 10000, mat1, light1));      //床
	//aggregate.add(make_shared<Sphere>(Vec3(0, 0, -3), 1, mat2, light1));      //床
	//aggregate.add(make_shared<Sphere>(Vec3(0, 0, -3), 1, mat2, light2));      //球

	//コーネルボックス
	aggregate.add(std::make_shared<Sphere>(Vec3(0, -10001, 0), 10000, mat1, light1));		//床
	aggregate.add(std::make_shared<Sphere>(Vec3(10003, 0, 0), 10000, mat2, light1));		//右の壁
	aggregate.add(std::make_shared<Sphere>(Vec3(-10003, 0, 0), 10000, mat3, light1));		//左の壁
	aggregate.add(std::make_shared<Sphere>(Vec3(0, 10003, 0), 10000, mat1, light1));		//天井
	aggregate.add(std::make_shared<Sphere>(Vec3(0, 0, -10003), 10000, mat1, light1));		//後ろの壁
	aggregate.add(std::make_shared<Sphere>(Vec3(0, 0, 0), 1, mat4, light1));		//球
	aggregate.add(std::make_shared<Sphere>(Vec3(0, 3, 0), 1, mat1, light2));		//光源

	//SimplySky sky;
	IBL sky = IBL("dikhololo_night_4k.hdr");

#pragma omp parallel for schedule(dynamic, i)
	for (int i = 0; i < img.width; i++)
	{
		for (int j = 0; j < img.height; j++)
		{
			for (int k = 0; k < N; k++)
			{
				//(u, v)の計算
				double u = (2.0 * (i + rnd()) - img.width) / img.width;
				double v = (2.0 * (j + rnd()) - img.height) / img.height;

				//レイを生成(ピンホールカメラは反転するのでマイナスを付ける)
				Ray ray = cam.getRay(-u, -v);

				//放射輝度を計算
				Vec3 col = raddiance(ray, aggregate, sky);

				//サンプル加算
				img.addPixel(i, j, col);
			}

			//進歩状況の出力
			if (omp_get_thread_num() == 0)
			{
				cout << double(j + i * img.height) / (img.width * img.height) * 100 << "\r" << endl;
			}
		}
	}

	//サンプリング数で割る
	img.divide(N);

	//ガンマ補正
	img.gamma_correction();

	//PPM出力
	img.ppm_output("dikhololo_night_4k_glass.ppm");
}

const int MAX_DEPTH = 500;      //最大反射回数
const double ROULETTE = 0.99;        //ロシアンルーレットの確率

/// <summary>
/// init_rayの方向から来る放射輝度の値を計算して返す
/// </summary>
/// <param name="init_ray">最初のレイ</param>
/// <param name="aggregate">物体の集合データ</param>
/// <returns></returns>
Vec3 raddiance(const Ray& init_ray, const Aggregate& aggregate, const Sky& sky)
{
	Vec3 col;       //最終的な色
	Vec3 throughput(1);     //途中までの計算結果
	Ray ray = init_ray;     //計算によって更新されるレイ

	//級数の評価
	for (int depth = 0; depth < MAX_DEPTH; depth++)
	{
		Hit res;

		if (aggregate.intersect(ray, res))
		{
			//物体に衝突
			//法線
			Vec3 n = res.hitNormal;

			//法線を1線とした正規直交基底ベクトルを作成
			Vec3 s, t;
			orthonormalBasis(n, s, t);
			//射出方向をローカル座標系に変換
			Vec3 wo_local = worldToLocal(-ray.direction, s, n, t);

			//マテリアルと光源の取得
			auto hitMaterial = res.hitSphere->material;
			auto hitLight = res.hitSphere->light;

			//当たった球体のLeの加算
			col += throughput * hitLight->Le();

			//方向のサンプリングとBRDFの評価
			Vec3 brdf;
			Vec3 wi_local;
			double pdf;
			brdf = hitMaterial->sample(wo_local, wi_local, pdf);
			//コサイン
			double cos = absCosTheta(wi_local);
			//サンプリングされた方向をワールド座標系に変換
			Vec3 wi = localToWorld(wi_local, s, n, t);

			//スループットの更新
			throughput *= brdf * cos / pdf;

			//次のレイを生成
			ray = Ray(res.hitPos, wi);
		}
		else
		{
			//空に飛んで行った場合
			//col += throughput * Vec3(1);
			//col += throughput * Vec3(0);
			col += throughput * sky.getRadiance(ray);
			break;
		}

		//ロシアンルーレット
		if (rnd() >= ROULETTE)
		{
			break;
		}
		else
		{
			throughput /= ROULETTE;
		}
	}

	return col;
}