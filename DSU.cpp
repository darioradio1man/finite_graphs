#include "DSU.h"

DSU::DSU(int n)
{
    p[n] = n;
    theRank[n] = 0;
}

int DSU::findIt(int x)
{
    return (x == p[x] ? x : p[x] = findIt(p[x]));
}

bool DSU::unite(int x, int y)
{
    if((x = findIt(x)) == (y = findIt(y)))
        return false;

    if(theRank[x] < theRank[y])
        p[x] = y;
    else p[y] = x;

    if(theRank[x] == theRank[y])
        ++theRank[x];
    return true;
}