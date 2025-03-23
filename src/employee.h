#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "common.h"

// Global Vars
extern Employee* employees;
extern int employeeCount;

void addEmployee();
void displayAllEmployees();
void filterByDepartment();
void searchEmployee();
void updateEmployee();
void deleteEmployee();

#endif // EMPLOYEE_H
