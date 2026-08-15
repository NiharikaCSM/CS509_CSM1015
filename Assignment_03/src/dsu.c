#include "dsu.h"
#include <stdlib.h>

DSU dsuCreate(int n) {
    DSU dsu;
    dsu.size = n;
    dsu.parent = malloc(sizeof(int) * n);
    dsu.rank_ = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) dsu.parent[i] = i; //initially each vertex is its own parent
    return dsu;
}

int dsuFind(DSU *dsu, int x) {
    //finding root of a vertex
    while (dsu->parent[x] != x) {
        dsu->parent[x] = dsu->parent[dsu->parent[x]];
        x = dsu->parent[x];
    }
    return x;
}

int dsuUnion(DSU *dsu, int a, int b) {
    int rootA = dsuFind(dsu, a);
    int rootB = dsuFind(dsu, b);
    //if root is same do nothing, because adding the edge would create a cycle
    if (rootA == rootB) return 0;

    //attach the shorter tree under the taller one's root
    if (dsu->rank_[rootA] < dsu->rank_[rootB]) {
        dsu->parent[rootA] = rootB;
    } else if (dsu->rank_[rootA] > dsu->rank_[rootB]) {
        dsu->parent[rootB] = rootA;
    } else {
        dsu->parent[rootB] = rootA;
        dsu->rank_[rootA]++;
    }
    return 1;
}

void dsuFree(DSU *dsu) {
    free(dsu->parent);
    free(dsu->rank_);
    dsu->parent = NULL;
    dsu->rank_ = NULL;
}