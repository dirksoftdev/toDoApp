#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxTasks = 100;
const int maxLength = 50;

// Function prototypes (declarations)
typedef struct {
    char *description;
    int status;
} Task;

void addTask(Task tasks[], int *taskCount);
void viewTasks(Task tasks[], int taskCount);
void completeTask(Task tasks[], int taskCount);
void deleteTask(Task tasks[], int *taskCount);

int main() {
    Task tasks[maxTasks];
    int taskCount = 0;
    int choice = 0;

    printf("\nWelcome to your To-Do List App!\n");

    while (choice != 5) {
        printf("\nMain Menu:\n");
        printf("1. Add a task\n");
        printf("2. View tasks\n");
        printf("3. Mark a task as complete\n");
        printf("4. Delete a task\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            choice = 0;
            continue;
        }
        getchar();  // Clear newline left in buffer

        switch (choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                viewTasks(tasks, taskCount);
                break;
            case 3:
                completeTask(tasks, taskCount);
                break;
            case 4:
                deleteTask(tasks, &taskCount);
                break;
            case 5:
                printf("Thank you for using the To-Do List App!\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

// Function definitions

void addTask(Task tasks[], int *taskCount) {
    if (*taskCount < maxTasks) {  // Check if the task list is not full
        tasks[*taskCount].description = (char *)malloc(maxLength * sizeof(char));  // Allocate memory for the task description
        if (tasks[*taskCount].description == NULL) {  // Check if memory allocation failed
            printf("Memory allocation failed!\n");  // Print error if memory allocation failed
            return;  // Exit the function
        }

        printf("Enter a new task: ");  // Prompt user to enter a new task
        fgets(tasks[*taskCount].description, maxLength, stdin);  // Get the task description from the user
        tasks[*taskCount].description[strcspn(tasks[*taskCount].description, "\n")] = '\0';  // Remove newline character from input

        tasks[*taskCount].status = 0;  // Mark the new task as incomplete (status = 0)
        (*taskCount)++;  // Increment the task count
    } else {
        printf("Task list is full!\n");  // Print error if the task list is full
    }
}

void viewTasks(Task tasks[], int taskCount) {
    if (taskCount == 0) {
        printf("No tasks available.\n");
    } else {
        printf("Your To-Do List:\n");
        for (int i = 0; i < taskCount; i++) {
            printf("%d. %s\n", i + 1, tasks[i].description);
            printf(tasks[i].status == 0 ? "[Incomplete]\n" : "[Complete]\n");
        }
    }
}

void completeTask(Task tasks[], int taskCount) {
    if (taskCount == 0) {
        printf("No tasks available to complete.\n");
    } else {
        int taskNumber;
        printf("Enter the task number to mark as complete: ");
        scanf("%d", &taskNumber);
        getchar();

        if (taskNumber < 1 || taskNumber > taskCount) {
            printf("Invalid task number.\n");
        } else {
            tasks[taskNumber - 1].status = 1;
            printf("Task %d marked as complete.\n", taskNumber);
        }
    }
}

void deleteTask(Task tasks[], int *taskCount) {
    if (*taskCount == 0) {
        printf("No tasks available to delete.\n");
    } else {
        int taskNumber;
        printf("Enter a task number to delete: ");
        scanf("%d", &taskNumber);
        getchar();

        if (taskNumber < 1 || taskNumber > *taskCount) {
            printf("Invalid task number.\n");
        } else {
            free(tasks[taskNumber - 1].description);

            for (int i = taskNumber - 1; i < *taskCount - 1; i++) {
                tasks[i] = tasks[i + 1];
            }

            (*taskCount)--;
            printf("Task %d deleted.\n", taskNumber);
        }
    }
}
