#include "util.h"

void readGraph(const char* filePath, GRAPH& graph, bool directed, int flag) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        exit(1);
    }

    int n, m;
    file >> n >> m;
    graph.vertices.resize(n + 1); // Assuming vertices are numbered from 1 to n

    for (int i = 1; i <= n; ++i) {
        graph.vertices[i] = new VERTEX{i, WHITE, std::numeric_limits<double>::max(), -1, -1}; // Initialize vertices
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

void insertEdge(std::vector<EDGE*>& list, EDGE* edge, int flag) {
    if (flag == 1) {
        // Insert at the front for flag = 1
        list.insert(list.begin(), edge);
    } else {
        // Default to inserting at the rear for flag = 2
        list.push_back(edge);
    }
}

void dijkstra(GRAPH& graph, int source) {
    // Initialize all vertices' keys to infinity, except the source
    for (auto& vertex : graph.vertices) {
        if (vertex) { // Check if the vertex pointer is not null
            vertex->key = std::numeric_limits<double>::max();
            vertex->pi = -1; // No predecessor
            vertex->color = WHITE;
        }
    }

    // Set the source vertex
    graph.vertices[source]->key = 0;
    graph.vertices[source]->color = GRAY;

    // Custom comparator for the priority queue (min-heap)
    auto cmp = [](VERTEX* left, VERTEX* right) { return left->key > right->key; };
    std::priority_queue<VERTEX*, std::vector<VERTEX*>, decltype(cmp)> queue(cmp);

    // Add source to the priority queue
    queue.push(graph.vertices[source]);

    while (!queue.empty()) {
        VERTEX* u = queue.top();
        queue.pop();

        // For each vertex v adjacent to u
        for (EDGE* edge : graph.adj[u->index]) {
            VERTEX* v = graph.vertices[edge->v];

            // Relaxation step
            if (v->key > u->key + edge->w) {
                v->key = u->key + edge->w; // Update the distance
                v->pi = u->index; // Update the predecessor
                if (v->color == WHITE) {
                    queue.push(v); // Add to the queue if not already visited
                    v->color = GRAY;
                }
            }
        }

        u->color = BLACK; // Mark as visited
    }
}

void printPath(GRAPH& graph, int source, int destination) {
    if (source < 1 || source >= static_cast<int>(graph.vertices.size()) || destination < 1 || destination >= static_cast<int>(graph.vertices.size())) {
        std::cout << "Invalid source or destination vertex." << std::endl;
        return;
    }
    if (graph.vertices[destination]->pi == -1) {
        std::cout << "There is no path from " << source << " to " << destination << "." << std::endl;
        return;
    }

    std::stack<int> path;
    for (int v = destination; v != -1; v = graph.vertices[v]->pi) {
        path.push(v);
    }

    std::cout << "The shortest path from " << source << " to " << destination << " is:\n";
    std::cout << "[" << source << ":    " << std::setw(4) << std::right << std::fixed << std::setprecision(2) << 0.00 << "]";
    double totalCost = 0.0;
    int prev = source;

    while (!path.empty()) {
        int vertex = path.top(); path.pop();
        if (vertex == source) continue; // Skip the source to prevent duplication
        totalCost += graph.vertices[vertex]->key - (prev != source ? graph.vertices[prev]->key : 0);

        std::ostringstream costStream;
        costStream << std::fixed << std::setprecision(2) << totalCost;
        std::string costStr = costStream.str();

        int spaces = (costStr.length() > 4) ? 3 : 4;

        std::cout << "-->[" << vertex << ":" << std::string(spaces, ' ') << costStr << "]";
        prev = vertex;
    }
    std::cout << "." << std::endl;
}

void printAdjacencyList(GRAPH& graph) {
    for (const auto& vertex : graph.vertices) {
        if (vertex) {
            std::cout << "ADJ[" << vertex->index << "]:";
            for (auto& edge : graph.adj[vertex->index]) {
                std::cout << "-->[" << edge->u << " " << edge->v << ": " << std::fixed << std::setprecision(2) << edge->w << "]";
            }
            std::cout << std::endl;
        }
    }
}
