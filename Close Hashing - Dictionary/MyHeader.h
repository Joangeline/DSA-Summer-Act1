#ifndef MYHEADER_H
#define MYHEADER_H
#include <stdbool.h>

#define EMPTY 9999 // use if the link is -1. Default is EMPTY //0
#define DELETED 9998 //use if link has synonym//-1
//if the function reaches 70% it is already full or full synonym area (adding synonym or adding non synonym)
//malloc, rehash, free data
//chaining -Cursor Based

//previous activity is chaining dictionary but in linked list environment

//Dictionary is simply adding into a specific location/index 

typedef struct {
	int elem;
	int link;
}Data;

typedef struct {
	Data *data;
	int avail;
	int count;
	int max;
}VSpace; //Dictionary

int hash(int val, int size){
	return val % size;
}
VSpace newVSpace(int max) {
    VSpace vs;
    
    vs.max = max%2 == 0? max: max + 1;
    vs.count = 0;
    vs.data = malloc(sizeof(Data) * vs.max);
    vs.avail = vs.max/2;
    
    int i;
    for(i = 0; i < vs.avail; ++i) {
        vs.data[i].elem = EMPTY;
        vs.data[i].link = -1;
    }
    
    for(; i < vs.max-1; ++i) {
        vs.data[i].elem = EMPTY;
        vs.data[i].link = i + 1;    
    }
    vs.data[i].elem = EMPTY;
    vs.data[i].link = -1;
    
    return vs;
}
int allocSpace(VSpace *vs){
	// for synonym can be removeable
	int loc = vs->avail;
    if (loc != -1) {
        vs->avail = vs->data[loc].link;
        vs->data[loc].elem = EMPTY;
        vs->data[loc].link = -1;
    }
    return loc;
}
void freeSpace(VSpace *vs, int loc){
	// for synonym can be removeable
	vs->data[loc].elem = EMPTY;
    vs->data[loc].link = vs->avail;
    vs->avail = loc;
 
}
bool addElement(VSpace *vs, int elem){
	int loc = hash(elem, vs->max);//if the space is still -1 add it there
				//if the index has already a value/element the synonym elem will use the next avail. 
				//link of the synonym index should change into the 
				//if space is already 
				//synonym area will always be empty  
				// u can implement allocspace here (if there is a synonym u use allocspace)
	int start = loc;
    int prev = -1;

    while (loc != -1) {
        if (vs->data[loc].elem == EMPTY || vs->data[loc].elem == DELETED) {
            vs->data[loc].elem = elem;
            vs->data[loc].link = -1;
            if (prev != -1) {
                vs->data[prev].link = loc;
            }
            vs->count++;
            return true;
        }
        prev = loc;
        loc = vs->data[loc].link;
    }

    if (vs->avail != -1) {
        loc = allocSpace(vs);
        if (loc != -1) {
            vs->data[loc].elem = elem;
            vs->data[loc].link = -1;
            if (prev != -1) {
                vs->data[prev].link = loc;
            }
            vs->count++;
            return true;
        }
    }

    return false;
}
bool removeElement(VSpace *vs, int elem){
	int loc = hash(elem, vs->max);
    int prev = -1;

    while (loc != -1) {
        if (vs->data[loc].elem == elem) {
            if (prev != -1) {
                vs->data[prev].link = vs->data[loc].link;
            } else {
                vs->data[loc].elem = DELETED;
            }
            freeSpace(vs, loc);
            vs->count--;
            return true;
        }
        prev = loc;
        loc = vs->data[loc].link;
    }

    return false;
}
void visualize(VSpace vs){
	int i, half = vs.max/2;
	printf("%5s | %5s | %5s  %10s %5s | %5s | %5s \n", "INDEX","DATA","LINK","","INDEX","DATA","LINK");
	printf("-----------------------          ---------------------\n");
	for(i=0; i < half; i++){
		printf("%5d | %5d | %5d  %10s %5d | %5d | %5d \n",
				 i,vs.data[i].elem==EMPTY?0:vs.data[i].elem,vs.data[i].link,"",
				 i+half,vs.data[i+half].elem==EMPTY?0:vs.data[i+half].elem,vs.data[i+half].link);
	}
}

#endif
