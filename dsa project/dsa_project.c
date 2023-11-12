#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100

// Defining the structure for a task
struct Task {
    char description[100];
    int priority;
    char due_date[20];
    int is_done;
};

// Initializing an array to store tasks and a counter for the number of tasks
struct Task tasks[MAX_TASKS];
int taskCount = 0;

// Function to compare tasks for sorting
int compareTasks(const void* a, const void* b) {
    // First, compare by due date
    int dateComparison = strcmp(((struct Task*)a)->due_date, ((struct Task*)b)->due_date);

    // If due dates are the same, compare by priority
    if (dateComparison == 0) {
        return ((struct Task*)a)->priority - ((struct Task*)b)->priority;
    }

    return dateComparison;
}

// Function to add a task to the to-do list
void addTask(char* description, int priority, char* due_date) {
    if (taskCount < MAX_TASKS) {
        // Copying task details into the next available slot in the array
        strcpy(tasks[taskCount].description, description);
        tasks[taskCount].priority = priority;
        strcpy(tasks[taskCount].due_date, due_date);
        tasks[taskCount].is_done = 0; // Initializing the task as not done

        // Sorting tasks after adding a new task
        qsort(tasks, taskCount + 1, sizeof(struct Task), compareTasks);

        taskCount++;
        printf("Awesome! Task added successfully!\n");
    } else {
        printf("Oops! The to-do list is full. Can't add more tasks.\n");
    }
}

// Function to display all tasks in the to-do list
void displayTasks() {
    if (taskCount == 0) {
        printf("Oh no! The to-do list is empty.\n");
        return;
    }

    printf("To-do List:\n");
    for (int i = 0; i < taskCount; i++) {
        printf("Task %d: Description: %s, Priority: %d, Due Date: %s, Status: %s\n",
               i + 1, tasks[i].description, tasks[i].priority, tasks[i].due_date,
               tasks[i].is_done ? "Done" : "Not Done");
    }
}

// Function to mark a task as done
void markTaskAsDone(int taskIndex) {
    if (taskIndex >= 0 && taskIndex < taskCount) {
        tasks[taskIndex].is_done = 1;
        printf("Great job! Task marked as done.\n");
    } else {
        printf("Uh-oh! Invalid task index. Task not found.\n");
    }
}

// Function to delete a task
void deleteTask(int taskIndex) {
    if (taskIndex >= 0 && taskIndex < taskCount) {
        // Shifting tasks to fill the gap left by the deleted task
        for (int i = taskIndex; i < taskCount - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        taskCount--;
        printf("Task deleted successfully.\n");
    } else {
        printf("Oops! Invalid task index. Task not found.\n");
    }
}

// Main function to run the task planner
int main() {
    int choice;
    char description[100];
    int priority;
    char due_date[20];
    int taskIndex;

    do {
        printf("\nTask Planner Menu:\n");
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Mark Task as Done\n");
        printf("4. Delete Task\n");
        printf("5. Exit\n");
        printf("What would you like to do? Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Tell me about the task: ");
                scanf(" %[^\n]s", description);
                printf("How important is it? (1 for high, 2 for medium, 3 for low): ");
                scanf("%d", &priority);
                printf("When is it due? (YYYY-MM-DD): ");
                scanf(" %[^\n]s", due_date);
                addTask(description, priority, due_date);
                break;
            case 2:
                displayTasks();
                break;
            case 3:
                printf("Which task did you complete? Enter the task number: ");
                scanf("%d", &taskIndex);
                markTaskAsDone(taskIndex - 1); // Adjusting for 0-based indexing
                break;
            case 4:
                printf("Which task would you like to remove? Enter the task number: ");
                scanf("%d", &taskIndex);
                deleteTask(taskIndex - 1); // Adjusting for 0-based indexing
                break;
            case 5:
                printf("Exiting Task Planner. Have a great day!\n");
                break;
            default:
                printf("Oops! Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
