#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	List empList;
	
	initList(&empList);
	
	addEmployee(&empList, newEmployee(1001,"Maria Dela Cruz","female",40.0f));
	addEmployee(&empList, newEmployee(1020,"Sabrina Yap","female",35.0f));
	addEmployee(&empList, newEmployee(1045,"Noel Tagpuno","male",45.0f));
	displayEmployeeList(empList);
	
	
	return 0;
}
