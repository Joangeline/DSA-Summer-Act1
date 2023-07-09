#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef char String[40];

typedef struct {
    String FName;
    String MName;
    String LName;
} NameType;

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    String studID;
    NameType studName;
    char sex;
    Date birthDate;
    String program;
    int year;
} StudentType;

typedef struct node {
    StudentType student;
    struct node* link;
} SType, *List;

typedef struct {
    SType* students;
    int count;
    int max;
} Dictionary;

NameType addName(String firstname, String middlename, String lastname) {
    NameType name;
    strcpy(name.FName, firstname);
    strcpy(name.MName, middlename);
    strcpy(name.LName, lastname);
    return name;
}

Date addDate(int day, int month, int year) {
    Date date;
    date.day = day;
    date.month = month;
    date.year = year;
    return date;
}

StudentType addStudent(String studID, NameType studName, char sex, Date birthdate, String program, int year) {
    StudentType student;
    strcpy(student.studID, studID);
    student.studName = studName;
    student.sex = sex;
    student.birthDate = birthdate;
    strcpy(student.program, program);
    student.year = year;
    return student;
}

void initDict(Dictionary* d, int size) {
	int i;
    d->students = (SType*)malloc(size * sizeof(SType));
    d->count = 0;
    d->max = size;
    for (i = 0; i < size; i++) {
        d->students[i].link = NULL;
    }
}

char hash(String LastName, int size) {
    return LastName[0] % size;
}

bool addElement(Dictionary* D, StudentType S) {
    if (D->count >= D->max){
    	return false;
	}
    int index = hash(S.studName.LName, D->max);
    SType* newNode = (SType*)malloc(sizeof(SType));
    newNode->student = S;
    newNode->link = D->students[index].link;
    D->students[index].link = newNode;
    D->count++;
    return true;
}

bool deleteElement(Dictionary* D, StudentType S) {
    int index = hash(S.studName.LName, D->max);
    SType* current = D->students[index].link;
    SType* previous = NULL;
    while (current != NULL) {
        if (strcmp(current->student.studID, S.studID) == 0) {
            if (previous == NULL)
                D->students[index].link = current->link;
            else
                previous->link = current->link;
            free(current);
            D->count--;
            return true;
        }
        previous = current;
        current = current->link;
    }
    return false;
}

bool searchElement(Dictionary* D, StudentType S) {
    int index = hash(S.studName.LName, D->max);
    SType* current = D->students[index].link;
    while (current != NULL) {
        if (strcmp(current->student.studID, S.studID) == 0)
            return true;
        current = current->link;
    }
    return false;
}

void displayStudents(Dictionary D) {
	int i;
    for (i = 0; i < D.max; i++) {
        SType* current = D.students[i].link;
        while (current != NULL) {
            printf("Student ID: %s\n", current->student.studID);
            printf("Name: %s %s %s\n", current->student.studName.FName, current->student.studName.MName, current->student.studName.LName);
            printf("Sex: %c\n", current->student.sex);
            printf("Birthdate: %d-%d-%d\n", current->student.birthDate.day, current->student.birthDate.month, current->student.birthDate.year);
            printf("Program: %s\n", current->student.program);
            printf("Year: %d\n", current->student.year);
            printf("\n");
            current = current->link;
        }
    }
}

void visualizeStudents(Dictionary D) {
	int i;
    for (i = 0; i < D.max; i++) {
        printf("[%d]: ", i);
        SType* current = D.students[i].link;
        while (current != NULL) {
            printf("%s -> ", current->student.studID);
            current = current->link;
        }
        printf("NULL\n");
    }
}

int main(int argc, char* argv[]) {
    Dictionary dict;
    initDict(&dict, 26);

    // Add students
    NameType name1 = addName("John", "Robert", "Doe");
    Date date1 = addDate(12, 3, 2000);
    StudentType student1 = addStudent("ABC231", name1, 'M', date1, "Computer Science", 2);
    addElement(&dict, student1);

    NameType name2 = addName("Jane", "Marie", "Smith");
    Date date2 = addDate(5, 9, 2001);
    StudentType student2 = addStudent("CCC02", name2, 'F', date2, "Business Administration", 1);
    addElement(&dict, student2);

    NameType name3 = addName("David", "Michael", "Johnson");
    Date date3 = addDate(18, 6, 1999);
    StudentType student3 = addStudent("DBC003", name3, 'M', date3, "Electrical Engineering", 3);
    addElement(&dict, student3);

    // Display students
    displayStudents(dict);

    // Visualize students
    visualizeStudents(dict);

    return 0;
}
