#include <string>
#include <vector>
#include <set>
#include "baseinterface.h"
#include <algorithm> 

using namespace std;

class PrimaSimpleDGPP : public BaseInterface
{
protected:
	struct Point {
		int weight;
		int number_point;
	public:
		Point(int w, int number)
		{
			weight = w;
			number_point = number;
		}
		bool operator < (const Point & t) const;
		bool operator == (const Point & t) const;
	};
private:

	int N;
	vector<multiset<Point>> treeQ;
	bool  *u;
	vector<size_t> fullWalk;
	void convert_from_str();
	void convert_to_str();
	void clear();
public:
	void solve();
	vector<int> p;
	vector<int> d;
};
