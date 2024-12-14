
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct Node {
    int data;
    int next;
} Node;

typedef struct LinkedList {
    Node nodes[MAX_NODES];
    int head;
    int free;
    int size;
} LinkedList;

void initList(LinkedList *list) {
    list->head = -1;
    list->free = 0;
    list->size = 0;

    for (int i = 0; i < MAX_NODES - 1; i++) {
        list->nodes[i].next = i + 1;
    }
    list->nodes[MAX_NODES - 1].next = -1;
}

int allocateNode(LinkedList *list) {
    if (list->free == -1) {
        printf("No more space to allocate new node.\n");
        return -1;
    }
    int newNodeIndex = list->free;
    list->free = list->nodes[newNodeIndex].next;
    return newNodeIndex;
}

void freeNode(LinkedList *list, int index) {
    list->nodes[index].next = list->free;
    list->free = index;
}

void insertEnd(LinkedList *list, int data) {
    int newNodeIndex = allocateNode(list);
    if (newNodeIndex == -1) return;

    list->nodes[newNodeIndex].data = data;
    list->nodes[newNodeIndex].next = -1;

    if (list->head == -1) {
        list->head = newNodeIndex;
    } else {
        int current = list->head;
        while (list->nodes[current].next != -1) {
            current = list->nodes[current].next;
        }
        list->nodes[current].next = newNodeIndex;
    }
    list->size++;
}

void deleteNode(LinkedList *list, int value) {
    if (list->head == -1) {
        printf("List is empty. Cannot delete.\n");
        return;
    }

    int current = list->head;
    int previous = -1;

    while (current != -1 && list->nodes[current].data != value) {
        previous = current;
        current = list->nodes[current].next;
    }

    if (current == -1) {
        printf("Value %d not found in the list.\n", value);
        return;
    }

    if (previous == -1) {
        list->head = list->nodes[current].next;
    } else {
        list->nodes[previous].next = list->nodes[current].next;
    }

    freeNode(list, current);
    list->size--;
}

void displayList(LinkedList *list) {
    if (list->head == -1) {
        printf("List is empty.\n");
        return;
    }

    int current = list->head;
    while (current != -1) {
        printf("%d -> ", list->nodes[current].data);
        current = list->nodes[current].next;
    }
    printf("NULL\n");
}
int main() {
    LinkedList list;
    initList(&list);
    insertEnd(&list, 10);
    insertEnd(&list, 20);
    insertEnd(&list, 30);
    displayList(&list);
    deleteNode(&list, 20);
    displayList(&list);
    deleteNode(&list, 10);
    displayList(&list);
    return 0;
}
