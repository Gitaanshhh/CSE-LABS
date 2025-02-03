/*
2). Write a C program to find Closest Common Ancestor (CCA) in a Binary Tree. 
The CCA of n1 and n2 in T is the shared ancestor of n1 and n2 that is located farthest from the root 
[i.e., closest to n1 and n2].    
For Example: Consider the following BT
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *left;
    struct node *right;
} Node;

Node *createNode(int val) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int height(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + max(height(root->left), height(root->right));
}

int diameter(Node *root, int *height) {
    if (root == NULL) {
        *height = 0;  // Height of an empty tree is 0
        return 0;     // Diameter of an empty tree is 0
    }

    int leftHeight = 0, rightHeight = 0;

    int leftDiameter = diameter(root->left, &leftHeight);
    int rightDiameter = diameter(root->right, &rightHeight);

    *height = max(leftHeight, rightHeight) + 1;

    return max(leftHeight + rightHeight + 1, max(leftDiameter, rightDiameter));
}

void freeTree(Node *root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    // Create the tree manually
    Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(6);
    root->left->right->left = createNode(7);
    root->left->right->right = createNode(8);
    root->right->right->right = createNode(9);
    root->right->right->right->left = createNode(10);
    root->right->right->right->right = createNode(11);
    root->right->right->right->left->left = createNode(12);
    root->right->right->right->left->right = createNode(13);

    int height = 0;
    printf("Diameter of the given binary tree is %d\n", diameter(root, &height));

    freeTree(root);

    return 0;
}
