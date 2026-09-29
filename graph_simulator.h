#ifndef GRAPH_SIMULATOR_H
#define GRAPH_SIMULATOR_H

#include "graph_operations.h"

// Creates a cycle graph
Graph generateCycleGraph(int n);

// Creates a complete graph where every pair is connected
Graph generateCompleteGraph(int n);

// Creates an empty graph
Graph generateEmptyGraph(int n);

#endif