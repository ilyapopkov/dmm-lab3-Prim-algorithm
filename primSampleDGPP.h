#include <string>
#include <vector>
#include "baseinterface.h"
#include <algorithm> 

using namespace std;

class PrimaSampleDGPP : public BaseInterface
{
protected:
	void convert_from_str();
	void convert_to_str();
public:
	void solve();
	vector<int> p;
	vector<int> d;
};
