//
// Created by G3 on 4/1/2024.
//

#ifndef LAST_TRY_UTIL_H
#define LAST_TRY_UTIL_H

#include "data_structures.h"

void readGraph(const char* filePath, GRAPH& graph, bool directed, int flag);
void printPath(GRAPH& graph, int source, int destination);
void printAdjacencyList(GRAPH& graph);
void insertEdge(vector<EDGE*>& list, EDGE* edge, int flag);


#endif //LAST_TRY_UTIL_H
