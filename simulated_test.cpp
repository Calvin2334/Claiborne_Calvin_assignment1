#include "graph_operations.h"
#include "graph_simulator.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

// Tests one generated graph
void testGraph(const std::string& name, Graph& graph) {

    std::cout << "\n==============================\n";
    std::cout << name << "\n";
    std::cout << "Vertices: " << graph.vertexCount() << "\n";
    std::cout << "==============================\n";

    // Test connected components
    std::vector<std::vector<int>> components =
        connectedComponents(graph);

    std::cout << "Connected components: "
              << components.size() << "\n";

    // Test cycle detection
    std::vector<int> cycle = oneCycle(graph);

    if (cycle.empty()) {
        std::cout << "Contains cycle: No\n";
    } else {
        std::cout << "Contains cycle: Yes\n";
    }

    // Test shortest paths from vertex 0
    if (graph.vertexCount() > 0) {

        std::map<int, std::vector<int>> paths =
            shortestPaths(graph, 0);

        std::cout << "Reachable vertices from 0: "
                  << paths.size() << "\n";
    }
}

int main() {

    // Test a cycle graph
    Graph cycleGraph = generateCycleGraph(10);

    testGraph(
        "Cycle Graph (n = 10)",
        cycleGraph
    );

    // Test a complete graph
    Graph completeGraph = generateCompleteGraph(10);

    testGraph(
        "Complete Graph (n = 10)",
        completeGraph
    );

    // Test an empty graph
    Graph emptyGraph = generateEmptyGraph(10);

    testGraph(
        "Empty Graph (n = 10)",
        emptyGraph
    );

    return 0;
}