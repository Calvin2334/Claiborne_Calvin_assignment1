#include "graph_operations.h"
#include "graph_simulator.h"

#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>


void testGraph(const std::string& name, Graph& graph) {

    std::cout << "\n==============================\n";
    std::cout << name << "\n";
    std::cout << "Vertices: " << graph.vertexCount() << "\n";
    std::cout << "==============================\n";

    // Start measuring CPU time
    std::clock_t start = std::clock();

    std::vector<std::vector<int>> components =
        connectedComponents(graph);

    std::vector<int> cycle =
        oneCycle(graph);

    std::map<int, std::vector<int>> paths;

    if (graph.vertexCount() > 0) {
        paths = shortestPaths(graph, 0);
    }

    // Stop measuring CPU time
    std::clock_t end = std::clock();

    double cpuTime =
        1000.0 * (end - start) / CLOCKS_PER_SEC;

    std::cout << "Connected components: "
              << components.size() << "\n";

    std::cout << "Contains cycle: "
              << (cycle.empty() ? "No" : "Yes")
              << "\n";

    std::cout << "Reachable vertices from 0: "
              << paths.size() << "\n";

    std::cout << "CPU time: "
              << cpuTime
              << " milliseconds\n";
}


int main(int argc, char* argv[]) {

    // If graph type and size are provided,
    // run one experiment.
    if (argc == 3) {

        std::string graphType = argv[1];
        int n = std::stoi(argv[2]);

        if (graphType == "cycle") {

            Graph graph = generateCycleGraph(n);
            testGraph("Cycle Graph", graph);

        } else if (graphType == "complete") {

            Graph graph = generateCompleteGraph(n);
            testGraph("Complete Graph", graph);

        } else if (graphType == "empty") {

            Graph graph = generateEmptyGraph(n);
            testGraph("Empty Graph", graph);

        } else {

            std::cout << "Unknown graph type.\n";
            return 1;
        }

        return 0;
    }


    // Otherwise run all experiments.
    std::vector<int> sizes = {
        10,
        100,
        500,
        1000
    };

    for (int n : sizes) {

        std::cout << "\n\n######## SIZE "
                  << n
                  << " ########\n";

        Graph cycleGraph =
            generateCycleGraph(n);

        testGraph(
            "Cycle Graph",
            cycleGraph
        );


        Graph completeGraph =
            generateCompleteGraph(n);

        testGraph(
            "Complete Graph",
            completeGraph
        );


        Graph emptyGraph =
            generateEmptyGraph(n);

        testGraph(
            "Empty Graph",
            emptyGraph
        );
    }

    return 0;
}