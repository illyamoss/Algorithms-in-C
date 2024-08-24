/*

An AVL tree defined as a self-balancing Binary Search Tree (BST)
where the difference between heights of left and right subtrees
for any node cannot be more than one. It is named after its
inventors Adelson-Velsky and Landis.

The key feature of an AVL tree is that it maintains its balance
by ensuring that the height difference between the left and right
subtrees (also known as the balance factor) of any node is at
most 1. This balance is crutial because it keeps the tree's
height logarithmic in the number of nodes, ensuring efficient
operations like insertion, deletion, and search, which all take
O(log n) time.

Key concepts:

- Height of a node: the number of edges on the longest path from
  that node to a leaf. The height of an empty tree is -1, and a
  leaf node (a node with no children) has a height of 0.

- Balance factor:
  Balance Factor = Height of Left Subtree - Height of Right Subtree
  For an AVL tree, the balance factor of any node must be -1, 0,
  or +1. If the balance factor goes outside this range, the tree
  needs to be rebalanced.

Why Use AVL Trees?

- Efficiency: The self-balancing property ensures that the
  tree remains approximately balanced, so the operations like
  search, insert, and delete are kept efficiently at O(log n).

- Predictable performance: Unlike an unbalanced BST, which can 
  degenerate into a linked list with O(n) operations, an AVL
  tree guarantees that its height is always logarithmic relative
  to the number of nodes.

Why Not to Use AVL Trees?

- Complex implementation: maintaining balance through rotations adds
  complexity to the code.

- Overhead: The balancing operations can slow down
  insertions and deletions.

Use Cases:

- In-Memory Databases: Fast, Balanced Access.
- Caching Systems: efficient updates.
- ETC.

Summary:
AVL trees are a sophisticated data structure that balances the
need for quick access to data (like a BST) with the requirement
to maintain performance through self-balancing mechanisms
(rotations). This ensures that operations remain efficient even
as the tree grows in size.


*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct AVLNode {
    int key;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} Node;


int getHeight(Node* node)
{
    if (node == NULL)
        return 0;
    return node->height;
}


Node* createNode(int key)
{
    Node* node = (Node*)malloc(sizeof(Node));
    
    if (node == NULL) {
        printf("Allocation failed\n");
        exit(1);
    }

    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}


int max(int a, int b)
{
    return (a > b) ? a : b;
}


int getBalanceFactor(Node* node)
{
    if (node == NULL)
        return 0;
    
    return getHeight(node->left) - getHeight(node->right);       
}


Node* leftRotate(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}


Node* rightRotate(Node* x)
{
    Node* y = x->left;
    Node* T2 = y->right;

    y->right = x;
    x->left = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}


Node* balance(Node* node, int key)
{
    if (node == NULL)
        return node;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    int balance = getBalanceFactor(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


Node* insert(Node* node, int key)
{
    if (node == NULL)
        return createNode(key);
    
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    node = balance(node, key);

    return node;
}


Node* min(Node* node)
{
    Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}


Node* delete(Node* node, int key)
{
    if (node == NULL)
        return node;
    
    if (key < node->key) {
        node->left = delete(node->left, key);
    } else if (key > node->key) {
        node->right = delete(node->right, key);
    } else if (key == node->key) {

        // Node with only one child or no child
        if ((node->left == NULL) || (node->right == NULL)) {
            Node *temp = node->left ? node->left : node->right;

            // No child use
            if (temp == NULL) {
                temp = node;
                node = NULL;
            } else
                *node = *temp;

            free(temp);
        } else {
            Node *temp = min(node->right);

            node->key = temp->key;

            node->right = delete(node->right, temp->key);
        }
    }

    node = balance(node, key);

    return node;
}


Node* search(Node* node, int key)
{    
    if (node == NULL)
        return node;

    if (key < node->key) {
        return search(node->left, key);
    } else if (key > node->key) {
        return search(node->right, key);
    }

    return node;
}


Node* searchI(Node* node, int key)
{
    if (node == NULL)
        return node;

    Node *current = node;

    while ((current->left != NULL) || (current->right != NULL)) {
        if (key == current->key)
            return current;

        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        }
    }

    return NULL;
}


void inOrder(Node* root)
{
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
        // printf("%d ", root->key);
    }
}


void freeTree(Node* node)
{
    if (node == NULL)
        return;

    freeTree(node->left);
    freeTree(node->right);

    free(node);
}


int main(void)
{
    Node* root = createNode(50);

    // Inserting nodes
    for (int i = 0; i < 50; ++i)
        root = insert(root, i);

    // Print preorder traversal of the AVL tree
    printf("Inorder traversal of AVL tree: ");
    inOrder(root);
    printf("\n");

    root = delete(root, 456);

    printf("After deletion: \n");

    printf("Inorder traversal of AVL tree: ");
    inOrder(root);
    printf("\n");

    int inputElement = 0;

    printf("What element do you want to find:\n");
    scanf("%d", &inputElement);

    char input;
    char iterative = 'i';
    char recursive = 'r';

    printf("Select your search type (r - recursive, i - iterative):\n");
    scanf(" %c", &input);

    Node* found = NULL;

    if (input == iterative) {
        found = searchI(root, inputElement);
    } else if (input == recursive) {
        found = search(root, inputElement);
    } else {
        printf("Command unrecognized.\n");
        return -1;
    }

    if (found == NULL)
        printf("Such an element does not exist\n");
    else
        printf("Found element: %d\n", found->key);

    freeTree(root);

    return 0;
}
