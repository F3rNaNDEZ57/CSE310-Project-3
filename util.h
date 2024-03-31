#ifndef UTIL_H
#define UTIL_H

#include "data_structures.h"
#include <limits>
#include <iomanip>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <climits>
#include <cstring>
#include <unordered_map>
#include <stack>
#include <cfloat>
#include <functional>
#include <limits>
#include <iomanip>
#include <map>
#include <sstream>

// Function prototypes
void readGraph(const char* filePath, GRAPH& graph, bool directed, int flag);
void dijkstra(GRAPH& graph, int source);
void printPath(GRAPH& graph, int source, int destination);
void printAdjacencyList(GRAPH& graph);
void insertEdge(std::vector<EDGE*>& list, EDGE* edge, int flag);
// Add more function prototypes as needed

#endif // UTIL_H
