#include "primSampleDGPP.h"


void PrimaSampleDGPP::convert_from_str()
{
	 p = vector<int>(ig.size() - 1, -1);
	 d = vector<int>(ig.size() - 1, INT_MAX);
}

void PrimaSampleDGPP::solve()
{

	vector<bool> u(ig.size() - 1, 0);
	vector<int> gg_temp;
	vector<size_t> ig_temp;
	vector<size_t> jg_temp(jg.size());
	while (true)
	{
		int  minN = -1;
		int  minV = INT_MAX;
		u[0] = 1;
		d[0] = 0;
		for (int i = 0; i < u.size(); i++)
		{
			if (u[i])
			{
				size_t j = *(ig.begin() + i);
				size_t J_end = *(ig.begin() + i + 1);

				while (j < J_end)
				{
					if (minV > gg[j])
					{
						if ((jg[j] != i) && (!u[jg[j]]))
						{
							minV = gg[j];
							minN = jg[j];
							p[minN] = i;
						}
					}
					j++;
				}

			}
		}

		if (minN == -1)
		{
			break;
		}
		else
		{
			u[minN] = 1;
			d[minN] = minV;
		}
	}
}
void PrimaSampleDGPP::convert_to_str()
{
	ig.clear(); 
	gg.clear();
	jg.clear();
	ig.push_back(0);
	ig.push_back(count(p.begin(), p.end(), 0));


	for (int i = 1; i < p.size(); i++)
	{
		ig.push_back(ig[i] + count(p.begin(), p.end(), i) + 1 );
	}

	gg = vector<int>(ig[ig.size()  - 1]);
	jg = vector<size_t>(ig[ig.size() - 1]);
	vector<size_t>  tempPos (p.size(), 0);
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
