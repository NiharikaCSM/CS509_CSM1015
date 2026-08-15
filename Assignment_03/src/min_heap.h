#ifndef MIN_HEAP_H
#define MIN_HEAP_H

typedef struct {
    int key;    
    int vertex; 
} HeapEntry;

typedef struct {
    HeapEntry *entries;
    int size;
    int capacity;
} MinHeap;

MinHeap heapCreate(int capacity);
void heapPush(MinHeap *heap, int key, int vertex);
/* Returns 1 and fills *outEntry if the heap was non-empty, 0 otherwise. */
int heapPop(MinHeap *heap, HeapEntry *outEntry);
int heapEmpty(const MinHeap *heap);
void heapFree(MinHeap *heap);

#endif