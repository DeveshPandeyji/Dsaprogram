#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct DoublyLinkedList {
    Node* head;
} DoublyLinkedList;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertEnd(DoublyLinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
}

void insertBeginning(DoublyLinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

void insertAtPosition(DoublyLinkedList* list, int data, int position) {
    Node* newNode = createNode(data);
    if (position == 0) {
        insertBeginning(list, data);
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
    newNode->prev = current;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;
}

void deleteNode(DoublyLinkedList* list, int value) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node* current = list->head;
    while (current != NULL && current->data != value) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Value %d not found in the list\n", value);
        return;
    }
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        list->head = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    free(current);
}

void printList(DoublyLinkedList* list) {
    Node* current = list->head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void printListReverse(DoublyLinkedList* list) {
    Node* current = list->head;
    if (current == NULL) return;
    while (current->next) {
        current = current->next;
    }
    while (current) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}

void searchValue(DoublyLinkedList* list, int value) {
    Node* current = list->head;
    while (current != NULL) {
        if (current->data == value) {
            printf("Value %d found in the list\n", value);
            return;
        }
        current = current->next;
    }
    printf("Value %d not found in the list\n", value);
}

int main() {
    DoublyLinkedList list;
    list.head = NULL;

    insertEnd(&list, 10);
    insertEnd(&list, 20);
    insertEnd(&list, 30);
    printf("List after inserting elements at the end: ");
    printList(&list);

    insertBeginning(&list, 5);
    printf("List after inserting 5 at the beginning: ");
    printList(&list);

    insertAtPosition(&list, 15, 2);
    printf("List after inserting 15 at position 2: ");
    printList(&list);

    deleteNode(&list, 20);
    printf("List after deleting 20: ");
    printList(&list);

    printf("List in reverse order: ");
    printListReverse(&list);

    searchValue(&list, 15);
    searchValue(&list, 50);

    return 0;
}
