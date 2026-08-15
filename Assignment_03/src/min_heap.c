#include "min_heap.h"
#include <stdlib.h>

MinHeap heapCreate(int capacity) {
    MinHeap heap;
    heap.entries = malloc(sizeof(HeapEntry) * capacity);
    heap.size = 0;
    heap.capacity = capacity;
    return heap;
}

static void swapEntries(HeapEntry *a, HeapEntry *b) {
    HeapEntry tmp = *a;
    *a = *b;
    *b = tmp;
}

static void siftUp(MinHeap *heap, int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->entries[parent].key <= heap->entries[i].key) break;
        swapEntries(&heap->entries[parent], &heap->entries[i]);
        i = parent;
    }
}

static void siftDown(MinHeap *heap, int i) {
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < heap->size && heap->entries[left].key < heap->entries[smallest].key)
            smallest = left;
        if (right < heap->size && heap->entries[right].key < heap->entries[smallest].key)
            smallest = right;
        if (smallest == i) break;
        swapEntries(&heap->entries[i], &heap->entries[smallest]);
        i = smallest;
    }
}

void heapPush(MinHeap *heap, int key, int vertex) {
    heap->entries[heap->size].key = key;
    heap->entries[heap->size].vertex = vertex;
    siftUp(heap, heap->size);
    heap->size++;
}

int heapPop(MinHeap *heap, HeapEntry *outEntry) {
    if (heap->size == 0) return 0;
    *outEntry = heap->entries[0];
    heap->size--;
    heap->entries[0] = heap->entries[heap->size];
    siftDown(heap, 0);
    return 1;
}

int heapEmpty(const MinHeap *heap) {
    return heap->size == 0;
}

void heapFree(MinHeap *heap) {
    free(heap->entries);
    heap->entries = NULL;
}