//
// Created by G3 on 4/1/2024.
//

#ifndef LAST_TRY_DATA_STRUCTURS_H
#define LAST_TRY_DATA_STRUCTURS_H

#include <vector>
#include <unordered_map>

using namespace std;

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
    vector<VERTEX*> vertices;
    unordered_map<int, vector<EDGE*>> adj;
};

#endif //LAST_TRY_DATA_STRUCTURS_H
