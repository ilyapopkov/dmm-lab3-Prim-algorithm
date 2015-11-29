#include "primBinTreeV.h"

void PrimaBinTreeV::solve()
{
	int to = 0; 
	int v = 0;
	int cost = 0;
	bool *check;
	int i, j, nmin=0;
	int otkuda = 0;
	check = new bool[size];
	b = new int[size];
	rebro = new int[size];

	for (i = 0; i < size; i++)
	{
        b[i] = numeric_limits<int>::max();
		rebro[i] = 0;
		check[i] = false;
	}

	q.insert(make_pair(cost, to));
	b[nmin] = 0;
	for (i = 0; i < size; i++)
	{
		int colElement = ig[v + 1] - ig[v];
		check[v] = true;
		otkuda = v;
		v = ig[v];
		for (j = 0; j < colElement; j++)
		{
			cost = gg[v];
			to = jg[v];
			v++;
			if (cost < b[to] && check[to] == false)
			{
				b[to] = cost;
				rebro[to] = otkuda;
				q.insert(make_pair(cost, to));
			}
		}
		v = q.begin()->second;
		q.erase(q.begin());
	}
	convert_to_str();
}

void PrimaBinTreeV::convert_to_str()
{
	ig.clear();
	jg.clear();
	gg.clear();
	int i, j;
	int jg_size = 0;
	for (i = 0; i < size; i++)
	if (b[i] != 0)
		jg_size += 2;

	ig.push_back(0);

	for (i = 0; i < size; i++)
	{
		ig.push_back(ig[i]);
		if (i > rebro[i])
		{
			gg.push_back(b[i]);
			jg.push_back(rebro[i]);
			ig[i + 1]++;
			for (j = 1; j < size; j++)
			{
				if (rebro[j] == i)
				{
					ig[i + 1] ++;
					jg.push_back(j);
					gg.push_back(b[j]);
				}
			}
		}
		else
		{
			for (j = 1; j < size; j++)
			{
				if (rebro[j] == i)
				{
					ig[i + 1] ++;
					jg.push_back(j);
					gg.push_back(b[j]);
				}
			}
			if (i != 0)
			{
				gg.push_back(b[i]);
				jg.push_back(rebro[i]);
				ig[i + 1]++;
			}

		}
	}
}
