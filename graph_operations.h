#ifndef GRAPH_OPERATIONS_H
#define GRAPH_OPERATIONS_H

#include <map>
#include <vector>

class Graph{
    private: 
    // Adjacency list of graph 
        std::vector<std::vector<int>> adjacencyList;

    public:
        //Creating a graph containing the number of vertices 
        explicit Graph(int numberOfVertices);

        int vertexCount() const;

        //Adds undirected edges
        void addEdge(int u, int v);

        //Reads neighbors from vertex
        const std::vector<int>& neighbors(int vertex) const;
};

std::vector<std::vector<int>> connectedComponents(const Graph& graph);

std::vector<int> oneCycle(const Graph& graph);

std::map<int, std::vector<int>> shortestPaths(
    const Graph& graph,
    int source
);

#endif