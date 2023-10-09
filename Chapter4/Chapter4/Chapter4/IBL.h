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
	//360���摜��p����
public:
	int width;
	int height;
	float* hdr_img;		//HDR�摜(�ʏ�̉摜����0�`1�܂ł����擾�ł��Ȃ�����)
	Distribution2D distribution;

	IBL(const std::string fileName)
	{
		int n;		//�摜���\�����Ă���F�`���l�������ۂ�
		hdr_img = stbi_loadf(fileName.c_str(), &width, &height, &n, 0);

		//2�������z�֐����쐬
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
	/// ����������ˋP�x���擾����
	/// </summary>
	Vec3 getRadiance(const Ray& ray) const
	{
		//���������ʍ��W�n�ɕϊ�
		double theta = std::acos(ray.direction.y);		//0�`��
		double phi = std::atan2(ray.direction.z, ray.direction.x);		// -�΁`��
		if (phi < 0)
		{
			phi += 2 * M_PI;
		}

		//�摜�̂ǂ̓_���擾���邩����(i, j)
		int i = phi / (2 * M_PI) * width;
		int j = theta / M_PI * height;

		return getColor(i, j);
	}

	/// <summary>
	/// �d�ݕt�����������T���v�����O���s��
	/// </summary>
	Vec3 sampling(Ray& sample, double& pdf) const
	{
		std::pair<double, double> uv = distribution.getSample(std::make_pair(rnd(), rnd()), pdf);
		double theta = uv.first * M_PI;		//0�`��
		double phi = uv.second * 2 * M_PI;		//0�`2��. �d�_�T���v�����O�̕��@�Ƒ�����

		pdf /= (2 * M_PI * M_PI / sin(theta));

		//�摜�̂ǂ̓_���擾���邩����(i, j)
		int i = (int)(phi / (2 * M_PI) * width) % width;
		int j = (int)(theta / M_PI * height) % height;
		return getColor(i, j);
	}

	Vec3 getColor(int u, int v) const
	{
		//(i, j)�̔z����ɂ�����C���f�b�N�X���v�Z
		//�摜�f�[�^�� R, G, B, R, G, B...�Ƃ��������Ŋi�[����Ă���
		int index = 3 * u + width * 3 * v;

		return Vec3(hdr_img[index], hdr_img[index + 1], hdr_img[index + 2]);
	}

	static float GetLuminance(const Vec3& color)
	{
		//�O���[�X�P�[���ϊ��������̂��P�x�Ƃ��Ĉ���
		return 0.299 * color.x + 0.587 * color.y + 0.114 * color.z;
	}
};

#endif