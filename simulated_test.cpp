#include "graph_operations.h"
#include "graph_simulator.h"

#include<chrono>
#include<map>
#include<string>
#include<vector>
#include <iostream>


void testGraph(const std::string& name, Graph& graph) {

    std::cout << "\n==============================\n";
    std::cout << name << "\n";
    std::cout << "Vertices: " << graph.vertexCount() << "\n";
    std::cout << "==============================\n";

    // Start measuring time
    auto start =
        std::chrono::high_resolution_clock::now();

    std::vector<std::vector<int>> components =
        connectedComponents(graph);

    std::vector<int> cycle =
        oneCycle(graph);

    std::map<int, std::vector<int>> paths;

    if (graph.vertexCount() > 0) {
        paths = shortestPaths(graph, 0);
    }

    // Stop measuring time
    auto end =
        std::chrono::high_resolution_clock::now();

    auto runtime =
        std::chrono::duration_cast<std::chrono::microseconds>(
            end - start
        );

    std::cout << "Connected components: "
              << components.size() << "\n";

    std::cout << "Contains cycle: "
              << (cycle.empty() ? "No" : "Yes")
              << "\n";

    std::cout << "Reachable vertices from 0: "
              << paths.size() << "\n";

    std::cout << "Runtime: "
              << runtime.count()
              << " microseconds\n";
}

int main() {
    std::vector<int> sizes = {
        10,
        100,
        500,
        1000
    };

    for (int n : sizes){

        std::cout << "\n\n######## SIZE "
                  << n
                  << " ########\n";

        // Cycle Graph
        Graph cycleGraph =
            generateCycleGraph(n);

        testGraph(
            "Cycle Graph",
            cycleGraph
        );

        // Complete Graph
        Graph completeGraph =
            generateCompleteGraph(n);

        testGraph(
            "Complete Graph",
            completeGraph
        );
      
        // empty Graph
        Graph emptygraph =
            generateEmptyGraph(n);

        testGraph(
            "Empty Graph",
            emptygraph
        );        

    }

    return 0;
}