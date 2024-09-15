/*

Dijkstra's algorithm - greedy algorithm that find the FASTEST path from
vectice A to vectice C in a Weighted Directed Acyclic Graph.

There are 4 steps in this algorithm:
1. Find the "cheapest" node. This is the node you can get to in the least
   amount of time.

2. Update the costs of the neightors of this node.
3. Repeat until you've done this for every node in the graph.
4. Calculate the final path.


Task:

Implement Dijkstra's algorithm to find the fastest path in a DAG.
Implement and use Adjacency matrix with weights.

Graph functions:

Graph strucure:
num of nodes
2d array of edges
2d array of weights

createGraph(number of nodes)
addEdge with a weight
destroyEdge
updateWeight
printGraph - just for debugging

int** dijkstra's algo(Graph g, int A, int B)

input example: [[1, 2], [2, 5], [5, 6]]


Dijstra working process:

While we have nodes to progress

Grab the node that is closest to the start

Update costs for its neighbors

If any of the neighbors' costs were updates,
update the parents too

Mark this node processed


*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "graph.h"


#define N_NODES 7


int minDistance(int dist[], bool visited[], int numberOfNodes)
{
    int min = INT_MAX;
    int minIndex;

    for (int v = 0; v < numberOfNodes; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}


int **dijkstra(Graph *g, int A, int B, int *outputSize)
{
    int numberOfNodes = g->numberOfNodes;
    
    int *dist = (int *)malloc(numberOfNodes * sizeof(int));
    bool *visited = (bool *)malloc(numberOfNodes * sizeof(bool));
    int *prev = (int *)malloc(numberOfNodes * sizeof(int));

    for (int i = 0; i < numberOfNodes; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        prev[i] = -1;
    }
    
    dist[A] = 0;

    for (int count = 0; count < numberOfNodes - 1; count++) {
        int u = minDistance(dist, visited, numberOfNodes);
        visited[u] = true;

        for (int v = 0; v < numberOfNodes; v++) {
            if (!visited[v] && g->edges[u][v] && dist[u] != INT_MAX && dist[u] + g->weights[u][v] < dist[v]) {
                dist[v] = dist[u] + g->weights[u][v];
                prev[v] = u;
            }
        }
    }

    int *path = (int *)malloc(numberOfNodes * sizeof(int));
    int pathLength = 0;

    for (int at = B; at != -1; at = prev[at]) {
        path[pathLength++] = at;
    }

    int **fastestPath = (int **)malloc(pathLength * sizeof(int *));
    for (int i = 0; i < pathLength / 2; i++) {
        int temp = path[i];
        path[i] = path[pathLength - 1 - i];
        path[pathLength - 1 - i] = temp;
    }

    for (int i = 0; i < pathLength - 1; i++) {
        fastestPath[i] = (int *)malloc(3 * sizeof(int));
        fastestPath[i][0] = path[i];
        fastestPath[i][1] = path[i + 1];
        fastestPath[i][2] = g->weights[path[i]][path[i + 1]];
    }

    *outputSize = pathLength;

    free(dist);
    free(prev);
    free(visited);
    free(path);

    return fastestPath;
}


int main()
{
    Graph *g = createGraph(N_NODES);

    addEdge(g, 1, 2, 6); // g - graph, (node1, node2), weight
    addEdge(g, 1, 3, 2);
    addEdge(g, 3, 2, 3);
    addEdge(g, 2, 4, 1);
    addEdge(g, 3, 4, 5);
    addEdge(g, 4, 5, 11);
    addEdge(g, 5, 6, 2);
    addEdge(g, 4, 6, 12);

    int A = 1;
    int B = 6;

    int outputSize = 0;

    int **fastestPath = dijkstra(g, A, B, &outputSize);

    for (int i = 0; i < outputSize - 1; i++) {
        if (i != 0)
            printf(" -> ");
        printf("%d -> %d (%d) ", fastestPath[i][0], fastestPath[i][1], fastestPath[i][2]);
    }
    printf("\n");

    destroyGraph(g);

    return 0;
}
