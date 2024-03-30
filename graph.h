#ifndef GRAPH_H
#define GRAPH_H

#include "data_structures.h"
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <fstream>

class Graph {
public:
    int V; // Number of vertices
    std::vector<std::list<pADJLIST_NODE>> adj; // Adjacency list
    std::vector<pVERTEX> vertices; // Vector of pointers to VERTEX objects

    Graph(int V); // Constructor
    void addEdge(int u, int v, double weight, bool directed); // Add edge to the graph
    void readGraphFromFile(const std::string& filename, bool directed); // Read graph from file
    void dijkstra(int source, bool printPath = false, int destination = -1); // Dijkstra's algorithm
    void printPath(int source, int destination);// Print shortest path from source to destination
    void printAdjacencyList(); // Print adjacency list of the graph

private:
    void initializeSingleSource(int source);
    void relax(pVERTEX u, pVERTEX v, double weight);
};

#endif // GRAPH_H
