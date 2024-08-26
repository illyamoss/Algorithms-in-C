/*

Red-black tree is a type of a binary search tree but with additional properties 
that ensure that the tree remains balanced which brings about O(log n) time
complexity for operations like insertion, search, and deletion.

RBT is similar to AVL tree but with less strict rules which brings less rotations.

Red-Black Trees generally require fewer rotations. This is because the balancing
criteria are more relaxed. The properties of RBTs allow for more flexibility in
the structure, reducing the need for rotations to restore balance compared to AVL
trees.

Reb-black tree properties:

- Every node is either red or black.
- The root is always black.
- Every leaf (NIL) is black.
- If a node is red, then both its children are black.
- Every path from a node to its descendant leaves has the same number of black nodes.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum
{
    RED,
    BLACK
} Color;

typedef struct Node {
    int data;
    Color color;
    struct Node *left, *right, *parent;
} Node;

Node *NIL;


void initializeNIL()
{
    NIL = (Node *)malloc(sizeof(Node));
    NIL->color = BLACK;
    NIL->left = NULL;
    NIL->right = NULL;
    NIL->parent = NULL;
}


Node* createNode(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    return node;
}


void rotateLeft(Node **node, Node *x)
{
    Node *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *node = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}


void rotateRight(Node **node, Node* y)
{
    Node *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        *node = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

void fixViolations(Node **node, Node *z)
{
    // Loop until z is the root or z is the child of a red parent
    while (z != *node && z->parent->color == RED) {
        // Z's parent is the left child of z's grandparent
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;  // y is z's uncle

            // case 1a: z's uncle y is RED:
            if (y->color == RED) {
                // Recolor parent and uncle to BLACK, and grandparent to RED.
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                // Move z up to grandparent and repeat the loop.
                z = z->parent->parent;
            } else {
                // Case 1b: z's uncle y is BLACK, and z is the right chlid.
                if (z == z->parent->right) {
                    // Perform a left rotation to transform the case into Case 1c.
                    z = z->parent;
                    rotateLeft(node, z);
                }

                // Case 1c: z's uncle y is BLACK, and z is the left child.
                // Recolor parent to BLACK and grandparent to RED, then perform a right rotation.
                z->parent->color = RED;
                z->parent->parent->color = RED;
                rotateRight(node, z->parent->parent);
            }
        } else {  // Case 2: z's parent is the right child of z's grandparent.
            Node *y = z->parent->parent->left;  // y is z's  uncle.

            // Case 2a: z's uncle is RED.
            if (y->color == RED) {
                // Recolor parent and uncle to BLACK, grandparent to RED.
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                // Move z up to grandparent and repeat the loop.
                z = z->parent->parent;
            } else {
                // case 2b: z's uncle y is BLACK, and z is the left child.
                if (z == z->parent->left) {
                    // Perform a right rotation to transform the case into case 2c.
                    z = z->parent;
                    rotateRight(node, z);
                }
                // Case 2c: z's uncle y is BLACK, and z is the right child.
                // Recolor parent to BLACK and grandparent to RED, then perform a left rotation.
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(node, z->parent->parent);
            }
        }
    }

    (*node)->color = BLACK;
}


Node *insert(Node *node, int data)
{
    if (node == NULL)
        return createNode(data);
    
    if (data < node->data) {
        node->left = insert(node->left, data);
        node->left->parent = node;
    }
    else if (data > node->data) {
        node->right = insert(node->right, data);
        node->right->parent = node;
    }

    fixViolations(&node, node);

    return node;
}


Node* search(Node *node, int data)
{
    if (node == NULL)
        return node;
    
    if (data < node->data) {
        return search(node->left, data);
    } else if (data > node->data) {
        return search(node->right, data);
    }

    return node;
}


Node* min(Node *node)
{
    Node *min = node;
    while (min->left != NULL)
        min = min->left;
    return min;
}


Node* delete(Node *node, int key) {
    Node *target = search(node, key);  // Find the node to delete
    if (target == NULL) {
        return node;  // Node to be deleted not found, return the original tree
    }

    // Handle deletion
    if (target->left == NULL || target->right == NULL) {
        Node *temp = target->left ? target->left : target->right;

        // No child case
        if (temp == NULL) {
            temp = target;
            target = NULL;
        } else {
            // Node with one child
            *target = *temp;
        }
        free(temp);
    } else {
        // Node with two children
        Node *temp = min(target->right);  // Find the minimum node in the right subtree
        target->data = temp->data;  // Replace target's key with the successor's key
        target->right = delete(target->right, temp->data);  // Delete the successor
    }

    // Fix violations in the tree after deletion
    // (This would be part of the Red-Black Tree fixing logic)
    if (target != NULL) {
        fixViolations(&node, target);
    }

    return node;
}


void inOrder(Node *node)
{
    if (node != NULL) {
        inOrder(node->left);
        printf("Node data: %d\n", node->data);
        inOrder(node->right);
    }
}


void freeTree(Node *node)
{
    if (node == NULL)
        return;

    freeTree(node->left);
    freeTree(node->right);

    free(node);
}


int main(void)
{
    initializeNIL();
    Node *root = createNode(50);

    srand(time(NULL));

    int min = 50;
    int max = 500;

    int i = 0;
    while (i < 100) {
         /* 
         
        Rand() return absolutely any number, by using the Modulus operator
        we ensure that we get a number that is not bigger than a certain
        number(max in our case). To implement the min number, we need to add
        min to a produced number from rand() but that is not bigger than 
        (max - min + 1), if we just write % max, then we can get a number
        bigger than min and after addition we will get a number bigger than
        our minimum.

        */ 
        
        int randomNumber = min + (rand() % (max - min + 1));

        root = insert(root, randomNumber);

        ++i;
    }

    inOrder(root);

    Node *element = search(root, 60);
    if (element)
        printf("Searched element %d\n", element->data);
    else
        printf("Element was not found\n");

    delete(root, 60);

    inOrder(root);

    freeTree(root);

    return 0;
}
