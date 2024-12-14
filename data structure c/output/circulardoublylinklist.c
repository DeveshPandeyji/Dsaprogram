#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct CircularDoublyLinkedList {
    Node* head;
} CircularDoublyLinkedList;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->data = data;
    newNode->next = newNode->prev = newNode;
    return newNode;
}

void insertEnd(CircularDoublyLinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* last = list->head->prev;
        last->next = newNode;
        newNode->prev = last;
        newNode->next = list->head;
        list->head->prev = newNode;
    }
}

void insertBeginning(CircularDoublyLinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* last = list->head->prev;
        newNode->next = list->head;
        newNode->prev = last;
        last->next = newNode;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

void insertAtPosition(CircularDoublyLinkedList* list, int data, int position) {
    if (position == 0) {
        insertBeginning(list, data);
        return;
    }
    Node* newNode = createNode(data);
    Node* current = list->head;
    int index = 0;
    do {
        if (index == position - 1) {
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
            return;
        }
        current = current->next;
        index++;
    } while (current != list->head);
    free(newNode);
}

void deleteNode(CircularDoublyLinkedList* list, int value) {
    if (list->head == NULL) return;
    Node* current = list->head;
    do {
        if (current->data == value) {
            if (current->next == current) {
                free(current);
                list->head = NULL;
                return;
            }
            if (current == list->head) {
                list->head = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            return;
        }
        current = current->next;
    } while (current != list->head);
}

void printList(CircularDoublyLinkedList* list) {
    if (list->head == NULL) return;
    Node* current = list->head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("\n");
}

void printListReverse(CircularDoublyLinkedList* list) {
    if (list->head == NULL) return;
    Node* current = list->head->prev;
    do {
        printf("%d ", current->data);
        current = current->prev;
    } while (current != list->head->prev);
    printf("\n");
}

void searchValue(CircularDoublyLinkedList* list, int value) {
    if (list->head == NULL) return;
    Node* current = list->head;
    int index = 0;
    do {
        if (current->data == value) {
            printf("Value %d found at position %d\n", value, index);
            return;
        }
        current = current->next;
        index++;
    } while (current != list->head);
    printf("Value %d not found in the list\n", value);
}

int getLength(CircularDoublyLinkedList* list) {
    if (list->head == NULL) return 0;
    int count = 0;
    Node* current = list->head;
    do {
        count++;
        current = current->next;
    } while (current != list->head);
    return count;
}

void clearList(CircularDoublyLinkedList* list) {
    if (list->head == NULL) return;
    Node* current = list->head;
    do {
        Node* temp = current;
        current = current->next;
        free(temp);
    } while (current != list->head);
    list->head = NULL;
}

int main() {
    CircularDoublyLinkedList list;
    list.head = NULL;

    insertEnd(&list, 10);
    insertEnd(&list, 20);
    insertEnd(&list, 30);
    printList(&list);

    insertBeginning(&list, 5);
    printList(&list);

    insertAtPosition(&list, 15, 2);
    printList(&list);

    deleteNode(&list, 20);
    printList(&list);

    printListReverse(&list);

    searchValue(&list, 15);
    searchValue(&list, 50);

    printf("Length of the list: %d\n", getLength(&list));

    clearList(&list);
    printList(&list);

    return 0;
}
