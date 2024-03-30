#include "heap.h"
#include <algorithm> // For std::swap
#include <limits>    // For std::numeric_limits

// Initialize a new heap with given capacity
pHEAP initializeHeap(int capacity) {
    return new TAG_HEAP(capacity); // Correct constructor call
}

// Insert a vertex into the heap
void insertHeap(pHEAP heap, pVERTEX vertex) {
    if (heap->size >= heap->capacity) {
        // Heap is full
        return;
    }
    // Place the vertex at the end of the heap and float it up
    heap->size++;
    int i = heap->size - 1;
    heap->vertices[i] = vertex;
    while (i != 0 && heap->vertices[(i - 1) / 2]->key > heap->vertices[i]->key) {
        std::swap(heap->vertices[i], heap->vertices[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Decrease the key value of a vertex in the heap
void decreaseKey(pHEAP heap, int index, double newKey) {
    if (index < heap->size && newKey < heap->vertices[index]->key) {
        heap->vertices[index]->key = newKey;
        while (index != 0 && heap->vertices[(index - 1) / 2]->key > heap->vertices[index]->key) {
            std::swap(heap->vertices[index], heap->vertices[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }
}

// Extract the vertex with the minimum key value
pVERTEX extractMin(pHEAP heap) {
    if (heap->size <= 0) return nullptr;
    if (heap->size == 1) {
        heap->size--;
        return heap->vertices[0];
    }
    pVERTEX root = heap->vertices[0];
    heap->vertices[0] = heap->vertices[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return root;
}

// Maintains the min-heap property
void minHeapify(pHEAP heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->vertices[left]->key < heap->vertices[smallest]->key)
        smallest = left;
    if (right < heap->size && heap->vertices[right]->key < heap->vertices[smallest]->key)
        smallest = right;

    if (smallest != i) {
        std::swap(heap->vertices[i], heap->vertices[smallest]);
        minHeapify(heap, smallest);
    }
}

// Build a min-heap from an unsorted array
void buildMinHeap(pHEAP heap) {
    for (int i = heap->size / 2 - 1; i >= 0; i--) {
        minHeapify(heap, i);
    }
}
//
// Created by G3 on 3/30/2024.
//

#include "heap.h"
