#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node {
    int data;
    struct tree_node *left;
    struct tree_node *right;
    int height;
} TreeNode;

TreeNode * newNode (int data);
TreeNode * insert (TreeNode *root, int data);
TreeNode * leftRotate (TreeNode *root);
TreeNode * rightRotate (TreeNode *root);
int getHeight (TreeNode *root);
void preorder (TreeNode *root);
void inorder (TreeNode *root);
void postorder (TreeNode *root);
void showTree (TreeNode *root, int level);

int main () {
    TreeNode *root = NULL;
    int data;
    while (scanf("%d", &data) != EOF) {
        root = insert(root, data);
    }
    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    showTree(root, 0);
    return 0;
}

TreeNode * newNode (int data) {
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

TreeNode * insert(TreeNode *root, int data) {
    if (root == NULL) {
        return newNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    } else {
        return root;
    }
    root->height = getHeight(root);
    int balance = getHeight(root->left) - getHeight(root->right);
    if (balance > 1 && data < root->left->data) {
        return rightRotate(root);
    }
    if (balance < -1 && data > root->right->data) {
        return leftRotate(root);
    }
    if (balance > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

TreeNode * leftRotate (TreeNode *root) {
    TreeNode *right = root->right;
    TreeNode *left = right->left;
    right->left = root;
    root->right = left;
    root->height = getHeight(root);
    right->height = getHeight(right);
    return right;
}

TreeNode * rightRotate (TreeNode *root) {
    TreeNode *left = root->left;
    TreeNode *right = left->right;
    left->right = root;
    root->left = right;
    root->height = getHeight(root);
    left->height = getHeight(left);
    return left;
}

int getHeight (TreeNode *root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void preorder (TreeNode *root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder (TreeNode *root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void postorder (TreeNode *root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

void showTree (TreeNode *root, int level) {
    if (root == NULL) {
        return;
    }
    showTree(root->right, level + 1);
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%d\n", root->data);
    showTree(root->left, level + 1);
}