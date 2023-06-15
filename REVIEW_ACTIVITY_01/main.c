#include <stdio.h>
#include <stdlib.h>
#include "StaticArray.h"
// include the library you want to test

int main(int argc, char *argv[]) {
    List list = newList();

    insertFront(&list, 10);
    insertRear(&list, 20);
    insertSorted(&list, 15);
    insertAt(&list, 5, 0);
    insertAt(&list, 25, 4);

    displayList(list);

    printf("Item 20 found at index: %d\n", getItem(list, 20));

    deleteFront(&list);
    deleteRear(&list);
    deleteItem(&list, 15);

    displayList(list);

    int deletedCount = deleteAllItem(&list, 25);
    printf("%d occurrences of item 25 deleted.\n", deletedCount);

    return 0;
}
