#include <stdio.h>
#include <string.h>

const int maxTasks = 100;
const int maxLength = 50;

char tasks[maxTasks][maxLength];  // 2D array that stores 100 tasks, each 50 characters long
int status[maxTasks] = {0};       // Array that keeps track of whether each task is done (1) or not (0)
int taskCount = 0;                // Counter to keep track of the number of tasks

void addTask() {
    if (taskCount < maxTasks) {
        printf("Enter a new task: ");
        scanf(" %[^\n]", tasks[taskCount]);  // Store the new task in tasks[taskCount]
        status[taskCount] = 0;               // Initialize the task as incomplete
        taskCount++;                         // Increment the task count
    } else {
        printf("Task list is full!\n");
    }
}

void viewTasks() {
    if (taskCount == 0) {
        printf("No tasks available.\n");
    } else {
        printf("Your To-Do List:\n");
        for (int i = 0; i < taskCount; i++) {  // Print the task number and description
            printf("%d. %s\n", i + 1, tasks[i]);
            if (status[i] == 0) {
                printf("[Incomplete]\n");  // Mark as incomplete if status[i] is 0
            } else {
                printf("[Complete]\n");  // Mark as complete if status[i] is 1
            }
        }
    }
}

void completeTask() {
    if (taskCount == 0) {
        printf("No tasks available to complete.\n");
    } else {
        int taskNumber;  // Variable to store task number entered by user
        printf("Enter the task number to mark as complete: ");
        scanf("%d", &taskNumber);  // Get the task number from the user

        if (taskNumber < 1 || taskNumber > taskCount) {
            printf("Invalid task number.\n");  // Check if the task number is valid
        } else {
            status[taskNumber - 1] = 1;  // Mark the task as complete
            printf("Task %d marked as complete.\n", taskNumber);
        }
    }
}

void deleteTask() {
    if (taskCount == 0) {
        printf("No tasks available to delete.\n");
    } else {
        int taskNumber;
        printf("Enter a task number to delete: ");
        scanf("%d", &taskNumber);  // Get task number from user

        if (taskNumber < 1 || taskNumber > taskCount) {
            printf("Invalid task number.\n");
        } else {
            // Shift tasks and statuses up to fill the gap
            for (int i = taskNumber - 1; i < taskCount - 1; i++) {
                strcpy(tasks[i], tasks[i + 1]);  // Copy the next task into the current position
                status[i] = status[i + 1];       // Copy the next status into the current position
            }

            // Decrement task count
            taskCount--;

            // Resetting the memory
            memset(tasks[taskCount], 0, sizeof(tasks[taskCount]));  // Set all characters in the task string to '\0'
            status[taskCount] = 0;  // Reset the status of the task at the invalid last position in the list to 0 (incomplete)
            printf("Task %d deleted.\n", taskNumber);
        }
    }
}

int main() {
    printf("\nWelcome to your To-Do List App!\n");

    int choice = 0;

    while (choice != 5) {  // Continue looping until user selects option 5
        printf("\nMain Menu:\n");
        printf("Enter 1 to Add a task.\n");
        printf("Enter 2 to View Tasks.\n");
        printf("Enter 3 to Mark a task as complete.\n");
        printf("Enter 4 to Delete a task.\n");
        printf("Enter 5 to Exit the Program.\n");
        printf("Enter your choice: ");

        // Validate input to ensure it's an integer
        if (scanf("%d", &choice) != 1) {
            // If scanf fails (returns 0), it's not a valid integer input
            printf("Invalid input. Please enter a number between 1 and 5.\n");

            // Clear the input buffer
            while (getchar() != '\n');  // Discard invalid input
            choice = 0;                 // Reset choice to avoid incorrect processing
            continue;                   // Go back to the start of the loop
        }

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                completeTask();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                printf("Thank you for choosing the To-Do List App!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
