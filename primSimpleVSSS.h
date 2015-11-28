#ifndef __PRIMA_H
#define __PRIMA_H

#include "baseinterface.h"

class PrimaSimpleVSSS : public BaseInterface {
public:
  void solve () override final;
};

#endif // __PRIMA_H
