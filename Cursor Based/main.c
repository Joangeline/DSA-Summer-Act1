#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CursorBased.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	VirtualHeap myHeap = newVirtualHeap();
	List myList = -1;
	List AnotherList = -1; //2 List borrowing the VirtualHeap
	Student studDelete;
	
	visualizeSpace(myHeap);
	insertFirst(&myHeap, &myList, newStudent(101,"Jon",'m',"BS IT"));
	insertFirst(&myHeap, &myList, newStudent(112,"Jen",'f',"BS IS"));
	
    Student s3 = newStudent(123, "Bob", 'm', "BS CS");
    insertFirst(&myHeap, &myList, s3);
	
	insertFirst(&myHeap, &AnotherList, newStudent(100,"Jeff",'f',"BS IS"));
	
	displayList(myHeap,myList);
	visualizeSpace(myHeap);
	
	studDelete = removeStudent(&myHeap, &myList, "Jon");
	displayList(myHeap,myList);
	visualizeSpace(myHeap);
	

	
	return 0;
}
