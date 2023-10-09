#ifndef DISTRIBUTION_1D
#define DISTRIBUTION_1D

using namespace std;
#include <vector>
#include <iostream>

class Distribution1D
{
public:
	vector<float> func;		//���z�l
	vector<float> cdf;		//�m�����z�֐�

	float funcSum;		//���z�l�̍��v

	Distribution1D() : funcSum(0), func(), cdf()
	{

	}

	Distribution1D(const vector<float> infunc)
	{
		unsigned int n = infunc.size();
		func = infunc;

		cdf.push_back(0);
		for (int i = 1; i < n + 1; i++)
		{
			cdf.push_back(cdf[i - 1] + func[i - 1] / n);
		}

		funcSum = cdf[n];

		if (funcSum == 0)
		{
			//�����m�����x�֐����Ƃ��ĕ��z�l���Z�o����
			for (int i = 0; i < n + 1; i++)
			{
				cdf[i] = (float)i / n;
			}
		}
		else
		{
			float divFuncInt = 1 / funcSum;
			for (int i = 0; i < n + 1; i++)
			{
				//cdf�̐��K��
				cdf[i] *= divFuncInt;
			}
		}
	}

	int Count() const { return func.size(); }

	unsigned int getOffset(float u) const
	{
		auto iter = lower_bound(cdf.begin(), cdf.end(), u);
		unsigned int index = iter - cdf.begin();
		return min(index, (unsigned int)cdf.size() - 2);
	}

	/// <summary>
	/// �T���v�����O
	/// </summary>
	/// <param name="u">�����l. 0�ȏ�1�ȉ��̒l������</param>
	/// <param name="pdf">�m�����x�֐�</param>
	/// <param name="offset">�T���v�����O�ʒu</param>
	/// <returns></returns>
	float sample(const float u, double& pdf, unsigned int& offset) const
	{
		offset = getOffset(u);
		float du = u - cdf[offset];		//�擾�������̊J�n�ʒu����̋���

		if (cdf[offset + 1] - cdf[offset] > 0.0)
		{
			//�擾���������̈ʒu�̊���
			du /= cdf[offset + 1] - cdf[offset];
		}

		//�m�����x�֐��� v_i / ��f(x) dx
		pdf = func[offset] / funcSum;

		//�T���v�����O�ʒu��Ԃ�
		return (offset + du) / Count();
	}
};
#endif