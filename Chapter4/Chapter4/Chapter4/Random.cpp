#include <random>		//random_device��p����̂ɕK�v
#define _USE_MATH_DEFINES
#include <math.h>

//�����Z���k�E�c�C�X�^�𗐐�������Ƃ��Ďg�p����
static std::random_device rnd_dev;		 //�V�[�h�����߂�f�o�C�X����
static std::mt19937 mt(rnd_dev());		 //�����Z���k�E�c�C�X�^
static std::uniform_real_distribution<> dist(0, 1); //[0, 1]�̈�l����

double rnd()
{
	return dist(mt);
}

/// <summary>
/// ���a1�̉~���̓_����l�T���v�����O
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void sampleDisk(double& x, double& y)
{
	double u1 = rnd();
	double u2 = rnd();

	x = std::sqrt(u1) * std::cos(2 * M_PI * u2);
	y = std::sqrt(u1) * std::sin(2 * M_PI * u2);
}