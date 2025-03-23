#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "department.h"
#include "employee.h"
#include "ui.h"

Department* departments = NULL;
int departmentCount = 0;

void manageDepartments() {
    departmentMenu();
}

void addDepartment() {
    if (departmentCount >= MAX_DEPARTMENTS) {
        printf("Error: Maximum department limit reached!\n");
        return;
    }

    Department* newDepartment = (Department*)malloc(sizeof(Department));
    if (newDepartment == NULL) {
        printf("Error: Memory allocation failed!\n");
        return;
    }

    newDepartment->employeeCount = 0;
    newDepartment->totalSalary = 0.0;
    newDepartment->next = NULL;

    printf("\n--- Add New Department ---\n");
    printf("Enter Department Name: ");
    fgets(newDepartment->name, DEPT_LENGTH, stdin);
    newDepartment->name[strcspn(newDepartment->name, "\n")] = '\0'; // Remove newline

    // Check if department already exists
    if (isDepartmentExists(newDepartment->name)) {
        printf("Error: Department already exists!\n");
        free(newDepartment);
        return;
    }

    // Add to the linked list
    newDepartment->next = departments;
    departments = newDepartment;
    departmentCount++;

    printf("Department added successfully!\n");
}

void viewDepartments() {
    if (departmentCount == 0) {
        printf("No departments available.\n");
        return;
    }

    printf("\n--- All Departments ---\n");
    printf("%-30s %-15s %-15s\n", "Department", "Employees", "Avg Salary");
    printf("---------------------------------------------------------\n");

    Department* current = departments;
    while (current != NULL) {
        float avgSalary = 0.0;
        if (current->employeeCount > 0) {
            avgSalary = current->totalSalary / current->employeeCount;
        }

        printf("%-30s %-15d $%-14.2f\n",
               current->name,
               current->employeeCount,
               avgSalary);

        current = current->next;
    }
}

void deleteDepartment() {
    if (departmentCount == 0) {
        printf("No departments available to delete.\n");
        return;
    }

    char deptName[DEPT_LENGTH];

    // Display available departments
    printf("\n--- Delete Department ---\n");
    printf("Available Departments:\n");
    Department* current = departments;
    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }

    printf("\nEnter Department Name to delete: ");
    fgets(deptName, DEPT_LENGTH, stdin);
    deptName[strcspn(deptName, "\n")] = '\0';

    Department* prev = NULL;
    current = departments;
    while (current != NULL) {
        char lowerDept1[DEPT_LENGTH], lowerDept2[DEPT_LENGTH];
        strcpy(lowerDept1, current->name);
        strcpy(lowerDept2, deptName);
        toLowerString(lowerDept1);
        toLowerString(lowerDept2);

        if (strcmp(lowerDept1, lowerDept2) == 0) {
            // Check if department has active employees
            Employee* empCurrent = employees;
            while (empCurrent != NULL) {
                if (empCurrent->active && strcmp(empCurrent->department, current->name) == 0) {
                    printf("Cannot delete department with active employees.\n");
                    return;
                }
                empCurrent = empCurrent->next;
            }

            printf("Are you sure you want to delete the %s department? (y/n): ", current->name);
            char confirm;
            scanf("%c", &confirm);
            getchar(); // consume newline

            if (confirm == 'y' || confirm == 'Y') {
                if (prev == NULL) {
                    departments = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current);
                departmentCount--;
                printf("Department deleted successfully!\n");
            } else {
                printf("Deletion cancelled.\n");
            }
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Department not found.\n");
}

void updateDepartmentStats() {
    // Reset all department stats
    Department* deptCurrent = departments;
    while (deptCurrent != NULL) {
        deptCurrent->employeeCount = 0;
        deptCurrent->totalSalary = 0.0;
        deptCurrent = deptCurrent->next;
    }

    // Recalculate based on active employees
    Employee* empCurrent = employees;
    while (empCurrent != NULL) {
        if (empCurrent->active) {
            deptCurrent = departments;
            while (deptCurrent != NULL) {
                char lowerDept1[DEPT_LENGTH], lowerDept2[DEPT_LENGTH];
                strcpy(lowerDept1, empCurrent->department);
                strcpy(lowerDept2, deptCurrent->name);
                toLowerString(lowerDept1);
                toLowerString(lowerDept2);

                if (strcmp(lowerDept1, lowerDept2) == 0) {
                    deptCurrent->employeeCount++;
                    deptCurrent->totalSalary += empCurrent->salary;
                    break;
                }
                deptCurrent = deptCurrent->next;
            }
        }
        empCurrent = empCurrent->next;
    }
}

int isDepartmentExists(const char *deptName) {
    char lowerDeptName[DEPT_LENGTH];
    strcpy(lowerDeptName, deptName);
    toLowerString(lowerDeptName);

    Department* current = departments;
    while (current != NULL) {
        char lowerStoredDept[DEPT_LENGTH];
        strcpy(lowerStoredDept, current->name);
        toLowerString(lowerStoredDept);

        if (strcmp(lowerDeptName, lowerStoredDept) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}