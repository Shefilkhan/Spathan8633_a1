/*
  FILE          : Spathan8633_a1.c
  PROJECT       : Assignment #1
  PROGRAMMER    : Shefilkhan Pathan
  FIRST VERSION : 2025-06-08
  DESCRIPTION   : This program implements a simple Todo list manager using
                  singly linked lists. It supports operations to add, delete,
                  find, print, and free Todo items.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// Struct definition
typedef struct Todo {
    int TodoId;
    char Title[100];
    char Description[250];
    struct Todo* NextTodo;
} Todo;

// Function prototypes
Todo* CreateNewTodo(int todoId, const char* title, const char* description);
Todo* AddTodo(Todo* head);
Todo* DeleteTodoByTodoId(Todo* head);
void FindTodoByIndex(Todo* head);
void PrintTodos(Todo* head);
void FreeList(Todo* head);

/*
  FUNCTION      : CreateNewTodo
  DESCRIPTION   : Allocates and initializes a new Todo node with the given values.
  PARAMETERS    : int todoId              - ID of the new todo
                  const char* title       - Title of the todo
                  const char* description - Description of the todo
  RETURNS       : Todo* - Pointer to the newly created Todo
 */
Todo* CreateNewTodo(int todoId, const char* title, const char* description) {
    Todo* newTodo = (Todo*)malloc(sizeof(Todo));
    if (newTodo == NULL) {
        printf("No memory!\n");
        exit(EXIT_FAILURE);
    }

    newTodo->TodoId = todoId;

    int i = 0;
    while (title[i] != '\0' && i < 99) {
        newTodo->Title[i] = title[i];
        i++;
    }
    newTodo->Title[i] = '\0';

    i = 0;
    while (description[i] != '\0' && i < 249) {
        newTodo->Description[i] = description[i];
        i++;
    }
    newTodo->Description[i] = '\0';

    newTodo->NextTodo = NULL;
    return newTodo;
}

/*
  FUNCTION      : AddTodo
  DESCRIPTION   : Gets input from the user, creates a new Todo, and adds it to the end of the list.
  PARAMETERS    : Todo* head - Pointer to the current head of the list
  RETURNS       : Todo* - Pointer to the new head (in case it was NULL before)
 */
Todo* AddTodo(Todo* head) {
    int id = 0;
    char title[100] = "";
    char desc[250] = "";

    printf("Enter Todo ID: ");
    if (scanf_s("%d", &id) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return head;
    }
    getchar();// clear newline

    printf("Enter Title: ");
    if (fgets(title, sizeof(title), stdin) == NULL) {
        printf("Error reading title.\n");
        return head;
    }
    title[strcspn(title, "\n")] = '\0'; //remove newline

    printf("Enter Description: ");
    if (fgets(desc, sizeof(desc), stdin) == NULL) {
        printf("Error reading description.\n");
        return head;
    }
    desc[strcspn(desc, "\n")] = '\0';

    Todo* newTodo = CreateNewTodo(id, title, desc);

    if (head == NULL) {
        return newTodo;
    }

    Todo* current = head;
    while (current->NextTodo != NULL) {
        current = current->NextTodo;
    }
    current->NextTodo = newTodo;

    return head;
}

/*
  FUNCTION      : DeleteTodoByTodoId
  DESCRIPTION   : Deletes a Todo node matching the user-supplied ID.
  PARAMETERS    : Todo* head - Pointer to the current head of the list
  RETURNS       : Todo* - Updated head after deletion (if applicable)
 */
Todo* DeleteTodoByTodoId(Todo* head) {
    int id;
    printf("Enter Todo ID to delete: ");
    if (scanf_s("%d", &id) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return head;
    }
    getchar();

    Todo* current = head;
    Todo* previous = NULL;

    //traverse to find the target node
    while (current != NULL && current->TodoId != id) {
        previous = current;
        current = current->NextTodo;
    }

    if (current == NULL) {
        printf("Todo ID %d not found.\n", id);
        return head;
    }

    if (previous == NULL) {
        head = current->NextTodo;
    }
    else {
        previous->NextTodo = current->NextTodo;
    }

    free(current);
    printf("Todo ID %d deleted successfully.\n", id);
    return head;
}

/*
  FUNCTION      : FindTodoByIndex
  DESCRIPTION   : Searches for a Todo node at a user-specified index.
  PARAMETERS    : Todo* head - Pointer to the current head of the list
  RETURNS       : void
 */
void FindTodoByIndex(Todo* head) {
    int index;
    printf("Enter index (starting from 0): ");
    if (scanf_s("%d", &index) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    getchar();

    Todo* current = head;
    int currentIndex = 0;

    while (current != NULL && currentIndex < index) {
        current = current->NextTodo;
        currentIndex++;
    }

    if (current == NULL) {
        printf("Todo not found at index %d.\n", index);
    }
    else {
        printf("Found Todo:\n");
        printf("ID: %d\n", current->TodoId);
        printf("Title: %s\n", current->Title);
        printf("Description: %s\n", current->Description);
    }
}

/*
  FUNCTION      : PrintTodos
  DESCRIPTION   : Prints all Todo items in the list.
  PARAMETERS    : Todo* head - Pointer to the head of the list
  RETURNS       : void
 */
void PrintTodos(Todo* head) {
    if (head == NULL) {
        printf("No todo items found.\n");
        return;
    }

    Todo* current = head;
    while (current != NULL) {
        printf("Address: %p\n", (void*)current);
        printf("ID: %d\n", current->TodoId);
        printf("Title: %s\n", current->Title);
        printf("Description: %s\n", current->Description);
        printf("NextTodo: %p\n", (void*)current->NextTodo);
        printf("-----------------------------\n");
        current = current->NextTodo;
    }
}

/*
  FUNCTION      : FreeList
  DESCRIPTION   : Frees all memory used by the list.
  PARAMETERS    : Todo* head - Pointer to the head of the list
  RETURNS       : void
 */
void FreeList(Todo* head) {
    Todo* current = head;
    Todo* temp = NULL;

    while (current != NULL) {
        temp = current->NextTodo;
        free(current);
        current = temp;
    }
}

/*
  FUNCTION      : main
  DESCRIPTION   : Entry point of the program. Provides menu options to operate on the Todo list.
  PARAMETERS    : void
  RETURNS       : int - exit code
 */
int main() 
{
    int choice = 0;
    Todo* head = NULL;

    while (1) {
        printf("\n------ TODO MENU ------\n");
        printf("1. Add Todo\n");
        printf("2. Delete Todo\n");
        printf("3. Find Todo by Index\n");
        printf("4. Print All Todos\n");
        printf("5. Exit\n");
        printf("Please enter your choice: ");

        if (scanf_s("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        getchar();

        switch (choice) {
        case 1:
            head = AddTodo(head);
            break;
        case 2:
            head = DeleteTodoByTodoId(head);
            break;
        case 3:
            FindTodoByIndex(head);
            break;
        case 4:
            PrintTodos(head);
            break;
        case 5:
            FreeList(head);
            printf("Exiting program. bye!\n");
            return 0;
        default:
            printf("Oops! You select Invalid option. Please try again.\n");
        }
    }

    return 0;
}
