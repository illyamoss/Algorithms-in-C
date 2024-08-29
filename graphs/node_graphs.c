#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node {
    int data;
    struct Node **neighbors;
    int neighborCount;
} Node;


Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Allocation fault");
        return NULL;
    }

    newNode->data = data;
    newNode->neighborCount = 0;
    newNode->neighbors = NULL;

    return newNode;
}


void addNeighbor(Node *node, Node *neighbor)
{
    node->neighborCount++;
    node->neighbors = (Node **)realloc(node->neighbors, node->neighborCount * sizeof(Node *));
    node->neighbors[node->neighborCount - 1] = neighbor;
}


void printNode(Node *node)
{
    printf("Node value: %d\n", node->data);
    for (int i = 0; i < node->neighborCount; ++i) {
        printf("Neighbor value: %d\n", node->neighbors[i]->data);
    }
    printf("\n");
}

int main(void)
{
    Node *node1 = createNode(4);

    addNeighbor(node1, createNode(5));
    addNeighbor(node1, createNode(7));

    printNode(node1);

    return 0;
}
