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
#include <iostream>
#include <cstring> // for strcmp and atoi
#include "graph.h"
#include "util.h"


int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <InputFile> <GraphType> <Flag>\n";
        return 1;
    }

    GRAPH graph;
    bool directed = strcmp(argv[2], "DirectedGraph") == 0;
    int flag = atoi(argv[3]); // Convert the flag argument from string to integer

    if (flag < 1 || flag > 2) {
        cerr << "Usage: " << argv[0] << " <InputFile> <GraphType> <Flag>\n";
        return 1;
    }
    readGraph(argv[1], graph, directed, flag);

    string command;
    int source = -1, destination = -1; // Use these to keep track of the last used source and destination

    bool pathCalculated = false;
    int lastDijkstraSource = -1;

    while (cin >> command) {
        if (command == "Stop") {
            break;
        } else if (command == "PrintADJ") {
            printAdjacencyList(graph);
        } else if (command == "SinglePair") {
            cin >> source >> destination;
            dijkstra(graph, source);
            pathCalculated = true;
            lastDijkstraSource = source;
        } else if (command == "SingleSource") {
            cin >> source;
            dijkstra(graph, source);
            pathCalculated = true;
            lastDijkstraSource = source;
        } else if (command == "PrintPath") {
            cin >> source >> destination;
            if (source != lastDijkstraSource) {
                // If the source isn't the last Dijkstra source, ignore this command
                continue; // Skip the current iteration and wait for the next command
            }
            printPath(graph, source, destination);
        } else if (command == "PrintLength") {
            cin >> source >> destination;
            if (source != lastDijkstraSource) {
                // If the source isn't the last Dijkstra source, ignore this command
                continue; // Skip the current iteration and wait for the next command
            }
            // This requires that dijkstra has already been run for the current source.
            if (graph.vertices[destination]->key != std::numeric_limits<double>::max()) {
                cout << "The length of the shortest path from " << source << " to " << destination << " is:     ";
                cout << fixed << setprecision(2) << graph.vertices[destination]->key << endl;
            } else {
                cout << "There is no path from " << source << " to " << destination << "." << endl;
            }
        } else {
            cerr << "Invalid instruction." << endl;
        }
    }

    // Clean up dynamically allocated memory
    for (auto& vertex : graph.vertices) {
        delete vertex;
    }
    for (auto& pair : graph.adj) {
        for (auto& edge : pair.second) {
            delete edge;
        }
    }

    return 0;
}
