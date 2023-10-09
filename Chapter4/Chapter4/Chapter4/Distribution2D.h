#ifndef DISTRIBUTION_2D
#define DISTRIBUTION_2D

using namespace std;
#include <vector>
#include "Distribution1D.h"
#include <memory>

class Distribution2D
{
private:
	std::vector<Distribution1D> pConditionV;
	Distribution1D pMarginal;

public:
	Distribution2D() : pConditionV(), pMarginal()
	{

	}

	Distribution2D(const int width, const int height, const vector<vector<float>> luminance)
	{
		for (int i = 0; i < width; i++)
		{
			std::vector<float> func;
			for (int j = 0; j < height; j++)
			{
				func.push_back(luminance[i][j]);
			}
			pConditionV.push_back(Distribution1D(func));
		}

		std::vector<float> mfunc;
		for (int i = 0; i < pConditionV.size(); i++)
		{
			mfunc.push_back(pConditionV[i].funcSum);
		}
		pMarginal = Distribution1D(mfunc);
	}
	/// <summary>
	/// サンプリング
	/// </summary>
	/// <param name="rnd">乱数値. first, secondいずれも0以上1以下の値が入る</param>
	/// <param name="pdf">確率密度関数</param>
	/// <returns></returns>
	pair<double, double> getSample(const pair<float, float> rnd, double& pdf) const
	{
		pair<int, int> uv;
		double pdf1, pdf2;
		unsigned int index;

		double u = pMarginal.sample(rnd.first, pdf1, index);
		double v = pConditionV[index].sample(rnd.second, pdf2, index);

		pdf = pdf1 * pdf2;
		return make_pair(u, v);
	}
};
#endif