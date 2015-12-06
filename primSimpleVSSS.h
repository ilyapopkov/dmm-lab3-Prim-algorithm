#include "baseinterface.h"

/*
 * Vaytsel
 * Sarychev
 * Stepanova
 * Sayfullaeva
 */

class PrimaSimpleVSSS : public BaseInterface {
  vector<int> rebra;
public:
  void solve () override final;
  void convert_to_str() override final;
};
