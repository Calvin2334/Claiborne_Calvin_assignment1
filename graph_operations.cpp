#include "graph_operations.h"
#include <stdexcept>
#include<functional>
#include<limits>
#include<queue>
#include<utility>

Graph::Graph(int numberOfVertices){
    if (numberOfVertices <0){
        throw std::invalid_argument(
            "Number of vertices cannot be negative"
        );
    }

    adjacencyList.resize(numberOfVertices);
}

int Graph::vertexCount() const{
    return static_cast<int>(adjacencyList.size());
}

void Graph::addEdge(int u, int v) {
    int n = vertexCount();

    if (u <0 || u>= n || v <0 || v>=n){
        throw std::out_of_range("Vertex is outside the graph.");
    }

    adjacencyList[u].push_back(v);
    adjacencyList[v].push_back(u);
}

const std::vector<int>& Graph::neighbors(int vertex) const {

    if (vertex <0 || vertex >= vertexCount()) {
        throw std::out_of_range("Vertex is outside the graph.");
    }

    return adjacencyList[vertex];
}

void componentDFS(
    const Graph& graph,
    int vertex,
    std::vector<bool>& visited,
    std::vector<int>& component
){
    // Labels Current vertex as visited 
    visited[vertex]= true;

    //Adds it to thecurent component
    component.push_back(vertex);

    //Goes to every unvisited neighbor
    for (int neighbor : graph.neighbors(vertex)){
        if(!visited[neighbor]){
            componentDFS(
                graph,
                neighbor,
                visited,
                component
            );
        }
    }

}

std::vector<std::vector<int>> connectedComponents(
    const Graph& graph
) {
    std::vector<std::vector<int>> components;

    std::vector<bool> visited(
        graph.vertexCount(),
        false
    );

    for (int vertex = 0;
         vertex < graph.vertexCount();
         vertex++) {

        if (!visited[vertex]) {
            std::vector<int> component;

            componentDFS(
                graph,
                vertex,
                visited,
                component
            );

            components.push_back(component);
        }
    }

    return components;
}


// This is a separate function, outside connectedComponents().
bool cycleDFS(
    const Graph& graph,
    int vertex,
    int parent,
    std::vector<bool>& visited,
    std::vector<int>& parents,
    std::vector<int>& cycle
) {
    visited[vertex] = true;

    // Record which vertex brought us here.
    parents[vertex] = parent;

    for (int neighbor : graph.neighbors(vertex)) {

        // Ignore the edge that brought us here.
        if (neighbor == parent) {
            continue;
        }

        if (!visited[neighbor]) {
            if (cycleDFS(
                    graph,
                    neighbor,
                    vertex,
                    visited,
                    parents,
                    cycle
                )) {
                return true;
            }
        } else {
            cycle.push_back(neighbor);

            int current = vertex;

            while (current != neighbor) {
                cycle.push_back(current);
                current = parents[current];
            }

            cycle.push_back(neighbor);
            return true;
        }
    }

    return false;
}


std::vector<int> oneCycle(const Graph& graph) {
    std::vector<bool> visited(
        graph.vertexCount(),
        false
    );

    std::vector<int> parents(
        graph.vertexCount(),
        -1
    );

    std::vector<int> cycle;

    for (int vertex = 0;
         vertex < graph.vertexCount();
         vertex++) {

        if (!visited[vertex]) {
            if (cycleDFS(
                    graph,
                    vertex,
                    -1,
                    visited,
                    parents,
                    cycle
                )) {
                return cycle;
            }
        }
    }

    // Empty vector means no cycle was found.
    return cycle;
}


std::map<int, std::vector<int>> shortestPaths(
    const Graph& graph,
    int source
) {
    int numberOfVertices = graph.vertexCount();

    if (source < 0 || source >= numberOfVertices) {
        throw std::out_of_range(
            "Source vertex is outside the graph."
        );
    }

    const int infinity =
        std::numeric_limits<int>::max();

    std::vector<int> distance(
        numberOfVertices,
        infinity
    );

    std::vector<int> parent(
        numberOfVertices,
        -1
    );

    using DistanceVertex = std::pair<int, int>;

    std::priority_queue<
        DistanceVertex,
        std::vector<DistanceVertex>,
        std::greater<DistanceVertex>
    > unvisited;

    distance[source] = 0;
    unvisited.push({0, source});

    while (!unvisited.empty()) {
        int currentDistance = unvisited.top().first;
        int currentVertex = unvisited.top().second;

        unvisited.pop();

        if (currentDistance != distance[currentVertex]) {
            continue;
        }

        for (int neighbor : graph.neighbors(currentVertex)) {
            int newDistance = currentDistance + 1;

            if (newDistance < distance[neighbor]) {
                distance[neighbor] = newDistance;
                parent[neighbor] = currentVertex;

                unvisited.push({
                    newDistance,
                    neighbor
                });
            }
        }
    }

    std::map<int, std::vector<int>> paths;

    for (int vertex = 0;
         vertex < numberOfVertices;
         vertex++) {

        // Skip vertices that cannot be reached from the source.
        if (distance[vertex] == infinity) {
            continue;
        }

        std::vector<int> path;
        int current = vertex;

        while (current != -1) {
            path.push_back(current);

            if (current == source) {
                break;
            }

            current = parent[current];
        }

        paths[vertex] = path;
    }

    return paths;
}