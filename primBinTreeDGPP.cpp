#include"primBinTreeDGPP.h"



void PrimaBinTreeDGPP::convert_from_str()
{
	clear();
	N = ig.size() - 1;
	p = vector<int>(N, -1);
	d = vector<int>(N, INT_MAX);
	u = new bool[N];
	multiset<Point> tempSet;
	size_t ind[2];
	ind[0] = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = ig[i]; j < ig[i + 1]; j++)
		{
			tempSet.insert(*(new Point(gg[j], jg[j], i)));
		}
		if (tempSet.size() > 0)
		{
			treeQ.push_back(tempSet);
		}
		tempSet.clear();
	}

	for (int i = 0; i < N; i++)
	{
		u[i] = 0;
	}
}

void PrimaBinTreeDGPP::solve()
{
	vector<int> gg_temp;
	vector<size_t> ig_temp;
	vector<size_t> jg_temp(jg.size());

	fullWalk.push_back(0);
	u[0] = 1;
	d[0] = 0;
	if (treeQ.size()!= 0)
	{

		addPointSort(treeQ[0]);
		while (fullWalk.size() < N)
		{
			std::multiset<Point>::iterator it1;
			while (sortPoint.size() > 0)
			{
				it1 = sortPoint.begin();
				if (!u[(*it1).number_point])
				{
					break;
					
				} 
				sortPoint.erase(it1);
			}
			if (sortPoint.size() == 0)
			{
				break;
			}
			fullWalk.push_back((*it1).number_point);
			p[(*it1).number_point] = (*it1).parentPoint;
			d[(*it1).number_point] = (*it1).weight;
			u[(*it1).number_point] = true;
			int n = (*it1).number_point;
			sortPoint.erase(it1);
			addPointSort(treeQ[n]);

			
		}
	}
}

void PrimaBinTreeDGPP::convert_to_str()
{
	ig.clear();
	gg.clear();
	jg.clear();
	ig.push_back(0);
	ig.push_back(count(p.begin(), p.end(), 0));


	for (int i = 1; i < p.size(); i++)
	{
		ig.push_back(ig[i] + count(p.begin(), p.end(), i) + 1);
	}

	gg = vector<int>(ig[ig.size() - 1]);
	jg = vector<size_t>(ig[ig.size() - 1]);
	vector<size_t>  tempPos(p.size(), 0);
	for (int i = 1; i < p.size(); i++)
	{
		if (p[i] != -1)
		{
			gg[ig[p[i]] + tempPos[p[i]]] = d[i];
			jg[ig[p[i]] + tempPos[p[i]]] = i;
			tempPos[p[i]]++;

			gg[ig[i] + tempPos[i]] = d[i];
			jg[ig[i] + tempPos[i]] = p[i];
			tempPos[i]++;

		}

	}

	for (int i = 1; i < p.size(); i++)
	{
		size_t begin = ig[i - 1];
		size_t end = ig[i];
		size_t min = begin;
		for (int j = begin; j < end; j++)
		{
			for (int l = j + 1; l < end; l++)
			{
				if (jg[l] < jg[min])
				{

					int tempIndJ = jg[l];
					int tempIndG = gg[l];
					jg[l] = jg[min];
					gg[l] = gg[min];
					jg[min] = tempIndJ;
					gg[min] = tempIndG;
					min = l;
				}
			}
		}
	}

}

void PrimaBinTreeDGPP::addPointSort(multiset<Point> points)
{
	if (points.size() > 0)
	{
		sortPoint.insert(points.begin(), points.end());
	}
}

void PrimaBinTreeDGPP::clear()
{
	fullWalk.clear();
	p.clear();
	d.clear();
	delete[] u;
	treeQ.clear();
	sortPoint.clear();
}

bool PrimaBinTreeDGPP::Point::operator < (const PrimaBinTreeDGPP::Point & t) const
{
	if (weight < t.weight) return true;
	if (weight > t.weight) return false;
	return false;
}
bool PrimaBinTreeDGPP::Point::operator == (const PrimaBinTreeDGPP::Point & t) const
{
	if (weight == t.weight) return true;
	return false;
}