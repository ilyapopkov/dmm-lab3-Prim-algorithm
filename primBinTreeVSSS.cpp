#include "primBinTreeVSSS.h"

void PrimaBinTreeVSSS::solve()
{
    //вершина u предок для i вершины, т.ч. (i,u) - мин. ребро
    vector<int> key(size, INF), p(size, -1);
    vector<int> gg1(gg.size(), 0);
    set<pair<int, int> > T;//множесто ребер мин. остового дерева
    //положить в нужном порядке вершины

    //Приоритетная очередь вершин графа, список не задействованных вершин.
    set<pair<int, int> > Q;

    key[0] = 0;// расстояние от "корня" дерева до построенного дерева
    Q.insert(make_pair(0, 0));

    while(!Q.empty()) {
        size_t v = Q.begin()->second;
        Q.erase(Q.begin());

        if (p[v] != -1)
            T.insert(make_pair(v, p[v]));

        for (size_t u = ig[v]; u < ig[v + 1]; u++) {
            int k = jg[u];
            if (gg[u] != 0) {
                if (gg[u] < key[k] && k != v)
                {
                    Q.erase(make_pair(key[k], k));
                    p[k] = v;
                    key[k] = gg[u];
                    Q.insert(make_pair(key[k], k));
                }
            }
        }
    }

    for(auto& t : T) {
        size_t i = t.first;
        size_t j = t.second;
        for(int k = ig[i]; k < ig[i + 1]; k++) {
            if(jg[k] == j) gg1[k] = gg[k];
        }
        for(int k = ig[j]; k < ig[j + 1]; k++) {
            if(jg[k] == i) gg1[k] = gg[k];
        }
    }

    gg = gg1;
}
