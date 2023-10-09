#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct to hold student data and a pointer to the next student in the queue.
struct Student {
    char name[50];  // Student's name
    char address[100];  // Student's address
    char curp[20];  // Student's CURP (a unique identity code)
    float average;  // Student's average grade
    struct Student* next;  // Pointer to the next student in the queue
};

// Function: createStudent
// Description: Allocates memory for a new student and initializes its fields.
struct Student* createStudent(char name[], char address[], char curp[], float average) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));  // Allocate memory for a new student
    strcpy(newStudent->name, name);  // Copy name into the new student's name field
    strcpy(newStudent->address, address);  // Copy address into the new student's address field
    strcpy(newStudent->curp, curp);  // Copy CURP into the new student's CURP field
    newStudent->average = average;  // Set the new student's average
    newStudent->next = NULL;  // Initialize the next pointer to NULL
    return newStudent;  // Return the new student
}

// Function: enqueue
// Description: Adds a new student to the end of the queue.
void enqueue(struct Student** front, struct Student** rear, char name[], char address[], char curp[], float average) {
    struct Student* newStudent = createStudent(name, address, curp, average);  // Create a new student
    if (*rear == NULL) {  // If the queue is empty
        *front = *rear = newStudent;  // Set front and rear to the new student
        return;
    }
    (*rear)->next = newStudent;  // Link the new student to the end of the queue
    *rear = newStudent;  // Update rear to point to the new student
}

// Function: dequeue
// Description: Removes a student from the front of the queue.
void dequeue(struct Student** front) {
    if (*front == NULL) {  // If the queue is empty
        printf("Queue is empty\n");  // Print a message
        return;
    }
    struct Student* temp = *front;  // Temporarily store the front student
    *front = (*front)->next;  // Update front to point to the next student
    printf("Dequeued student: %s\n", temp->name);  // Print a message
    free(temp);  // Free the memory of the dequeued student
}

// Function: display
// Description: Displays all students in the queue.
void display(struct Student* front) {
    if (front == NULL) {  // If the queue is empty
        printf("Queue is empty\n");  // Print a message
        return;
    }
    printf("Students in the queue:\n");  // Print a message
    while (front != NULL) {  // While there are students in the queue
        // Print the student's details
        printf("Name: %s, Address: %s, CURP: %s, Average: %.2f\n", front->name, front->address, front->curp, front->average);
        front = front->next;  // Move to the next student
    }
}

// Function: validateInput
// Description: Validates student details according to specified rules.
int validateInput(char name[], char address[], char curp[], float average) {
    // Validate CURP: Ensure no lowercase letters
    for (int i = 0; i < strlen(curp); i++) {
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

    // Additional validations can be added here as per requirements

    return 1;  // Valid input
}

// Function: readAndEnqueue
// Description: Reads student details from the user, validates them, and enqueues the student if valid.
void readAndEnqueue(struct Student** front, struct Student** rear) {
    char name[50], address[100], curp[20];  // Variables to store student details
    float average;  // Variable to store student average

    // Read student details from the user
    printf("Enter student name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;  // Remove the newline character

    printf("Enter address: ");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = 0;  // Remove the newline character

    printf("Enter CURP: ");
    fgets(curp, sizeof(curp), stdin);
    curp[strcspn(curp, "\n")] = 0;  // Remove the newline character

    printf("Enter average: ");
    scanf("%f", &average);
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
void loadStudentsFromFile(struct Student** front, struct Student** rear, const char* filename) {
    FILE* file = fopen(filename, "r");  // Open the file for reading
    if (file == NULL) {  // If the file could not be opened
        printf("Could not open file %s for reading.\n", filename);  // Print a message
        return;
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
        printf("4. Exit\n");
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
                exit(0);  // Exit the program
            default:
                printf("Invalid choice\n");  // Print a message for invalid choice
        }
    }

    return 0;  // End the program
}

