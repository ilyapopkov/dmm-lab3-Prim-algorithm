#include "primSimpleVSSS.h"
#include <vector>
void PrimaSimpleVSSS::solve () {
  vector<bool> you_in_ostov (size, false); you_in_ostov[0] = true;
  vector<int> b(size, INT_MAX); b[0] = 0;
  rebra.clear(); rebra.resize(size, -1); rebra[0] = 0;
  for(int _ = 0, v = 0; _ < size; _++) {
    for (int j = ig[v]; j < ig[v + 1]; j++)
      if (!you_in_ostov[jg[j]] && gg[j] < b[jg[j]]) {
        b[jg[j]] = gg[j]; rebra[jg[j]] = v;
      }
    for (int l = 0, min = INT_MAX; l < size; l++)
      if (!you_in_ostov[l] && b[l] < min) {
        min = b[l]; v = l;
      }
    you_in_ostov[v] = true;
  }
}
void PrimaSimpleVSSS::convert_to_str() {
    for (int i = 0; i < size; i++)
      for (int j = ig[i]; j < ig[i + 1]; j++)
        if (jg[j] == i) gg[j] = 0;
    for(int i = 0; i < size; i++)
      for(int j = ig[i]; j < ig[i+1]; j++)
        if(rebra[i] != jg[j] && rebra[jg[j]] != i) gg[j] = 0;
}
