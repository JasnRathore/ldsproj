#ifndef COMMON_H
#define COMMON_H

#define MAX_EMPLOYEES 100
#define MAX_DEPARTMENTS 10
#define NAME_LENGTH 50
#define DEPT_LENGTH 30
#define ID_LENGTH 10
#define FILE_PATH_LENGTH 100

// Structure to store employee data
typedef struct Employee {
    char id[ID_LENGTH];
    char name[NAME_LENGTH];
    char department[DEPT_LENGTH];
    float salary;
    int active; // 1 for active, 0 for deleted
    struct Employee* next;
} Employee;

// Structure to store department data
typedef struct Department {
    char name[DEPT_LENGTH];
    int employeeCount;
    float totalSalary;
    struct Department* next;
} Department;

// Function for string operations
void toLowerString(char *str);

#endif // COMMON_H
