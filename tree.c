#include <stdio.h>
#include <stdlib.h>

// Define a struct to hold the tree node data and pointers to the left and right subtrees.
typedef struct tree_node {
    char info;
    struct tree_node* left;
    struct tree_node* right;
} TreeNode;

// Function: addNode
// Description: Adds a new node to the tree.
TreeNode* addNode(TreeNode* root, char info) {
    // If the tree is empty, create a new node and return it.
    if (root == NULL) {
        root = (TreeNode*)malloc(sizeof(TreeNode)); // Allocate memory for a new node
        root->info = info; // Set the node's info
        root->left = root->right = NULL; // Initialize the left and right subtrees to NULL
    } else if (info < root->info) { // If the info is less than the node's info, add it to the left subtree.
        root->left = addNode(root->left, info); // Recursively add the node to the left subtree.
    } else { // If the info is greater than or equal to the node's info, add it to the right subtree.
        root->right = addNode(root->right, info); // Recursively add the node to the right subtree.
    }
    return root;
}

// Function: inorder
// Description: Prints the tree in inorder.
void inorder(TreeNode* root) {
    if (root != NULL) { // If the tree is not empty
        inorder(root->left); // Recursively print the left subtree
        printf("%c ", root->info); // Print the node's info
        inorder(root->right); // Recursively print the right subtree
    }
}

// Function: preorder
// Description: Prints the tree in preorder.
void preorder(TreeNode* root) {
    // If the tree is not empty
    if (root != NULL) {
        printf("%c ", root->info); // Print the node's info
        preorder(root->left); // Recursively print the left subtree
        preorder(root->right); // Recursively print the right subtree
    }
}

// Function: postorder
// Description: Prints the tree in postorder.
void postorder(TreeNode* root) {
    if (root != NULL) { // If the tree is not empty
        postorder(root->left); // Recursively print the left subtree
        postorder(root->right); // Recursively print the right subtree
        printf("%c ", root->info); // Print the node's info
    }
}

// Function: buildTreeFromFile
// Description: Builds a tree from a file.
TreeNode* buildTreeFromFile(char* filename) {
    FILE* file = fopen(filename, "r"); // Open the file for reading
    // If the file cannot be opened, print a message and return NULL.
    if (file == NULL) {
        printf("Cannot open file.\n"); // Print a message
        return NULL; // Return NULL
    }

    TreeNode* root = NULL; // Initialize the root to NULL
    char ch; // Variable to store the character read from the file
    while (fscanf(file, "%c", &ch) != EOF) { // While there are characters to read from the file
        if(ch != '\n' && ch != ' ') { // If the character is not a newline or space
            root = addNode(root, ch); // Add the character to the tree
        }
    }
    fclose(file); // Close the file
    return root; // Return the root
}

// Function: swapTree
// Description: Swaps the left and right subtrees of a tree.
void swapTree(TreeNode* root) {
    if (root == NULL) { // If the tree is empty, return.
        return; // Return
    }

    // Swap the left and right subtrees.
    TreeNode* temp = root->left; // Store the left subtree in a temporary variable.
    root->left = root->right; // Set the left subtree to the right subtree.
    root->right = temp; // Set the right subtree to the temporary variable.

    // Recursively swap the subtrees of left and right.
    swapTree(root->left);
    swapTree(root->right);
}

int main() {
    // Build tree from file
    TreeNode* root = buildTreeFromFile("tree.txt"); // Build the tree from the file
    printf("Original tree:\n");
    printf("Inorder: ");
    inorder(root); // Print the tree in inorder
    printf("\nPreorder: ");
    preorder(root); // Print the tree in preorder
    printf("\nPostorder: ");
    postorder(root); // Print the tree in postorder
    printf("\n");

    // Swap tree
    swapTree(root); // Swap the tree
    printf("\nSwapped tree:\n");
    printf("Inorder: ");
    inorder(root); // Print the tree in inorder
    printf("\nPreorder: ");
    preorder(root); // Print the tree in preorder
    printf("\nPostorder: ");
    postorder(root); // Print the tree in postorder
    printf("\n");

    return 0;
}

// Sample input
// F
// B
// A
// D
// C
// E
// G
// I
// H

// Sample output

// Should output from file default
// Inorder: A B C D E F G H I
// Preorder: F B A D C E G I H
// Postorder: A C E D B H I G F

// Should output from swapped tree
// Inorder: I H G F E D C B A
// Preorder: F G I H B D E C A
// Postorder: H I G E C D A B F