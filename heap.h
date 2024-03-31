#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h" // Assuming VERTEX might be used

class Heap {
public:
    Heap(int capacity);
    ~Heap();
    void insert(VERTEX* vertex);
    VERTEX* extractMin();
    bool isEmpty() const;
    void decreaseKey(int vertexIndex, double newValue);
private:
    void minHeapify(int index);
    int parent(int index);
    int left(int index);
    int right(int index);
    void swap(VERTEX** a, VERTEX** b);

    VERTEX** elements; // Dynamic array of VERTEX pointers
    int capacity;
    int currentSize;
};

#endif // HEAP_H
