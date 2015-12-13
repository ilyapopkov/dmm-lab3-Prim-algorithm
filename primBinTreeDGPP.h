#include <string>
#include <vector>
#include <set>
#include "baseinterface.h"
#include <algorithm> 

using namespace std;

class PrimaBinTreeDGPP : public BaseInterface
{
protected:
	struct Point {
		int weight;
		int number_point;
		int parentPoint;
	public:
		Point(int w, int number , int parent)
		{
			weight = w;
			number_point = number;
			parentPoint = parent;
		}
		bool operator < (const Point & t) const;
		bool operator == (const Point & t) const;
	};
private:

	int N;
	vector<multiset<Point>> treeQ;
	multiset<Point> sortPoint;
	bool  *u;
	vector<size_t> fullWalk;
	void convert_from_str();
	void convert_to_str();
	void addPointSort(multiset<Point> points);
	void clear();
public:
	void solve();
	vector<int> p;
	vector<int> d;
};
