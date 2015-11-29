#define NOMINMAX

#include "baseinterface.h"
#include <set>
#include <limits>

class PrimaBinTreeV : public BaseInterface
{
protected:

	int *b;
	int *rebro;
	set<pair<int, int>> q;
public:
	void solve();
	void convert_to_str();
};
