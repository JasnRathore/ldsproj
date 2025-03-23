#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "common.h"

// Global Vars
extern Department* departments;
extern int departmentCount;

// Function prototypes for department operations
void manageDepartments();
void addDepartment();
void viewDepartments();
void deleteDepartment();
void updateDepartmentStats();
int isDepartmentExists(const char *deptName);

#endif // DEPARTMENT_H
