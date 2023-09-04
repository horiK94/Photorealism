#ifndef AGGREGATE_H
#define AGGREGATE_H

#include <memory>
#include <vector>
#include "Ray.h"
#include "Hit.h"
#include "Sphere.h"
using namespace std;

class Aggregate
{
public:
	//shared_ptr: 
	vector<shared_ptr<Sphere>> spheres;

	Aggregate() {};
	Aggregate(const vector<shared_ptr<Sphere>>& _spheres) : spheres(_spheres) {};

	void add(const shared_ptr<Sphere> s)
	{
		spheres.push_back(s);
	};

	bool intersect(const Ray& ray, Hit& res) const
	{
		bool hit = false;
		for (auto s : spheres)
		{
			Hit res_tmp;
			if (s->intersect(ray, res_tmp))
			{
				if (res_tmp.t < res.t)
				{
					//X‚ÉŽè‘O‚É‚ ‚é•¨‘Ì‚É“–‚½‚é
					hit = true;
					res = res_tmp;
				}
			}
		}

		return hit;
	}
};
#endif

