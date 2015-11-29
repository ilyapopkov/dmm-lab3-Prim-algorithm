#include "primUnknownV.h"
void PrimaUnknownV::solve()
{
	bool *check;
	int i, j, nmin,min;

	check = new bool[size];
	b = new int[size];
	rebro = new int[size];
	for (i = 0; i < size; i++)
	{
        b[i] = numeric_limits<int>::max();
		check[i] = false;
	}
	nmin = 0;
	int to = 0, v = 0;
	int cost = 0;
	int otkuda = 0;
	b[nmin] = 0;
	rebro[nmin] = 0;
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
			}
		}
        min = numeric_limits<int>::max();
		for (int l = 0; l < size; l++) //заменить N на количество не чекнутых (n-i)
		{
			if (b[l] < min && check[l] == false)
			{
				min = b[l];
				v = l;
			}
		}
	}
	convert_to_str();
}
void PrimaUnknownV::convert_to_str()
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
