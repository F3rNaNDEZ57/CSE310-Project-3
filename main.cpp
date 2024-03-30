//#include "heap.h"
//#include <iostream>
//
//// Function prototypes (if not already defined)
//void printHeap(const pHEAP heap);
//
//int main() {
//    // Initialize heap
//    int capacity = 10;
//    pHEAP heap = initializeHeap(capacity);
//
//    // Insert vertices with different keys
//    for (int i = 0; i < capacity; ++i) {
//        auto vertex = new VERTEX;
//        vertex->index = i;
//        vertex->key = (i * 7) % capacity; // Arbitrary key value for testing
//        insertHeap(heap, vertex);
//    }
//
//    // Print heap after insertion
//    std::cout << "Heap after insertion:" << std::endl;
//    printHeap(heap);
//
//    // Decrease key of a vertex and reprint the heap
//    decreaseKey(heap, 5, 1); // Example: decrease key of vertex at index 5 to 1
//    std::cout << "Heap after decreasing key of vertex 5:" << std::endl;
//    printHeap(heap);
//
//    // Extract min and reprint the heap until empty
//    while (!heap->size == 0) {
//        pVERTEX minVertex = extractMin(heap);
//        std::cout << "Extracted Vertex " << minVertex->index << " with key " << minVertex->key << std::endl;
//        delete minVertex; // Assuming dynamic allocation
//    }
//
//    delete heap; // Clean up
//    return 0;
//}
//
//void printHeap(const pHEAP heap) {
//    for (int i = 0; i < heap->size; ++i) {
//        std::cout << "Vertex " << heap->vertices[i]->index << " with key " << heap->vertices[i]->key << std::endl;
//    }
//}


//#include "stack.h"
//#include <iostream>
//
//void testStack() {
//    Stack stack;
//
//    std::cout << "Pushing values onto the stack." << std::endl;
//    for (int i = 0; i < 5; ++i) {
//        std::cout << "Pushing: " << i << std::endl;
//        stack.push(i);
//    }
//
//    std::cout << "\nChecking if stack is empty (0 for no, 1 for yes): " << stack.isEmpty() << std::endl;
//
//    std::cout << "\nPopping values from the stack." << std::endl;
//    while (!stack.isEmpty()) {
//        int value = stack.pop();
//        std::cout << "Popped: " << value << std::endl;
//    }
//
//    std::cout << "\nChecking if stack is empty after popping all items (0 for no, 1 for yes): " << stack.isEmpty() << std::endl;
//
//    std::cout << "\nAttempting to pop from an empty stack:" << std::endl;
//    int value = stack.pop(); // This should show an error message.
//    if (value == -1) {
//        std::cout << "Error value returned as expected." << std::endl;
//    }
//}
//
//int main() {
//    testStack();
//    return 0;
//}


//#include "graph.h"
//#include <iostream>
//
//int main() {
//    int V = 5; // Number of vertices
//    Graph g(V);
//
//    // Read the graph from the file
//    g.readGraphFromFile("test_graph.txt", true); // true for directed graph
//
//    // Example: Find shortest path from vertex 1 to vertex 5
//    int source = 0; // Start from vertex 1 in the file, hence 0 in 0-indexed
//    int destination = 4; // To vertex 5 in the file, hence 4 in 0-indexed
//    bool shouldPrintPath = true;
//
//    // Run Dijkstra's algorithm and print the path from source to destination
//    g.dijkstra(source, shouldPrintPath, destination);
//
//    return 0;
//}
//




#include "graph.h"
#include "util.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <InputFile> <GraphType> <Flag>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string graphType = argv[2]; // Not used in this example, but you might need it for handling directed/undirected graphs differently.
    int flag = std::stoi(argv[3]);

    // Assuming Graph's constructor takes the number of vertices, which we don't know yet.
    // Graph initialization needs to happen after reading the file.
    Graph* graph = nullptr;

    // Read the graph from the file
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << inputFile << std::endl;
        return 1;
    }

    int V, E;
    file >> V >> E;
    graph = new Graph(V); // Initialize the graph with the number of vertices

    int u, v;
    double w;
    for (int i = 0; i < E; ++i) {
        file >> u >> v >> w;
        graph->addEdge(u - 1, v - 1, w, graphType == "DirectedGraph"); // Adjust indices if your implementation assumes 0-based indexing
    }
    file.close();

    // Command processing loop
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "Stop") {
            break;
        } else if (cmd == "PrintADJ") {
            graph->printAdjacencyList();
        } else if (cmd == "SinglePair") {
            int source, destination;
            if (iss >> source >> destination) {
                graph->dijkstra(source, true, destination);
            }
        } else if (cmd == "SingleSource") {
            int source;
            if (iss >> source) {
                graph->dijkstra(source);
            }
        } else if (cmd == "PrintLength" || cmd == "PrintPath") {
            // Placeholder: Implement as per your project specification
            std::cerr << "Error: " << cmd << " instruction not implemented." << std::endl;
        } else {
            std::cerr << "Invalid instruction." << std::endl;
        }
    }

    delete graph;
    return 0;
}
