#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"


static void allocationFail()
{
    printf("Allocation failed\n");
    exit(EXIT_FAILURE);
}


static void **initArray(Graph *g, unsigned int cols, size_t typeSize)
{
    void **array = (void **)calloc(cols, sizeof(void *));

    for (int row = 0; row < cols; row++) {
        array[row] = (void *)calloc(cols, typeSize); 
    }

    return array;
}


Graph *createGraph(unsigned int numberOfNodes)
{
    Graph *g = (Graph *)malloc(sizeof(Graph));
    if (g == NULL) {
        allocationFail();
    }

    g->edges = (bool **)initArray(g, numberOfNodes, sizeof(bool));
    
    if (g->edges == NULL) {
        destroyGraph(g);
        allocationFail();
    }

    g->weights = (unsigned int **)initArray(g, numberOfNodes, sizeof(unsigned int));

    if (g->weights == NULL) {
        destroyGraph(g);
        allocationFail();
    }

    g->numberOfNodes = numberOfNodes;

    return g;
}


static void destroyArray(void **arr, int n)
{
    if (arr == NULL)
        return;

    for (int i = 0; i < n; i++)
        if (arr[i] != NULL)
            free(arr[i]);
            
    free(arr);
}


void destroyGraph(Graph *g)
{
    destroyArray((void **)g->edges, g->numberOfNodes);
    destroyArray((void **)g->weights, g->numberOfNodes);

    free(g);
}


void addEdge(Graph *g, unsigned int fromNode, unsigned int toNode, unsigned int weight)
{
    g->edges[fromNode][toNode] = true;
    g->weights[fromNode][toNode] = weight;
}


void removeEdge(Graph *g, unsigned int fromNode, unsigned int toNode)
{
    g->edges[fromNode][toNode] = false;
}


void setWeight(Graph *g, unsigned int fromNode, unsigned int toNode, unsigned int weight)
{
    g->weights[fromNode][toNode] = weight;
}


void printGraph(Graph *g)
{
    printf("Graph {\n");

    for (int from = 0; from < g->numberOfNodes; ++from) {
        for (int to = 0; to < g->numberOfNodes; ++to) {
            if (g->edges[from][to]) 
                printf("%d -> %d, %d\n", from, to, g->edges[from][to]);
        }
    }
    printf("}\n");
}
