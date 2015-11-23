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
			tempSet.insert(*(new Point(gg[j], jg[j])));
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
	while (fullWalk.size() < N)
	{
		int  minN = -1;
		int  minV = INT_MAX;
		int index1 = 0;
		int index2 = 0;
		for (int i = 0; i < fullWalk.size(); i++)
		{
			std::multiset<Point>::iterator it;
			if (treeQ[fullWalk[i]].size() > 0)
			{
				it = treeQ[fullWalk[i]].begin();
				index1 = 0;
				while (u[(*it).number_point])
				{
					if (index1 >= treeQ[fullWalk[i]].size()-1)
					{
						break;
					}
					it++;
					index1++;
				}
				Point h = *it;
				if ((h.weight < minV) && (!u[h.number_point]))
				{
					minV = h.weight;
					minN = fullWalk[i];
					index2 = index1;
				}
			}
		}
		std::multiset<Point>::iterator it;
		it = treeQ[minN].begin();
		std::advance(it, index2);
		int k = (*it).number_point;
		treeQ[minN].erase(it);
		fullWalk.push_back(k);
		p[k] = minN;
		d[k] = minV;
		u[k] = true;
		//cout << k << endl;
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

void PrimaBinTreeDGPP::clear()
{
	fullWalk.clear();
	p.clear();
	d.clear();
	delete[] u;
	treeQ.clear();
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