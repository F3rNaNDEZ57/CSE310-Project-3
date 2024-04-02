//
// Created by G3 on 4/1/2024.
//

#include "util.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <stack>
#include "util.h"
#include <fstream>  // For std::ifstream
#include <iostream> // For std::cerr, std::cout
#include <limits>   // For std::numeric_limits
#include <iomanip>  // For std::setw, std::setprecision, std::fixed, std::right
#include <sstream>  // For std::ostringstream


void readGraph(const char* filePath, GRAPH& graph, bool directed, int flag) {
//    cout << "Flag value: " << flag << endl;
    ifstream file(filePath);
    if (!file) {
        cerr << "Error: Unable to open file " << filePath << endl;
        exit(1);
    }

    int n, m;
    file >> n >> m;
    graph.vertices.resize(n + 1); // Assuming vertices are numbered from 1 to n

    for (int i = 1; i <= n; ++i) {
        graph.vertices[i] = new VERTEX{i, WHITE, numeric_limits<double>::max(), -1, -1}; // Initialize vertices
    }

    int edgeIndex, u, v;
    double w;
    for (int i = 0; i < m; ++i) {
        file >> edgeIndex >> u >> v >> w;
        EDGE* edge = new EDGE{edgeIndex, u, v, w, nullptr};

        // Handle directed graphs
        if (directed) {
            insertEdge(graph.adj[u], edge, flag);
        } else {
            // For undirected graphs, add edge in both directions
            insertEdge(graph.adj[u], new EDGE{edgeIndex, u, v, w, nullptr}, flag);
            insertEdge(graph.adj[v], new EDGE{edgeIndex, v, u, w, nullptr}, flag);
        }
    }
}

void insertEdge(vector<EDGE*>& list, EDGE* edge, int flag) {
    if (flag == 1) {
        // Insert at the front for flag = 1
        list.insert(list.begin(), edge);
    } else {
        // Default to inserting at the rear for flag = 2
        list.push_back(edge);
    }
}

void printPath(GRAPH& graph, int source, int destination) {
    if (source < 1 || source >= static_cast<int>(graph.vertices.size()) || destination < 1 || destination >= static_cast<int>(graph.vertices.size())) {
        cout << "Invalid source or destination vertex." << endl;
        return;
    }
    if (graph.vertices[destination]->pi == -1) {
        cout << "There is no path from " << source << " to " << destination << "." << endl;
        return;
    }

    stack<int> path;
    for (int v = destination; v != -1; v = graph.vertices[v]->pi) {
        path.push(v);
    }

    cout << "The shortest path from " << source << " to " << destination << " is:\n";
    // Include ":    " directly in the string literal for the desired formatting
    cout << "[" << source << ":    " << setw(4) << right << fixed << setprecision(2) << 0.00 << "]";
    double totalCost = 0.0;
    int prev = source;

    while (!path.empty()) {
        int vertex = path.top(); path.pop();
        if (vertex == source) continue; // Skip the source to prevent duplication
        totalCost += graph.vertices[vertex]->key - (prev != source ? graph.vertices[prev]->key : 0);

        // Convert totalCost to a string with fixed precision
        std::ostringstream costStream;
        costStream << fixed << setprecision(2) << totalCost;
        std::string costStr = costStream.str();

        // Determine the number of spaces based on the length of costStr
        int spaces = (costStr.length() > 4) ? 3 : 4; // Adjust the condition based on your requirements

        // Output the formatted path step
        cout << "-->[" << vertex << ":" << std::string(spaces, ' ') << costStr << "]";
        prev = vertex;
    }
    cout << "." << endl;
}


void printAdjacencyList(GRAPH& graph) {
    for (const auto& vertex : graph.vertices) {
        if (vertex) {
            cout << "ADJ[" << vertex->index << "]:";
            for (auto& edge : graph.adj[vertex->index]) {
                cout << "-->[" << edge->u << " " << edge->v << ": " << fixed << setprecision(2) << edge->w << "]";
            }
            cout << endl;
        }
    }
}

