#ifndef DSU_H
#define DSU_H

typedef struct {
    int *parent; 
    int *rank_; 
    int size;
} DSU;

DSU dsuCreate(int n);
int dsuFind(DSU *dsu, int x);

int dsuUnion(DSU *dsu, int a, int b);
void dsuFree(DSU *dsu);

#endif 
