#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Linked list structure
typedef struct LinkedList {
    Node* head;
} LinkedList;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the end of the list
void insert(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to insert a new node at a specific position
void insertAtPosition(LinkedList* list, int data, int position) {
    Node* newNode = createNode(data);
    if (position == 0) {
        newNode->next = list->head;
        list->head = newNode;
        return;
    }

    Node* current = list->head;
    for (int i = 0; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Position out of bounds\n");
        free(newNode);
        return;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// Function to delete a node by value
void deleteNode(LinkedList* list, int value) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node* current = list->head;
    Node* previous = NULL;

    // Check if the head node is the one to be deleted
    if (current->data == value) {
        list->head = current->next; // Move head to the next node
        free(current);
        return;
    }

    // Traverse the list to find the node to delete
    while (current != NULL && current->data != value) {
        previous = current;
        current = current->next;
    }

    // If the value was not found
    if (current == NULL) {
        printf("Value %d not found in the list\n", value);
        return;
    }

    // Unlink the node from the list
    previous->next = current->next;
    free(current);
}

// Function to print the linked list
void printList(LinkedList* list) {
    Node* current = list->head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Example usage
int main() {
    LinkedList list;
    list.head = NULL;

    insert(&list, 1);
    insert(&list, 2);
    insert(&list, 3);
    printf("Initial list: ");
    printList(&list);

    insertAtPosition(&list, 4, 1); // Insert 4 at position 1
    printf("After inserting 4 at position 1: ");
    printList(&list);

    deleteNode(&list, 2); // Delete node with value 2
    printf("After deleting 2: ");
    printList(&list);

    deleteNode(&list, 5); // Attempt to delete a non-existent value
    printf("After attempting to delete 5: ");
    printList(&list);

    return 0;
}


