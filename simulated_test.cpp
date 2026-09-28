#include "graph_operations.h"
#include <iostream>

int main() {
    Graph graph(6);

    // First component: 0, 1, 2
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);

    // Second component: 3, 4
    graph.addEdge(3, 4);

    // Vertex 5 is the third component.

    std::vector<std::vector<int>> components =
        connectedComponents(graph);

    std::cout << "Number of components: "
              << components.size() << "\n";

    for (int i = 0;
         i < static_cast<int>(components.size());
         i++) {

        std::cout << "Component " << i + 1 << ":";

        for (int vertex : components[i]) {
            std::cout << " " << vertex;
        }

        std::cout << "\n";
    }

    // The component loop ends before the cycle test begins.
    std::cout << "\nCycle test:\n";

    Graph cycleGraph(4);

    cycleGraph.addEdge(0, 1);
    cycleGraph.addEdge(1, 2);
    cycleGraph.addEdge(2, 3);
    cycleGraph.addEdge(3, 0);

    std::vector<int> cycle = oneCycle(cycleGraph);

    if (cycle.empty()) {
        std::cout << "No cycle found.\n";
    } else {
        std::cout << "Cycle found:";

        for (int vertex : cycle) {
            std::cout << " " << vertex;
        }

        std::cout << "\n";
    }
std::cout << "\nShortest-path test from source 0:\n";

Graph pathGraph(6);

pathGraph.addEdge(0,1);
pathGraph.addEdge(0,2);
pathGraph.addEdge(1,3);
pathGraph.addEdge(2,4);
pathGraph.addEdge(3,4);

// Cant reach vertex 5 from 0

std::map<int, std::vector<int>> paths =
    shortestPaths(pathGraph,0);

for (const auto& entry : paths) {
    int vertex = entry.first;
    const std::vector<int>& path = entry.second;

    std::cout << "Path from "<< vertex
              << " back to 0:";

    for (int pathVertex : path) {
        std::cout << " " << pathVertex;
    }

    std::cout << "\n";
}

    return 0;
}