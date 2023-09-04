#ifndef IBL_H
#define IBL_H
#include "Sky.h"
#define _USE_MATH_DEFINES
#include <math.h>

class IBL : public Sky
{
	//360���摜��p����
public:
	int width;
	int height;
	float* hdr_img;		//HDR�摜(�ʏ�̉摜����0�`1�܂ł����擾�ł��Ȃ�����)

	IBL(const std::string fileName)
	{
		int n;		//�摜���\�����Ă���F�`���l�������ۂ�
		hdr_img = stbi_loadf(fileName.c_str(), &width, &height, &n, 0);
	}

	~IBL()
	{
		stbi_image_free(hdr_img);
	}

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

		//(i, j)�̔z����ɂ�����C���f�b�N�X���v�Z
		//�摜�f�[�^�� R, G, B, R, G, B...�Ƃ��������Ŋi�[����Ă���
		int index = 3 * i + width * 3 * j;

		return Vec3(hdr_img[index], hdr_img[index + 1], hdr_img[index + 2]);
	}
};

#endif