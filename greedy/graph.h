#ifndef GRAPH_ADJ_MATRIX_H_

#define GRAPH_ADJ_MATRIX_H_


typedef struct Graph {
    unsigned int numberOfNodes;
    bool **edges;
    unsigned int **weights;
} Graph;

Graph *createGraph(unsigned int numberOfNodes);
void addEdge(Graph *g, unsigned int fromNode, unsigned int toNode, unsigned int weight);
void removeEdge(Graph *g, unsigned int fromNode, unsigned int toNode);
void setWeight(Graph *g, unsigned int fromNode, unsigned int toNode, unsigned int weight);

void printGraph(Graph *g);
void destroyGraph(Graph *g);

#endif