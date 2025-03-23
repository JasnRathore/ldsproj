#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"
#include "department.h"

// Global variables for employees
Employee* employees = NULL; // Head of the linked list
int employeeCount = 0;

void addEmployee() {
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Error: Maximum employee limit reached!\n");
        return;
    }

    if (departmentCount == 0) {
        printf("Error: No departments available. Please add a department first.\n");
        return;
    }

    Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
    if (newEmployee == NULL) {
        printf("Error: Memory allocation failed!\n");
        return;
    }

    newEmployee->active = 1;
    newEmployee->next = NULL;

    printf("\n--- Add New Employee ---\n");
    printf("Enter ID: ");
    fgets(newEmployee->id, ID_LENGTH, stdin);
    newEmployee->id[strcspn(newEmployee->id, "\n")] = '\0'; // Remove newline

    // Check if ID already exists
    Employee* current = employees;
    while (current != NULL) {
        if (current->active && strcmp(current->id, newEmployee->id) == 0) {
            printf("Error: Employee ID already exists!\n");
            free(newEmployee);
            return;
        }
        current = current->next;
    }

    printf("Enter Name: ");
    fgets(newEmployee->name, NAME_LENGTH, stdin);
    newEmployee->name[strcspn(newEmployee->name, "\n")] = '\0';

    // Display available departments
    printf("\nAvailable Departments:\n");
    Department* deptCurrent = departments;
    while (deptCurrent != NULL) {
        printf("%s\n", deptCurrent->name);
        deptCurrent = deptCurrent->next;
    }

    int validDept = 0;
    while (!validDept) {
        printf("\nEnter Department: ");
        fgets(newEmployee->department, DEPT_LENGTH, stdin);
        newEmployee->department[strcspn(newEmployee->department, "\n")] = '\0';

        // Check if department exists
        if (isDepartmentExists(newEmployee->department)) {
            validDept = 1;
        } else {
            printf("Error: Department does not exist! Please enter a valid department.\n");
        }
    }

    printf("Enter Salary: ");
    scanf("%f", &newEmployee->salary);
    getchar(); // consume newline

    // Add to the linked list
    newEmployee->next = employees;
    employees = newEmployee;
    employeeCount++;

    updateDepartmentStats();
    printf("Employee added successfully!\n");
}

void displayAllEmployees() {
    int found = 0;

    printf("\n--- All Employees ---\n");
    printf("%-10s %-30s %-20s %-10s\n", "ID", "Name", "Department", "Salary");
    printf("------------------------------------------------------------------\n");

    Employee* current = employees;
    while (current != NULL) {
        if (current->active) {
            printf("%-10s %-30s %-20s $%.2f\n",
                   current->id,
                   current->name,
                   current->department,
                   current->salary);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No employees found.\n");
    }
}

void filterByDepartment() {
    if (departmentCount == 0) {
        printf("No departments available.\n");
        return;
    }

    char deptName[DEPT_LENGTH];
    int found = 0;

    // Display available departments
    printf("\nAvailable Departments:\n");
    Department* deptCurrent = departments;
    while (deptCurrent != NULL) {
        printf("%s\n", deptCurrent->name);
        deptCurrent = deptCurrent->next;
    }

    printf("\nEnter Department to filter by: ");
    fgets(deptName, DEPT_LENGTH, stdin);
    deptName[strcspn(deptName, "\n")] = '\0';

    printf("\n--- Employees in %s Department ---\n", deptName);
    printf("%-10s %-30s %-20s %-10s\n", "ID", "Name", "Department", "Salary");
    printf("------------------------------------------------------------------\n");

    Employee* current = employees;
    while (current != NULL) {
        if (current->active) {
            char lowerDept1[DEPT_LENGTH], lowerDept2[DEPT_LENGTH];
            strcpy(lowerDept1, current->department);
            strcpy(lowerDept2, deptName);
            toLowerString(lowerDept1);
            toLowerString(lowerDept2);

            if (strcmp(lowerDept1, lowerDept2) == 0) {
                printf("%-10s %-30s %-20s $%.2f\n",
                       current->id,
                       current->name,
                       current->department,
                       current->salary);
                found = 1;
            }
        }
        current = current->next;
    }

    if (!found) {
        printf("No employees found in the %s department.\n", deptName);
    }
}

void searchEmployee() {
    char searchId[ID_LENGTH];
    int found = 0;

    printf("\n--- Search Employee ---\n");
    printf("Enter Employee ID to search: ");
    fgets(searchId, ID_LENGTH, stdin);
    searchId[strcspn(searchId, "\n")] = '\0';

    Employee* current = employees;
    while (current != NULL) {
        if (current->active && strcmp(current->id, searchId) == 0) {
            printf("\nEmployee Found:\n");
            printf("ID: %s\n", current->id);
            printf("Name: %s\n", current->name);
            printf("Department: %s\n", current->department);
            printf("Salary: $%.2f\n", current->salary);
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("Employee with ID %s not found.\n", searchId);
    }
}

void updateEmployee() {
    char searchId[ID_LENGTH];
    int found = 0;

    printf("\n--- Update Employee ---\n");
    printf("Enter Employee ID to update: ");
    fgets(searchId, ID_LENGTH, stdin);
    searchId[strcspn(searchId, "\n")] = '\0';

    Employee* current = employees;
    while (current != NULL) {
        if (current->active && strcmp(current->id, searchId) == 0) {
            printf("\nCurrent Details:\n");
            printf("ID: %s\n", current->id);
            printf("Name: %s\n", current->name);
            printf("Department: %s\n", current->department);
            printf("Salary: $%.2f\n\n", current->salary);

            printf("Enter new Name (or press Enter to keep current): ");
            char buffer[NAME_LENGTH];
            fgets(buffer, NAME_LENGTH, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strlen(buffer) > 0) {
                strcpy(current->name, buffer);
            }

            // Display available departments
            printf("\nAvailable Departments:\n");
            Department* deptCurrent = departments;
            while (deptCurrent != NULL) {
                printf("%s\n", deptCurrent->name);
                deptCurrent = deptCurrent->next;
            }

            printf("\nEnter new Department (or press Enter to keep current): ");
            fgets(buffer, DEPT_LENGTH, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strlen(buffer) > 0) {
                if (isDepartmentExists(buffer)) {
                    strcpy(current->department, buffer);
                } else {
                    printf("Department does not exist. Keeping current department.\n");
                }
            }

            printf("Enter new Salary (or 0 to keep current): ");
            float newSalary;
            scanf("%f", &newSalary);
            getchar(); // consume newline
            if (newSalary > 0) {
                current->salary = newSalary;
            }

            updateDepartmentStats();
            printf("Employee updated successfully!\n");
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("Employee with ID %s not found.\n", searchId);
    }
}

void deleteEmployee() {
    char searchId[ID_LENGTH];
    int found = 0;

    printf("\n--- Delete Employee ---\n");
    printf("Enter Employee ID to delete: ");
    fgets(searchId, ID_LENGTH, stdin);
    searchId[strcspn(searchId, "\n")] = '\0';

    Employee* prev = NULL;
    Employee* current = employees;
    while (current != NULL) {
        if (current->active && strcmp(current->id, searchId) == 0) {
            printf("Are you sure you want to delete employee %s? (y/n): ", current->name);
            char confirm;
            scanf("%c", &confirm);
            getchar(); // consume newline

            if (confirm == 'y' || confirm == 'Y') {
                current->active = 0; // Mark as deleted
                updateDepartmentStats();
                printf("Employee deleted successfully!\n");
            } else {
                printf("Deletion cancelled.\n");
            }

            found = 1;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!found) {
        printf("Employee with ID %s not found.\n", searchId);
    }
}