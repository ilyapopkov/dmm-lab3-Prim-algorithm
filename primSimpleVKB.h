#define NOMINMAX

#include "baseinterface.h"
#include <limits>
/*
 * Волк
 * Кислицын
 * Бублей
 */

class PrimaSimpleVKB: public BaseInterface
{
protected:

	int *b;
	int *rebro;
public:
	void solve();
	void convert_to_str();
};
