// static binary tree implementation
#include <stdio.h>

struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

void preorder(struct TreeNode *root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

int main() {
    // Statically allocated nodes
    struct TreeNode n1, n2, n3, n4, n5;

    n1.data = 1;
    n2.data = 2;
    n3.data = 3;
    n4.data = 4;
    n5.data = 5;

    // Manually link them as a tree:
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    n1.left  = &n2;
    n1.right = &n3;
    n2.left  = &n4;
    n2.right = &n5;
    n3.left  = NULL;
    n3.right = NULL;
    n4.left  = n4.right = NULL;
    n5.left  = n5.right = NULL;

    struct TreeNode *root = &n1;

    printf("Preorder traversal of static binary tree:\n");
    preorder(root);
    printf("\n");

    return 0;
}
