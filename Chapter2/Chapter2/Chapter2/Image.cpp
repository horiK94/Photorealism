#include "Image.h"
#include "Util.h"
#include <fstream>

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
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
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
