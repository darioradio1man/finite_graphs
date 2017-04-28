#ifndef DSU_H
#define DSU_H

#include <cstdio>

class DSU
{
    public:
        int p[1000], theRank[1000];
        DSU(int);
        int findIt(int);
        bool unite(int, int);
};

#endif // DSU_H