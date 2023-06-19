#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

int main(int argc, char *argv[]) {
	
	List myList = newList();

    insertFront(&myList, 3);
    insertFront(&myList, 2);
    insertFront(&myList, 1);

    displayList(myList);

    insertRear(&myList, 4);
    insertRear(&myList, 5);

	displayList(myList);

    deleteFront(&myList);

    displayList(myList);

    printf("Searching for item 4: %s\n", searchItem(myList, 4) ? "Found" : "Not Found");
    printf("Searching for item 8: %s\n", searchItem(myList, 8) ? "Found" : "Not Found");

    deleteItem(&myList, 4);

    displayList(myList);

    int count = deleteAllItem(&myList, 2);
    printf("%d instances of item 2 deleted\n", count);

    displayList(myList);

    return 0;
}
