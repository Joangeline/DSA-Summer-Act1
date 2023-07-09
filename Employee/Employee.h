#ifndef EMPLOYEE_H
#define EMPLOYEE_H

typedef char string[30];

typedef struct {
	int idNumber;
	string name;
	string gender;
	float totalHoursWorked;
} HourlyEmployee, *EmployeeList;

typedef struct{
	EmployeeList employees;
	int count;
	int max;
} List;

HourlyEmployee newEmployee(int id, string name, string gender,float hours);
void displayEmployee(HourlyEmployee he);

void initList(List *list);
void addEmployee(List *list, HourlyEmployee emp); //use insert rear
void displayEmployeeList(List list);
List getFemaleEmployees(List list);

#endif
