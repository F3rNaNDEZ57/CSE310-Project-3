#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <vector>
#include <unordered_map>

enum COLOR { WHITE, GRAY, BLACK };

struct VERTEX {
    int index;
    COLOR color;
    double key;
    int pi;
    int position;
};

struct EDGE {
    int index;
    int u, v;
    double w;
    EDGE* next;
};

struct HEAP {
    int capacity;
    int size;
    VERTEX** H;
};

struct GRAPH {
    std::vector<VERTEX*> vertices;
    std::unordered_map<int, std::vector<EDGE*>> adj;
};

#endif // DATA_STRUCTURES_H
