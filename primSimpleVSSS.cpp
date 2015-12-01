#include "primSimpleVSSS.h"

#include <vector>

void PrimaSimpleVSSS::solve () {
  vector<bool> you_in_ostov (size, false);
  you_in_ostov[0] = true;

  for (int i = 0; i < size; i++) {
    for (int j = ig[i]; j < ig[i + 1]; j++) {
      int jj = jg[j];
      if (jj == i) {
        gg[j] = 0;
      }
    }
  }

  int count = 1;
  int v1, v2, minves;
  while (count != size) {
    v1 = 0;
    v2 = 0;
    minves = INT_MAX;

    for (int i = 0; i < size; i++) {
      if (you_in_ostov[i]) {
        for (int j = ig[i]; j < ig[i + 1]; j++) {
          if (!you_in_ostov[jg[j]] && minves > gg[j]) {
            v1 = i;
            v2 = jg[j];
            minves = gg[j];
          }
        }
      }
    }

    you_in_ostov[v2] = true;

    for (int i = 0; i < size; i++) {
      if (you_in_ostov[i]) {
        for (int j = ig[i]; j < ig[i + 1]; j++) {
          int jj = jg[j];
          if (i != v1 && jj == v2) gg[j] = 0;
          if (you_in_ostov[jj] && jj != v1 && i == v2) gg[j] = 0;
        }
      }
    }

    count++;
  }

  return;
}
