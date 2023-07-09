#include <stdio.h>
#include <stdlib.h>
#include "MyHeader.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int maxSize = 10;
    VSpace space = newVSpace(maxSize);
    visualize(space);
    
    addElement(&space, 7);
    addElement(&space, 23);
    addElement(&space, 8);
    addElement(&space, 11);
    addElement(&space, 21);
    addElement(&space, 3);
    addElement(&space, 18);
    
    visualize(space);
    
	removeElement(&space, 21);

    // Visualize the dictionary after removal
    visualize(space);

	
	return 0;
}
