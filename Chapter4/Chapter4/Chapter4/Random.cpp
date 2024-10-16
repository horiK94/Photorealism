﻿#include <random>		//random_deviceを用いるのに必要
#define _USE_MATH_DEFINES
#include <math.h>

//メルセンヌ・ツイスタを乱数生成器として使用する
static std::random_device rnd_dev;		 //シードを決めるデバイス乱数
static std::mt19937 mt(rnd_dev());		 //メルセンヌ・ツイスタ
static std::uniform_real_distribution<> dist(0, 1); //[0, 1]の一様乱数

double rnd()
{
	return dist(mt);
}

/// <summary>
/// 半径1の円内の点を一様サンプリング
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void sampleDisk(double& x, double& y)
{
	//レンズのどこを通るか
	double u1 = rnd();
	double u2 = rnd();

	x = std::sqrt(u1) * std::cos(2 * M_PI * u2);
	y = std::sqrt(u1) * std::sin(2 * M_PI * u2);
}