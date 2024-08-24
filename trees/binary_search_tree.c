#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;


Node* createNode(int data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation fault");
        exit(1);
    }

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}


Node* insertRecursively(Node* root, int data)
{
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertRecursively(root->left, data);
    } else if (data > root->data) {
        root->right = insertRecursively(root->right, data);
    }

    return root;
}


void insertIteratively(Node** root, int data) {
    Node* newNode = createNode(data);
    if (*root == NULL) {  // Check if the tree is empty
        *root = newNode;  // Update the original root pointer
        return;
    }

    Node* temp = *root;
    Node* parent = NULL;

    while (temp != NULL) {
        parent = temp;
        if (data < temp->data) {
            temp = temp->left;
        } else if (data > temp->data) {
            temp = temp->right;
        } else {
            // Data already in the tree, no duplicates allowed
            free(newNode);
            return;
        }
    }

    // Insert the new node as a child of the parent
    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}


void inOrderTraversal(Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d\n", root->data);
        inOrderTraversal(root->right);
    }
}


void printTree(Node *root, int level)
{
    if (root == NULL)
            return;
    for (int i = 0; i < level; i++)
            printf(i == level - 1 ? "|-" : "  ");
    printf("%d\n", root->data);
    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}


void freeTree(Node* root)
{
    if (root == NULL)
        return;
    
    freeTree(root->left);
    freeTree(root->right);

    free(root);
}


int main(void)
{
    Node* root = createNode(7);
     
    srand(time(NULL));

    int a = 0;
    while (a <= 55) {

        /* 
        RANDOM - is a part of a standard C library.
        In order to use it you have to include <stdlib.io>

        You might also incluse <time.h> in order to seed the random number generator
        with the current time.



        Functions:

        Key Functions for Random Number Generation
            srand()

              Purpose: Seeds the random number generator to produce different sequences of random numbers on each run.
              Prototype: void srand(unsigned int seed);
              Usage: Typically called once at the beginning of the program with a seed value, often derived from the current time.
            
            rand()

              Purpose: Generates a pseudo-random integer.
              Prototype: int rand(void);
              Range: Returns an integer between 0 and RAND_MAX (typically 32767).
            
            RAND_MAX

              Purpose: Defines the maximum value returned by rand().
              Usage: Useful for scaling random numbers to a desired range.
        
        */

        int min = 50;
        int max = 100;        

        int random = min + rand() % (max - min + 1);       

        insertIteratively(&root, random);

        ++a;
    }
    // inOrderTraversal(root);

    printTree(root, 0);

    freeTree(root);

    return 0;
}
