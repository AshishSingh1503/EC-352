// dynamic binary tree implementation`
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int value) {
    struct TreeNode *node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (!node) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    node->data = value;
    node->left = node->right = NULL;
    return node;
}

// Simple example: build fixed tree and traverse
void preorder(struct TreeNode *root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void freeTree(struct TreeNode *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    // Build this tree using malloc:
    //        10
    //       /  \
    //      5    20
    //     / \     \
    //    3   7     30

    struct TreeNode *root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(20);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->right = createNode(30);

    printf("Preorder traversal of dynamic binary tree:\n");
    preorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}
