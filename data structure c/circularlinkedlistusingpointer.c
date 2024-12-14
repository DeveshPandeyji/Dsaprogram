#include <stdio.h>
#include <stdlib.h>

// Node structure for a circular singly linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Circular singly linked list structure
typedef struct CircularLinkedList {
    Node* head;
} CircularLinkedList;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the end of the list
void insertEnd(CircularLinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        newNode->next = newNode; // Point to itself
    } else {
        Node* current = list->head;
        while (current->next != list->head) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = list->head; // Make it circular
    }
}

// Function to insert a new node at the beginning of the list
void insertBeginning(CircularLinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        newNode->next = newNode; // Point to itself
    } else {
        Node* current = list->head;
        while (current->next != list->head) {
            current = current->next;
        }
        newNode->next = list->head;
        current->next = newNode; // Make it circular
        list->head = newNode; // Update head
    }
}

// Function to delete a node by value
void deleteNode(CircularLinkedList* list, int value) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node* current = list->head;
    Node* previous = NULL;

    do {
        if (current->data == value) {
            if (previous == NULL) { // Node to delete is head
                if (current->next == list->head) { // Only one node
                    free(current);
                    list->head = NULL;
                } else {
                    Node* last = list->head;
                    while (last->next != list->head) {
                        last = last->next;
                    }
                    last->next = current->next; // Update last node's next
                    list->head = current->next; // Update head
                    free(current);
                }
            } else {
                previous->next = current->next; // Bypass the current node
                free(current);
            }
            return;
        }
        previous = current;
        current = current->next;
    } while (current != list->head);

    printf("Value %d not found in the list\n", value);
}

// Function to print the circular linked list
void printList(CircularLinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node* current = list->head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("\n");
}

// Example usage
int main() {
    CircularLinkedList list;
    list.head = NULL;

    insertEnd(&list, 1);
    insertEnd(&list, 2);
    insertEnd(&list, 3);
    printf("List after inserting at the end: ");
    printList(&list);

    insertBeginning(&list, 0);
    printf("List after inserting 0 at the beginning: ");
    printList(&list);

    deleteNode(&list, 2);
    printf("List after deleting 2: ");
    printList(&list);

    deleteNode(&list, 0);
    printf("List after deleting 0: ");
    printList(&list);

    deleteNode(&list, 5); // Attempt to delete a non-existent value
    printf("List after attempting to delete 5: ");
    printList(&list);

    return 0;
}