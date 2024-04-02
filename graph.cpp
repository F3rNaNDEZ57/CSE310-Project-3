//
// Created by G3 on 4/1/2024.
//

#include "graph.h"
#include <queue>
#include <limits>

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

