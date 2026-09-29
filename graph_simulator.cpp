#include "graph_simulator.h"

#include <stdexcept>

// Create n-cycle
Graph generateCycleGraph(int n) {

    if (n < 3) {
        throw std::invalid_argument(
            "A cycle graph must have at least 3 vertices."
        );
    }

    Graph graph(n);

    for (int vertex = 0; vertex < n; vertex++) {

        int nextVertex = (vertex + 1) % n;

        graph.addEdge(vertex, nextVertex);
    }

    return graph;
}


// Generate a complete graph
Graph generateCompleteGraph(int n) {

    if (n < 0) {
        throw std::invalid_argument(
            "Number of vertices can't be negative."
        );
    }

    Graph graph(n);

    for (int u = 0; u < n; u++) {

        for (int v = u + 1; v < n; v++) {

            graph.addEdge(u, v);
        }
    }

    return graph;
}


// Create empty graph
Graph generateEmptyGraph(int n) {

    if (n < 0) {
        throw std::invalid_argument(
            "Number of vertices can't be negative."
        );
    }

    Graph graph(n);

    return graph;
}