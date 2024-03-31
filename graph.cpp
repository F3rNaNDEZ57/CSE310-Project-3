#include "graph.h"
#include "stack.h"
#include <queue>
#include <vector>
#include <functional>
#include <fstream>
#include <iostream>
#include <iomanip>
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

//void Graph::addEdge(int u, int v, double weight, bool directed) {
//    pADJLIST_NODE newNode = new ADJLIST_NODE;
//    newNode->edge.startVertex = u;
//    newNode->edge.endVertex = v;
//    newNode->edge.weight = weight;
//    adj[u].push_back(newNode); // Add edge from u to v
//
//    if (!directed) {
//        newNode = new ADJLIST_NODE;
//        newNode->edge.startVertex = v;
//        newNode->edge.endVertex = u;
//        newNode->edge.weight = weight;
//        adj[v].push_back(newNode);
//    }
//}

void Graph::addEdge(int u, int v, double weight, bool directed) {
    // Adjust for zero-based indexing if necessary
    u--; v--;

    // Creating new adjacency list node for u -> v
    pADJLIST_NODE newNode = new ADJLIST_NODE;
    newNode->edge.startVertex = u;
    newNode->edge.endVertex = v;
    newNode->edge.weight = weight;
    newNode->next = adj[u].front(); // Assuming front() gives you access to the first element
    adj[u].push_front(newNode); // For std::list, use push_front to add to the list

    if (!directed) {
        // If undirected, add the edge in the opposite direction as well
        pADJLIST_NODE newNodeReverse = new ADJLIST_NODE;
        newNodeReverse->edge.startVertex = v;
        newNodeReverse->edge.endVertex = u;
        newNodeReverse->edge.weight = weight;
        newNodeReverse->next = adj[v].front(); // Similar to above
        adj[v].push_front(newNodeReverse);
    }
}


void Graph::printAdjacencyList() {
    for (size_t i = 0; i < adj.size(); i++) {
        cout << "ADJ[" << (i + 1) << "]:";
        for (const auto& node : adj[i]) {
            cout << "-->[" << node->edge.startVertex << " " << node->edge.endVertex << ": " << fixed << setprecision(2) << node->edge.weight << "]";
        }
        cout << endl;
    }
}

//void Graph::readGraphFromFile(const std::string& filename, bool directed) {
//    std::ifstream file(filename);
//    if (!file) {
//        std::cerr << "Cannot open the file." << std::endl;
//        return;
//    }
//
//    int m; // Number of edges
//    file >> V >> m;
//
//    int u, v;
//    double w;
//    for (int i = 0; i < m; ++i) {
//        file >> u >> v >> w;
//        addEdge(u - 1, v - 1, w, directed); // Assuming vertices are 1-indexed in the file
//    }
//}


void Graph::readGraphFromFile(const std::string& filename, bool directed) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Cannot open the file." << std::endl;
        return;
    }

    int m; // Assuming the first line contains V and m
    file >> V >> m;
    adj.resize(V); // Resize adjacency list to hold all vertices

    int u, v;
    double w;
    for (int i = 0; i < m; ++i) {
        file >> u >> v >> w;
        addEdge(u - 1, v - 1, w, directed);
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

