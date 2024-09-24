#ifndef AGGREGATE_H
#define AGGREGATE_H

#include <memory>
#include <vector>
#include "Ray.h"
#include "Hit.h"
#include "Shape.h"
using namespace std;

class Aggregate
{
public:
	//shared_ptr: 
	vector<shared_ptr<Shape>> shapes;

	Aggregate() {};
	Aggregate(const vector<shared_ptr<Shape>>& _spheres) : shapes(_spheres) {};

	void add(const shared_ptr<Shape> s)
	{
		shapes.push_back(s);
	};

	bool intersect(const Ray& ray, Hit& res) const
	{
		bool hit = false;
		for (auto s : shapes)
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

