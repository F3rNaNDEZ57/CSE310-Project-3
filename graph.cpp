#include "graph.h"
#include "stack.h"
#include <queue>
#include <vector>
#include <functional>
#include <fstream>
#include <iostream>
#include <limits>

Graph::Graph(int V) : V(V) {
    adj.resize(V);
    // Allocate and initialize vertices
    for (int i = 0; i < V; ++i) {
        pVERTEX newVertex = new VERTEX; // Assuming VERTEX has a suitable constructor
        newVertex->index = i;
        vertices.push_back(newVertex);
    }
}

void Graph::addEdge(int u, int v, double weight, bool directed) {
    pADJLIST_NODE newNode = new ADJLIST_NODE;
    newNode->edge.startVertex = u;
    newNode->edge.endVertex = v;
    newNode->edge.weight = weight;
    adj[u].push_back(newNode); // Add edge from u to v

    if (!directed) {
        newNode = new ADJLIST_NODE;
        newNode->edge.startVertex = v;
        newNode->edge.endVertex = u;
        newNode->edge.weight = weight;
        adj[v].push_back(newNode);
    }
}

void Graph::printAdjacencyList() {
    for (int i = 0; i < V; ++i) {
        std::cout << "Adjacency list of vertex " << i+1 << ": ";
        for (auto node = adj[i].begin(); node != adj[i].end(); ++node) {
            std::cout << "-> (" << (*node)->edge.endVertex+1 << ", " << (*node)->edge.weight << ") ";
        }
        std::cout << std::endl;
    }
}

void Graph::readGraphFromFile(const std::string& filename, bool directed) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Cannot open the file." << std::endl;
        return;
    }

    int m; // Number of edges
    file >> V >> m;

    int u, v;
    double w;
    for (int i = 0; i < m; ++i) {
        file >> u >> v >> w;
        addEdge(u - 1, v - 1, w, directed); // Assuming vertices are 1-indexed in the file
    }
}

void Graph::initializeSingleSource(int source) {
    for (auto& list : adj) {
        for (auto& node : list) {
            node->edge.weight = std::numeric_limits<double>::max();
        }
    }
    adj[source].front()->edge.weight = 0;
}

void Graph::relax(pVERTEX u, pVERTEX v, double weight) {
    if (v->key > u->key + weight) {
        v->key = u->key + weight;
        v->pi = u->index;
    }
}

void Graph::dijkstra(int source, bool shouldPrintPath, int destination) {
    // Assume vertices are stored in a member vector<pVERTEX> vertices; initialized elsewhere
    for (int i = 0; i < V; ++i) {
        vertices[i]->key = std::numeric_limits<double>::max();
        vertices[i]->pi = -1;
    }
    vertices[source]->key = 0;

    auto comp = [](pVERTEX a, pVERTEX b) { return a->key > b->key; };
    std::priority_queue<pVERTEX, std::vector<pVERTEX>, decltype(comp)> minHeap(comp);

    minHeap.push(vertices[source]);

    while (!minHeap.empty()) {
        pVERTEX u = minHeap.top();
        minHeap.pop();

        for (auto& node : adj[u->index]) {
            pVERTEX v = vertices[node->edge.endVertex]; // Get vertex pointed by the adjacency list node
            if (v->key > u->key + node->edge.weight) {
                v->key = u->key + node->edge.weight;
                v->pi = u->index;
                // Since std::priority_queue does not support decrease-key operation, we push the updated vertex again.
                // This is not efficient and ideally, a custom priority queue supporting decrease-key should be used.
                minHeap.push(v);
            }
        }
    }

    if (shouldPrintPath && destination >= 0) {
        printPath(source, destination);
    }
}

void Graph::printPath(int source, int destination) {
    if (vertices[destination]->pi == -1) {
        std::cout << "No path exists from " << source << " to " << destination << std::endl;
        return;
    }

    Stack path;
    for (int at = destination; at != -1; at = vertices[at]->pi) {
        path.push(at);
    }

    std::cout << "The shortest path from " << source << " to " << destination << " is:" << std::endl;
    while (!path.isEmpty()) {
        int vertexIndex = path.pop();
        std::cout << vertexIndex+1;
        if (!path.isEmpty()) std::cout << " -> ";
    }
    std::cout << std::endl;
}

