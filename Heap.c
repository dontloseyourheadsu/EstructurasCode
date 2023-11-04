#include <stdio.h>  // Including standard input-output library
#include <stdlib.h> // Including standard library for functions like exit()

#define MAXSIZE 100 // Defining a constant for the maximum size of the heap

// Global array to represent the heap
int treeNodes[MAXSIZE];
// Variable to keep track of the last position in the heap
int last;

// Function declarations
void insert(int item);
void reHeapUp(int index);
int removeTop();
void reHeapDown(int i);
void showHeap();

int main() {
    last = 0; // Initializing last to 0, meaning the heap is currently empty

    // Initializing all positions in the heap to a default value of -1
    for (int i = 0; i < MAXSIZE; i++) {
        treeNodes[i] = -1;
    }

    // Infinite loop to provide a console-based menu for heap operations
    int choice, value;
    while (1) {
        printf("\nMenu:\n1. Insert\n2. Remove Top\n3. Show Heap\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); // Taking user input for choice

        // Switch-case to perform operations based on user choice
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value); // Taking value to insert from the user
                insert(value);
                break;
            case 2:
                printf("Removed value: %d\n", removeTop()); // Removing and printing the top value of the heap
                break;
            case 3:
                showHeap(); // Displaying the current state of the heap
                break;
            case 4:
                exit(0); // Exiting the program
            default:
                printf("Invalid choice\n"); // Informing user of an invalid choice
        }
    }
}

void insert(int item) {
    if (last == MAXSIZE) {
        printf("Heap is full!\n");
        return; // Exiting if the heap is full
    }
    last++; // Increasing the last position
    treeNodes[last - 1] = item; // Inserting the item at the new last position
    reHeapUp(last - 1); // Adjusting the heap property after insertion
}

void reHeapUp(int index) {
    if (index == 0) return; // If the index is the root, return

    // Computing the parent's index
    int parentIndex = (index - 1) / 2;

    // If the parent's value is less than the current value, they are swapped
    if (treeNodes[parentIndex] < treeNodes[index]) {
        int temp = treeNodes[parentIndex];
        treeNodes[parentIndex] = treeNodes[index];
        treeNodes[index] = temp;
        // Recursively adjust the parent's position
        reHeapUp(parentIndex);
    }
}

int removeTop() {
    if (last == 0) {
        printf("Heap is empty!\n");
        return -1; // Returning -1 if the heap is empty
    }
    int topValue = treeNodes[0]; // Storing the top value
    treeNodes[0] = treeNodes[last - 1]; // Replacing the root with the last element
    last--; // Decreasing the size of the heap
    reHeapDown(0); // Adjusting the heap property after removal
    return topValue; // Returning the removed top value
}

void reHeapDown(int i) {
    // Computing the left and right child indices
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;
    int largest = i; // Assuming the largest value is at the current index

    // If left child exists and its value is greater, update largest
    if (leftChild < last && treeNodes[leftChild] > treeNodes[largest]) {
        largest = leftChild;
    }

    // If right child exists and its value is greater, update largest
    if (rightChild < last && treeNodes[rightChild] > treeNodes[largest]) {
        largest = rightChild;
    }

    // If the largest value is not at the current index, swap and recursively adjust
    if (largest != i) {
        int temp = treeNodes[i];
        treeNodes[i] = treeNodes[largest];
        treeNodes[largest] = temp;
        reHeapDown(largest);
    }
}

void showHeap() {
    // Loop to print all the values in the heap
    for (int i = 0; i < last; i++) {
        printf("%d ", treeNodes[i]);
    }
    printf("\n");
}