#include "heap.h"
#include <algorithm>
#include <limits>

Heap::Heap(int capacity) {
    this->elements = new VERTEX*[capacity + 1];
    this->capacity = capacity;
    this->currentSize = 0;
}

Heap::~Heap() {
    delete[] elements;
}

void Heap::insert(VERTEX* vertex) {
    // Implementation
}

VERTEX* Heap::extractMin() {
    // Implementation
    return nullptr; // Placeholder
}

bool Heap::isEmpty() const {
    return currentSize == 0;
}

void Heap::decreaseKey(int vertexIndex, double newValue) {
    // Implementation
}

void Heap::minHeapify(int index) {
    // Implementation
}

int Heap::parent(int index) { return index / 2; }
int Heap::left(int index) { return 2 * index; }
int Heap::right(int index) { return 2 * index + 1; }

void Heap::swap(VERTEX** a, VERTEX** b) {
    VERTEX* temp = *a;
    *a = *b;
    *b = temp;
}
