#ifndef SKY_H
#define SKY_H
#include "Vector3.h"
#include "Ray.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC		//????
#define STB_IMAGE_IMPLEMENTATION
#include "std_image.h"
#endif // STB_IMAGE_IMPLEMENTATION

class Sky
{
public:
	Vec3 color;		//��̐F

	/// <summary>
	/// �󂯎�������C�̕����痈���̕��ˋP�x�̒l��Ԃ�
	/// </summary>
	/// <param name="ray"></param>
	/// <returns></returns>
	virtual Vec3 getRadiance(const Ray& ray) const = 0;

	virtual Vec3 sampling(Ray& sample, double& pdf) const = 0;
};
#endif
