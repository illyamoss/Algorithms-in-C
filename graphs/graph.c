/*

Graph G = (V, E) is a set of vertices V and Edges E, where each Edge is  a connection between vertices.


*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"


typedef struct graph {
    int numberOfNodes;
    bool **edges;
} graph;

graph *createGraph(int numberOfNodes)
{
    graph *g = malloc(sizeof(*g));
    if (g == NULL) {
        return NULL;
    }

    g->numberOfNodes = numberOfNodes;

    g->edges = calloc(sizeof(bool *), g->numberOfNodes);

    if (g->edges == NULL) {
        free(g);
        return NULL;
    }

    for (int i = 0; i < g->numberOfNodes; ++i) {
        g->edges[i] = calloc(sizeof(bool), g->numberOfNodes);

        if (g->edges[i] == NULL) {
            destroyGraph(g);
            return NULL;
        }
    }

    return g;
}


bool hasEdge(graph *g, int fromNode, int toNode)
{
    assert(g != NULL);
    assert(fromNode < g->numberOfNodes);
    assert(toNode < g->numberOfNodes);

    return g->edges[fromNode][toNode];
}


bool addEdge(graph *g, unsigned int fromNode, unsigned int toNode)
{
    assert(g != NULL);
    assert(fromNode < g->numberOfNodes);
    assert(toNode < g->numberOfNodes);

    if (hasEdge(g, fromNode, toNode)) {
        return false;
    }

    g->edges[fromNode][toNode] = true;
    return true;
}


void destroyGraph(graph *g)
{
    if (g->edges == NULL) {
        return;
    }

    for (int i = 0; i < g->numberOfNodes; ++i) {
        if (g->edges[i] != NULL) {
            free(g->edges[i]);
        }
    }

    free(g->edges);
}


void printGraph(graph *g)
{
    printf("Digraph {\n");

    for (int from = 0; from < g->numberOfNodes; ++from) {
        for (int to = 0; to < g->numberOfNodes; ++to) {
            if (g->edges[from][to]) {
                printf("%d -> %d\n", from, to);
            }
        }
    }
    printf("}\n");
}
