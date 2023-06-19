#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

void initList(List* list) {
    *list = NULL;
}

List newList() {
    List list;
    initList(&list);
    return list;
}

NodeType createNode(DATA data) {
    NodeType newNode;
    newNode.data = data;
    newNode.next = NULL;
    return newNode;
}

void displayList(List list) {
    NodePtr current = list;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}


bool insertFront(List* list, DATA item) {
    NodePtr newNode = (NodePtr)malloc(sizeof(NodeType));
    if (newNode == NULL)
        return false;

    newNode->data = item;
    newNode->next = *list;
    *list = newNode;
    return true;
}

bool insertRear(List* list, DATA item) {
    NodePtr newNode = (NodePtr)malloc(sizeof(NodeType));
    if (newNode == NULL)
        return false;

    newNode->data = item;
    newNode->next = NULL;

    if (*list == NULL) {
        *list = newNode;
    } else {
        NodePtr current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    return true;
}

bool insertAt(List *list, DATA item, int loc);

bool insertSorted(List *list, DATA data);

bool searchItem(List list, DATA key) {
    NodePtr current = list;
    while (current != NULL) {
        if (current->data == key)
            return true;
        current = current->next;
    }
    return false;
}

int getItem(List list, DATA key);

bool deleteFront(List* list) {
    if (*list == NULL)
        return false;

    NodePtr front = *list;
    *list = (*list)->next;
    free(front);
    return true;
}

bool deleteRear(List *list);

int deleteAt(List *list, int loc);

bool deleteItem(List* list, DATA key) {
    NodePtr current = *list;
    NodePtr previous = NULL;
    while (current != NULL) {
        if (current->data == key) {
            if (previous == NULL) {
                deleteFront(list);
                return true;
            } else {
                previous->next = current->next;
                free(current);
                return true;
            }
        }
        previous = current;
        current = current->next;
    }
    return false;
}

int deleteAllItem(List* list, DATA key) {
    int count = 0;
    NodePtr current = *list;
    while (current != NULL) {
        if (current->data == key) {
            if (current == *list) {
                deleteFront(list);
            } else {
                NodePtr previous = *list;
                while (previous->next != current) {
                    previous = previous->next;
                }
                previous->next = current->next;
                free(current);
            }
            count++;
            current = current->next;
        } else {
            current = current->next;
        }
    }
    return count;
}
