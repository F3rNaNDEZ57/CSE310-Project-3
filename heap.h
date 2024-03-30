//
// Created by G3 on 3/30/2024.
//

#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"

// Function prototypes for heap operations
pHEAP initializeHeap(int capacity);
void insertHeap(pHEAP heap, pVERTEX vertex);
void decreaseKey(pHEAP heap, int index, double newKey);
pVERTEX extractMin(pHEAP heap);
void minHeapify(pHEAP heap, int index);
void buildMinHeap(pHEAP heap);


#endif // HEAP_H

