#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CursorBased.h"

Student newStudent(int studID, string studName, char sex, string program){
	Student s;
	
	s.studID = studID;
	strcpy(s.studName,studName);
	s.sex = sex;
	strcpy(s.program,program);
	
	return s;
}

VirtualHeap newVirtualHeap(){ //empty function
	VirtualHeap vh;
	int i;
	
	for(i=0; i<MAX; ++i){
		vh.elems[i].elem = newStudent(0,"",' ',""); //or vh.elems[i].elem.studID = 0;
		vh.elems[i].next = i-1; // cause we started at -1
	}
	vh.avail = MAX-1;

	return vh;
}
int allocSpace(VirtualHeap *vh){ //equivalent to malloc
	int retVal = vh->avail; //temp
	
	if(retVal != -1){
		vh->avail = vh->elems[vh->avail].next; //can use retval
	}
	
	return retVal;
}
void insertFirst(VirtualHeap *vh, List *list, Student s){ //will still contain integer type
	List temp = allocSpace(vh/*vh ra kay pointer*/);
	
	if(temp != -1){
		vh->elems[temp].next = *list;    //assigning
		*list = temp;                   //assigning
		vh->elems[temp].elem = s; //placing value
	}
}

void displayList(VirtualHeap vh,List list){ //both traversal will only show whats in the list, no index
	int i;
	printf("%4s | %25s \n"," ID ","NAME");
	printf("-----------------------\n");
	for(i=0;i<MAX; ++i){
		if(vh.elems[i].elem.studID != 0){
			printf("%4d - %23s \n",vh.elems[i].elem.studID,vh.elems[i].elem.studName);	
		}
	}

}
void visualizeSpace(VirtualHeap vh){
	int i;
	printf("%5s | %30s | %s\n","INDEX","ELEMENTS","NEXT");
	printf("------------------------------------------\n");
	for(i=0;i<MAX; ++i){
		printf("%5d | ",i);
		if(vh.elems[i].elem.studID == -1){
			printf("%30s | ","Empty");
		} else{
			printf("%4d - %23s | ",vh.elems[i].elem.studID,vh.elems[i].elem.studName);	
		}
		printf("%d\n",vh.elems[i].next);
	}
	printf("------------------------------------------\n");
	printf("AVAILABLE: %d\n\n", vh.avail);
	
}

/*free/delete the next, change the index with the next to the deleted next before deleting it,
next will be the available value or 0 indicating empty, update avail to the next index that is available */
void deallocSpace(VirtualHeap *vh, int ndx){ // this function will only set next or relink and repurpose the index. Will set avail to the deleted | NO DELETE only RELINK
	vh->elems[ndx].next = vh->avail;
    vh->avail = ndx;
}

Student removeStudent(VirtualHeap *vh, List *list, string keyword){ //use deallocSpace
	Student retVal;
    int current = *list;
    int previous = -1;

    while (current != -1) {
        Student s = vh->elems[current].elem;
        if (strcmp(s.studName, keyword) == 0) {
            if (previous == -1) {
                *list = vh->elems[current].next;
            } else {
                vh->elems[previous].next = vh->elems[current].next;
            }
            deallocSpace(vh, current);
            retVal = s;
            break;
        }
        previous = current;
        current = vh->elems[current].next;
    }

    return retVal;
}
