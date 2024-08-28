#ifndef GRAPH_ADJ_MAT_H_
#define GRAPH_ADJ_MAT_H_

#include <stdbool.h>


typedef struct graph graph;

graph *createGraph(int numberOfNodes);
void destroyGraph(graph *g);
void printGraph(graph *g);
bool addEdge(graph *g, unsigned int fromNode, unsigned int toNode);

#endif