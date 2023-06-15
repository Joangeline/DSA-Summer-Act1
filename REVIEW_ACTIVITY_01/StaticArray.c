#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "StaticArray.h"


void initList(List *list) {
    list->count = 0;
}

List newList() {
    List list;
    initList(&list);
    return list;
}

void displayList(List list) {
    printf("List elements: ");
    for (int i = 0; i < list.count; i++) {
        printf("%d ", list.elems[i]);
    }
    printf("\n");
}

bool insertFront(List *list, DATA item) {
    if (list->count == MAX) {
        printf("List is full.\n");
        return false;
    }

    for (int i = list->count - 1; i >= 0; i--) {
        list->elems[i + 1] = list->elems[i];
    }

    list->elems[0] = item;
    list->count++;
    return true;
}

bool insertRear(List *list, DATA item) {
    if (list->count == MAX) {
        printf("List is full. Cannot insert.\n");
        return false;
    }

    list->elems[list->count] = item;
    list->count++;
    return true;
}

bool insertSorted(List *list, DATA item) {
    if (list->count == MAX) {
        printf("List is full. Cannot insert.\n");
        return false;
    }

    int i = list->count - 1;
    while (i >= 0 && list->elems[i] > item) {
        list->elems[i + 1] = list->elems[i];
        i--;
    }

    list->elems[i + 1] = item;
    list->count++;
    return true;
}

bool insertAt(List *list, DATA item, int loc) {
    if (loc < 0 || loc > list->count) {
        printf("Invalid location. Cannot insert.\n");
        return false;
    }

    if (list->count == MAX) {
        printf("List is full. Cannot insert.\n");
        return false;
    }

    for (int i = list->count - 1; i >= loc; i--) {
        list->elems[i + 1] = list->elems[i];
    }

    list->elems[loc] = item;
    list->count++;
    return true;
}

bool searchItem(List list, DATA key) {
    for (int i = 0; i < list.count; i++) {
        if (list.elems[i] == key) {
            return true;
        }
    }
    return false;
}

int getItem(List list, DATA key) {
    for (int i = 0; i < list.count; i++) {
        if (list.elems[i] == key) {
            return i;
        }
    }
    return -1;
}

bool deleteFront(List *list) {
    if (list->count == 0) {
        printf("List is empty. Cannot delete.\n");
        return false;
    }

    for (int i = 1; i < list->count; i++) {
        list->elems[i - 1] = list->elems[i];
    }

    list->count--;
    return true;
}

bool deleteRear(List *list) {
    if (list->count == 0) {
        printf("List is empty. Cannot delete.\n");
        return false;
    }

    list->count--;
    return true;
}

int deleteAt(List *list, int loc) {
    if (loc < 0 || loc >= list->count) {
        printf("Invalid location. Cannot delete.\n");
        return -1;
    }

    int item = list->elems[loc];

    for (int i = loc + 1; i < list->count; i++) {
        list->elems[i - 1] = list->elems[i];
    }

    list->count--;
    return item;
}

bool deleteItem(List *list, DATA key) {
    int loc = getItem(*list, key);
    if (loc == -1) {
        printf("Item not found. Cannot delete.\n");
        return false;
    }

    deleteAt(list, loc);
    return true;
}

int deleteAllItem(List *list, DATA key) {
    int count = 0;
    int loc;

    while ((loc = getItem(*list, key)) != -1) {
        deleteAt(list, loc);
        count++;
    }

    return count;
}

