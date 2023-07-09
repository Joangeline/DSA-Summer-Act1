#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"Employee.h"


HourlyEmployee newEmployee(int id, string name, string gender, float hours){
	HourlyEmployee he;
	
	he.idNumber = id;
	strcpy(he.name,name);
	strcpy(he.gender,gender);
	he.totalHoursWorked = hours;
	
	return he;
}

void displayEmployee(HourlyEmployee he){
	printf("ID: %d\n", he.idNumber);
	printf("NAME: %s\n",he.name);
	printf("GENDER: %s\n",he.gender);
	printf("HOURS WORKED: %.2f", he.totalHoursWorked);
}

void initList(List *list){
	list->max = 2;
	list->employees = malloc(sizeof(HourlyEmployee)*list->max);
	list->count = 0;
}
void addEmployee(List *list, HourlyEmployee emp){
	if(list->count == list->max){
		list->max *= 2;
		list->employees = realloc(list->employees,sizeof(HourlyEmployee)*list->max);
	}
	
	list->employees[(list->count)++] = emp;
}
void displayEmployeeList(List list){
	int i;
	printf("%10s | %30s | %10s\n", "ID" , "NAME", "GENDER");
	for(i=0;i<list.count; ++i){
		printf("%10s | %30s | %10c\n",list.employees[i].idNumber, list.employees[i].name,list.employees[i].gender);
	}
	printf("END OF LIST\n\n");
}
List getFemaleEmployees(List list){
	List femaleList;
	initList(&femaleList);
	int i;
	for(i= 0; i < list.count;++i){
		if(!strcmp(list.employees[i].gender,"female")){
			addEmployee(&femaleList,list.employees[i]);
		}
	}
	
	return femaleList;
}
