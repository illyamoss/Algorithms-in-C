#include "graph.h"


int main(void)
{
    graph *g1 = createGraph(5);

    addEdge(g1, 1, 4);
    addEdge(g1, 3, 4);
    addEdge(g1, 1, 3);

    printGraph(g1);

    destroyGraph(g1);

    return 0;
}
