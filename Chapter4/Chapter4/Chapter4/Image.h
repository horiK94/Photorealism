#ifndef IMAGE_H
#define IMAGE_H
#include "Vector3.h"

class Image
{
public:
	int width;
	int height;

	const int GRADUATION_NUM = 255;

	Vec3* data;

	Image(int _width, int _height) : width(_width), height(_height)
	{
		data = new Vec3[width * height];
	}

	~Image()
	{
		delete[] data;
	}

	Vec3 getPixel(int i, int j) const;

	void setPixel(int i, int j, const Vec3& c);
	void addPixel(int i, int j, const Vec3& c);

	//全ピクセルを引数で割る
	void divide(double k);

	//ガンマ補正をすることで、リニアな色変換が可能になる
	void gamma_correction();

	/// <summary>
	/// PPM画像出力
	/// </summary>
	/// <param name="filename"></param>
	void ppm_output(const std::string& filename) const;

	void png_output(const std::string& filename) const;
};
#endif