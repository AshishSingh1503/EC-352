// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Count leaf nodes
int countLeafNodes(struct Node *root) {
    if (root == NULL)
        return 0;

    // If both children NULL → leaf
    if (root->left == NULL && root->right == NULL)
        return 1;

    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Count leaf nodes
int countLeafNodes(struct Node *root) {
    if (root == NULL)
        return 0;

    // Leaf node
    if (root->left == NULL && root->right == NULL)
        return 1;

    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Function to count nodes
int countNodes(struct Node* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Function to count internal nodes
int countInternal(struct Node* root) {
    if (root == NULL)
        return 0;

    // leaf node
    if (root->left == NULL && root->right == NULL)
        return 0;

    // internal node
    return 1 + countInternal(root->left) + countInternal(root->right);
}

// Function to calculate height of tree
int height(struct Node* root) {
    if (root == NULL)
        return 0;   // empty tree height = 0

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to calculate number of levels
int numberOfLevels(struct Node* root) {
    if (root == NULL)
        return 0;

    int left = numberOfLevels(root->left);
    int right = numberOfLevels(root->right);

    // number of levels = height of tree
    return (left > right ? left : right) + 1;
}



