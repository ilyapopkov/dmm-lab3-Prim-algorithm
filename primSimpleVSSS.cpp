#include "primSimpleVSSS.h"

#include <vector>
#include <map>
#include <algorithm>

bool find (vector<int> v, int value) {
  for (auto& i : v) {
    if (value == i) return true;
  }
  return false;
}

bool find (vector<pair<int,int>> v, pair<int, int> value) {
  for (auto& i : v) {
    if (value == i)
      return true;
    if (pair<int, int> (value.second, value.first) == i)
      return true;
  }
  return false;
}

struct rebro {
  pair<int, int> f;
  int ves;
  rebro (pair<int, int> f, int ves) : f(f), ves(ves) {}
};

void PrimaSimpleVSSS::solve() {
  vector<int> U;
  vector<pair<int, int>> E;
  vector<pair<int, int>> F;

  U.push_back(0);

  for (int i = 0; i < size; i++) {
    for (int j = ig[i]; j < ig[i + 1]; j++) {
      int jj = jg[j];
      E.push_back (pair<int, int> (i, jj));
    }
  }

  while (U.size () != size) {
    vector<rebro> rebra;
    for (auto& i : U) {
      for (int j = ig[i]; j < ig[i + 1]; j++) {
        int jj = jg[j];
        if (!find (U, jj) && gg[j] != 0) {
          rebra.push_back (rebro(pair<int, int> (i, jj), gg[j]));
        }
      }
    }
    rebro min_rebro = *min_element (
      rebra.begin (),
      rebra.end (),
      [](rebro r, rebro l) { return r.ves < l.ves; }
    );
    F.push_back (pair<int, int> (min_rebro.f));
    int ver = min_rebro.f.second;
    U.push_back (ver);
  }

  vector<pair<int, int>> delE;
  for (auto& e : E) {
    if (!find (F, e)) {
      delE.push_back (e);
    }
  }

  for (int i = 0; i < size; i++) {
    for (int j = ig[i]; j < ig[i + 1]; j++) {
      int jj = jg[j];
      if (find(delE, pair<int,int>(i, jj))) {
        gg[j] = 0;
      }
    }
  }

  return;
}
