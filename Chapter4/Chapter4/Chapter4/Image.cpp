#include "Image.h"
#include "Util.h"
#include <fstream>
#include <vector>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define __STDC_LIB_EXT1__
#include "stb_image_write.h"

Vec3 Image::getPixel(int i, int j) const
{
	return data[i + width * j];
}

void Image::setPixel(int i, int j, const Vec3& c)
{
	data[i + width * j] = c;
}

void Image::addPixel(int i, int j, const Vec3& c)
{
	data[i + width * j] = data[i + width * j] + c;
}

void Image::divide(double k)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			this->setPixel(i, j, this->getPixel(i, j) / k);
		}
	}
}

void Image::gamma_correction()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			Vec3 c = this->getPixel(i, j);
			this->setPixel(i, j, Vec3(std::pow(c.x, 1 / 2.2), std::pow(c.y, 1 / 2.2), std::pow(c.z, 1 / 2.2)));
		}
	}
}

void Image::ppm_output(const std::string& filename) const
{
	std::ofstream file(filename);

	file << "P3" << std::endl;
	file << width << " " << height << std::endl;
	file << GRADUATION_NUM << std::endl;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			Vec3 c = getPixel(i, j);
			int r = clamp((int)(GRADUATION_NUM * c.x), 0, GRADUATION_NUM);
			int g = clamp((int)(GRADUATION_NUM * c.y), 0, GRADUATION_NUM);
			int b = clamp((int)(GRADUATION_NUM * c.z), 0, GRADUATION_NUM);

			file << r << " " << g << " " << b << std::endl;
		}
	}

	file.close();
}

void Image::png_output(const std::string& filename) const
{
	std::vector<unsigned char> pixels(width * height * 4);
	int64_t i = 0;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			Vec3 pixel = getPixel(x, y);
			pixels[i * 4 + 0] = clamp((int)(GRADUATION_NUM * pixel.x), 0, GRADUATION_NUM);
			pixels[i * 4 + 1] = clamp((int)(GRADUATION_NUM * pixel.y), 0, GRADUATION_NUM);
			pixels[i * 4 + 2] = clamp((int)(GRADUATION_NUM * pixel.z), 0, GRADUATION_NUM);
			pixels[i * 4 + 3] = 255;
			i++;
		}
	}

	stbi_write_png(filename.c_str(), width, height, 4, pixels.data(), width * 4);
}