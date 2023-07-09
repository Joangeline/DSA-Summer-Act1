#ifndef CURSOR_BASED_H
#define CURSOR_BASED_H

#define MAX 10
//can define EMPTY for retVal alloc

typedef char string[20];
typedef int List;

typedef struct {
	int studID;
	string studName;
	char sex;
	string program;
}Student;


typedef struct {
	Student elem;
	int next;
}SType;

typedef struct{
	SType elems[MAX];
	int avail;
}VirtualHeap;

Student newStudent(int studID, string studName, char sex, string program);

VirtualHeap newVirtualHeap(); //empty function
int allocSpace(VirtualHeap *vh); //equivalent to malloc
void insertFirst(VirtualHeap *vh, List *list, Student s); //will still contain integer type

void displayList(VirtualHeap vh,List list); //both traversal
void visualizeSpace(VirtualHeap vh);//

void deallocSpace(VirtualHeap *vh, int ndx); //free delete the next, change the index with the next to the deleted next before deleting it,
Student removeStudent(VirtualHeap *vh, List *list, string keyword); // next will be the available value or 0 indicating empty, update avail to the next index that is available

#endif
