#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct to hold student data and a pointer to the next student in the queue.
struct Student {
    char name[50];  // Student's name
    char address[100];  // Student's address
    char curp[20];  // Student's CURP
    float average;  // Student's average grade
    struct Student *next;  // Pointer to the next student in the queue
};

// Function: createStudent
// Description: Allocates memory for a new student and initializes its fields.
struct Student *createStudent(char name[], char address[], char curp[], float average) {
    struct Student *newStudent = (struct Student *) malloc(
            sizeof(struct Student));  // Allocate memory for a new student
    strcpy(newStudent->name, name);  // Copy name into the new student's name field
    strcpy(newStudent->address, address);  // Copy address into the new student's address field
    strcpy(newStudent->curp, curp);  // Copy CURP into the new student's CURP field
    newStudent->average = average;  // Set the new student's average
    newStudent->next = NULL;  // Initialize the next pointer to NULL
    return newStudent;  // Return the new student
}

// Function: enqueue
// Description: Adds a new student to the end of the queue.
void enqueue(struct Student **front, struct Student **rear, char name[], char address[], char curp[], float average) {
    struct Student *newStudent = createStudent(name, address, curp, average);  // Create a new student
    if (*rear == NULL) {  // If the queue is empty
        *front = *rear = newStudent;  // Set front and rear to the new student
        return; // Return because the queue is empty
    }
    (*rear)->next = newStudent;  // Link the new student to the end of the queue
    *rear = newStudent;  // Update rear to point to the new student
}

// Function: dequeue
// Description: Removes a student from the front of the queue.
void dequeue(struct Student **front) {
    if (*front == NULL) {  // If the queue is empty
        printf("Queue is empty\n");  // Print a message
        return;
    }
    struct Student *temp = *front;  // Temporarily store the front student
    *front = (*front)->next;  // Update front to point to the next student
    printf("Dequeued student: %s\n", temp->name);  // Print a message
    free(temp);  // Free the memory of the dequeued student
}

// Function: display
// Description: Displays all students in the queue.
void display(struct Student *front) {
    if (front == NULL) {  // If the queue is empty
        printf("Queue is empty\n");  // Print a message
        return;
    }
    printf("Students in the queue:\n");  // Print a message
    while (front != NULL) {  // While there are students in the queue
        // Print the student's details
        printf("Name: %s, Address: %s, CURP: %s, Average: %.2f\n", front->name, front->address, front->curp,
               front->average);
        front = front->next;  // Move to the next student
    }
}

// Function: validateInput
// Description: Validates student details according to specified rules.
int validateInput(char name[], char address[], char curp[], float average) {
    // Validate CURP: Ensure no lowercase letters
    for (int i = 0; i < strlen(curp); i++) {
        // If the current character is a lowercase letter
        if (curp[i] >= 'a' && curp[i] <= 'z') {
            printf("Invalid CURP: Should not contain lowercase letters.\n");
            return 0;  // Invalid input
        }
    }

    // Validate average: Ensure it's between 0 and 10
    if (average < 0 || average > 10) {
        printf("Invalid average: Should be between 0 and 10.\n");
        return 0;  // Invalid input
    }

    return 1;  // Valid input
}

// Function: readAndEnqueue
// Description: Reads student details from the user, validates them, and enqueues the student if valid.
void readAndEnqueue(struct Student **front, struct Student **rear) {
    char name[50], address[100], curp[20];  // Variables to store student details
    float average;  // Variable to store student average

    // Read student details from the user
    printf("Enter student name: ");
    fgets(name, sizeof(name), stdin); // Read the name
    name[strcspn(name, "\n")] = 0;  // Remove the newline character

    printf("Enter address: ");
    fgets(address, sizeof(address), stdin); // Read the address
    address[strcspn(address, "\n")] = 0;  // Remove the newline character

    printf("Enter CURP: ");
    fgets(curp, sizeof(curp), stdin); // Read the CURP
    curp[strcspn(curp, "\n")] = 0;  // Remove the newline character

    printf("Enter average: ");
    scanf("%f", &average); // Read the average
    getchar();  // Consume the newline character

    // Validate input before enqueue
    if (validateInput(name, address, curp, average)) {
        enqueue(front, rear, name, address, curp, average);  // Enqueue the student
    } else {
        printf("Student not added due to invalid input.\n");  // Print a message
    }
}

// Function: loadStudentsFromFile
// Description: Loads students from a file, validates them, and enqueues them if valid.
void loadStudentsFromFile(struct Student **front, struct Student **rear, const char *filename) {
    FILE *file = fopen(filename, "r");  // Open the file for reading
    if (file == NULL) {  // If the file could not be opened
        printf("Could not open file %s for reading.\n", filename);  // Print a message
        return; // Return because the file could not be opened
    }

    char name[50], address[100], curp[20];  // Variables to store student details
    float average;  // Variable to store student average

    // While there are students to read from the file
    while (fscanf(file, "%49s\n%99s\n%19s\n%f\n", name, address, curp, &average) == 4) {
        // Validate input before enqueue
        if (validateInput(name, address, curp, average)) {
            enqueue(front, rear, name, address, curp, average);  // Enqueue the student
        } else {
            printf("Student %s not added due to invalid input.\n", name);  // Print a message
        }
    }

    fclose(file);  // Close the file
}

// Function: sortedInsert
// Description: Given a sorted linked list and a new node, inserts the node into the correct sorted position.
void sortedInsert(struct Student** head_ref, struct Student* new_node) {
    struct Student* current;
    // Special case for the head end
    if (*head_ref == NULL || (*head_ref)->average < new_node->average) {
        new_node->next = *head_ref;
        *head_ref = new_node;
    } else {
        // Locate the node before the point of insertion
        current = *head_ref;
        while (current->next != NULL && current->next->average >= new_node->average) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

// Function: insertionSort
// Description: Sorts the linked list of students by average grade in descending order using insertion sort.
void insertionSort(struct Student** head_ref) {
    // Initialize sorted linked list
    struct Student* sorted = NULL;
    struct Student* current = *head_ref;
    // Traverse the given linked list and insert every node to sorted
    while (current != NULL) {
        // Store next for next iteration
        struct Student* next = current->next;
        // Insert current in sorted linked list
        sortedInsert(&sorted, current);
        // Update current
        current = next;
    }
    // Update head_ref to point to sorted linked list
    *head_ref = sorted;
}

// Function: main
// Description: The entry point of the program, contains the main loop and logic.
int main() {
    struct Student *front = NULL, *rear = NULL;  // Pointers to the front and rear of the queue
    int choice;  // Variable to store the user's menu choice

    // Load students from file
    loadStudentsFromFile(&front, &rear, "students.txt");

    // Main loop
    while (1) {
        // Display menu and read user's choice
        printf("\nMenu:\n");
        printf("1. Enqueue student\n");
        printf("2. Dequeue student\n");
        printf("3. Display queue\n");
        printf("4. Sort queue by average grade\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume the newline character left by scanf

        // Perform action based on user's choice
        switch (choice) {
            case 1:
                readAndEnqueue(&front, &rear);  // Enqueue a student
                break;
            case 2:
                dequeue(&front);  // Dequeue a student
                break;
            case 3:
                display(front);  // Display the queue
                break;
            case 4:
                insertionSort(&front);  // Sort the queue by average grade
                printf("Queue sorted by average grade.\n");
                break;
            case 5:
                exit(0);  // Exit the program
            default:
                printf("Invalid choice\n");  // Print a message for invalid choice
        }
    }

    return 0;  // End the program
}

// Sample input
// JohnDoe
// 123MainSt
// ABC123456HGF
// 8.5
//
// JaneDoe
// 456ElmSt
// XYZ987654LKP
// 9.2
//
// JimBeam
// 789OakSt
// LMN654321QWE
// 7.4

// Sample output
// Menu:
// 1. Enqueue student
// 2. Dequeue student
// 3. Display queue
// 4. Exit
// Enter your choice: 3
// Students in the queue:
// Name: JohnDoe, Address: 123MainSt, CURP: ABC123456HGF, Average: 8.50
// Name: JaneDoe, Address: 456ElmSt, CURP: XYZ987654LKP, Average: 9.20
// Name: JimBeam, Address: 789OakSt, CURP: LMN654321QWE, Average: 7.40
