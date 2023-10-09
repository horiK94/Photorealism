#ifndef DISTRIBUTION_1D
#define DISTRIBUTION_1D

using namespace std;
#include <vector>
#include <iostream>

class Distribution1D
{
public:
	vector<float> func;		//分布値
	vector<float> cdf;		//確率分布関数

	float funcSum;		//分布値の合計

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
			//同じ確率密度関数だとして分布値を算出する
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
				//cdfの正規化
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
	/// サンプリング
	/// </summary>
	/// <param name="u">乱数値. 0以上1以下の値が入る</param>
	/// <param name="pdf">確率密度関数</param>
	/// <param name="offset">サンプリング位置</param>
	/// <returns></returns>
	float sample(const float u, double& pdf, unsigned int& offset) const
	{
		offset = getOffset(u);
		float du = u - cdf[offset];		//取得した区域の開始位置からの距離

		if (cdf[offset + 1] - cdf[offset] > 0.0)
		{
			//取得した区域内の位置の割合
			du /= cdf[offset + 1] - cdf[offset];
		}

		//確率密度関数は v_i / ∫f(x) dx
		pdf = func[offset] / funcSum;

		//サンプリング位置を返す
		return (offset + du) / Count();
	}
};
#endif