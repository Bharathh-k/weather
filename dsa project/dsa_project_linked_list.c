#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a task
struct Task {
    char description[100];
    int priority;
    char due_date[20];
    int is_done;
    struct Task* next;
};

// Head of the linked list
struct Task* head = NULL;

// Function to compare tasks for sorting
int compareTasks(const struct Task* a, const struct Task* b) {
    // First, compare by due date
    int dateComparison = strcmp(a->due_date, b->due_date);

    // If due dates are the same, compare by priority
    if (dateComparison == 0) {
        return a->priority - b->priority;
    }

    return dateComparison;
}

// Function to add a task to the to-do list
void addTask(char* description, int priority, char* due_date) {
    struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
    if (newTask == NULL) {
        printf("Memory allocation failed. Cannot add task.\n");
        return;
    }

    strcpy(newTask->description, description);
    newTask->priority = priority;
    strcpy(newTask->due_date, due_date);
    newTask->is_done = 0;
    newTask->next = NULL;

    // Inserting the new task at the appropriate position to maintain order
    struct Task** current = &head;
    while (*current != NULL && compareTasks(newTask, *current) > 0) {
        current = &(*current)->next;
    }

    newTask->next = *current;
    *current = newTask;

    printf("Awesome! Task added successfully!\n");
}

// Function to display all tasks in the to-do list
void displayTasks() {
    if (head == NULL) {
        printf("Oh no! The to-do list is empty.\n");
        return;
    }

    printf("To-do List:\n");
    struct Task* current = head;
    int taskNumber = 1;
    while (current != NULL) {
        // Printing task details
        printf("Task %d: Description: %s, Priority: %d, Due Date: %s, Status: %s\n",
               taskNumber++, current->description, current->priority, current->due_date,
               current->is_done ? "Done" : "Not Done");
        current = current->next;
    }
}

// Function to mark a task as done and move it to the end
void markTaskAsDone(int taskIndex) {
    struct Task* current = head;
    struct Task* prev = NULL;
    int currentIndex = 0;

    // Traverse the linked list to find the task at the given index
    while (current != NULL && currentIndex < taskIndex) {
        prev = current;
        current = current->next;
        currentIndex++;
    }

    if (current != NULL) {
        // If the task is already done, no need to rearrange
        if (current->is_done == 1) {
            printf("This task is already marked as done.\n");
            return;
        }

        // Mark the task as done
        current->is_done = 1;

        // If the task is not the last one, rearrange the linked list
        if (current->next != NULL) {
            // Unlink the current task
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                head = current->next;
            }

            // Traverse to the end of the list
            struct Task* lastTask = current;
            while (lastTask->next != NULL) {
                lastTask = lastTask->next;
            }

            // Place the completed task at the end
            lastTask->next = current;
            current->next = NULL;
        }

        printf("Great job! Task marked as done and moved to the end.\n");
    } else {
        printf("Uh-oh! Invalid task index. Task not found.\n");
    }
}

// Function to delete a task
void deleteTask(int taskIndex) {
    struct Task** current = &head;
    int currentIndex = 0;

    while (*current != NULL && currentIndex < taskIndex) {
        current = &(*current)->next;
        currentIndex++;
    }

    if (*current != NULL) {
        struct Task* temp = *current;
        *current = (*current)->next;
        free(temp);
        printf("Task deleted successfully.\n");
    } else {
        printf("Oops! Invalid task index. Task not found.\n");
    }
}

// Function to free the allocated memory for the linked list
void freeTasks() {
    struct Task* current = head;
    while (current != NULL) {
        struct Task* temp = current;
        current = current->next;
        free(temp);
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
                freeTasks();  // Free allocated memory before exiting
                printf("Exiting Task Planner. Have a great day!\n");
                break;
            default:
                printf("Oops! Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}
