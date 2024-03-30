#ifndef FINAL_DATA_STRUCTURES_H
#define FINAL_DATA_STRUCTURES_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// Define a color enumeration for marking vertices during algorithms.
enum COLOR { WHITE, GRAY, BLACK };

// Structure for a vertex in the graph.
typedef struct TAG_VERTEX {
    int index; // Unique identifier for the vertex.
    COLOR color; // Used for marking during algorithms.
    double key; // Key value used in min-heap, representing the shortest distance from source.
    int pi; // Predecessor index in the shortest path.
    int heapPosition; // Position of the vertex in the heap, useful for decrease-key operations.

    // Initialize vertex with maximum possible key value.
    TAG_VERTEX() : index(-1), color(WHITE), key(std::numeric_limits<double>::max()), pi(-1), heapPosition(-1) {}
} VERTEX, *pVERTEX;


// Structure for an edge in the graph.
typedef struct TAG_EDGE {
    int startVertex; // Index of the start vertex.
    int endVertex; // Index of the end vertex.
    double weight; // Weight of the edge.

    TAG_EDGE() : startVertex(-1), endVertex(-1), weight(0.0) {}
} EDGE, *pEDGE;


// Structure for an adjacency list node.
typedef struct TAG_ADJLIST_NODE {
    EDGE edge; // Edge information.
    TAG_ADJLIST_NODE* next; // Next node in the adjacency list.

    TAG_ADJLIST_NODE() : next(nullptr) {}
} ADJLIST_NODE, *pADJLIST_NODE;


// Min-Heap structure for managing the priority queue.
struct TAG_VERTEX;
typedef TAG_VERTEX* pVERTEX;

struct TAG_HEAP {
    int capacity; // Maximum capacity of the heap.
    int size;     // Current size of the heap.
    pVERTEX* vertices; // Dynamic array of pointers to vertices.

    // Constructor to initialize the HEAP with a given capacity.
    TAG_HEAP(int cap) : capacity(cap), size(0) {
        vertices = new pVERTEX[capacity](); // Allocate and initialize to nullptrs.
    }

    // Destructor to clean up the dynamic array.
    ~TAG_HEAP() {
        delete[] vertices;
    }
};

typedef TAG_HEAP* pHEAP;


#endif //FINAL_DATA_STRUCTURES_H
