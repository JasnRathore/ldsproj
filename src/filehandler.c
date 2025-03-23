#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filehandler.h"
#include "common.h"
#include "employee.h"
#include "department.h"

// File paths
char employeeFilePath[FILE_PATH_LENGTH] = "employees.dat";
char departmentFilePath[FILE_PATH_LENGTH] = "departments.dat";

void saveEmployeesToFile() {
    FILE* file = fopen(employeeFilePath, "wb");
    if (file == NULL) {
        printf("Error opening employee file for writing!\n");
        return;
    }

    fwrite(&employeeCount, sizeof(int), 1, file);

    Employee* current = employees;
    while (current != NULL) {
        fwrite(current, sizeof(Employee), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Employee data saved successfully.\n");
}

void loadEmployeesFromFile() {
    FILE* file = fopen(employeeFilePath, "rb");
    if (file == NULL) {
        // File doesn't exist yet, not an error
        return;
    }

    fread(&employeeCount, sizeof(int), 1, file);

    Employee* prev = NULL;
    for (int i = 0; i < employeeCount; i++) {
        Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
        fread(newEmployee, sizeof(Employee), 1, file);
        newEmployee->next = NULL;

        if (prev == NULL) {
            employees = newEmployee;
        } else {
            prev->next = newEmployee;
        }
        prev = newEmployee;
    }

    fclose(file);
}

void saveDepartmentsToFile() {
    FILE* file = fopen(departmentFilePath, "wb");
    if (file == NULL) {
        printf("Error opening department file for writing!\n");
        return;
    }

    fwrite(&departmentCount, sizeof(int), 1, file);

    Department* current = departments;
    while (current != NULL) {
        fwrite(current, sizeof(Department), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Department data saved successfully.\n");
}

void loadDepartmentsFromFile() {
    FILE* file = fopen(departmentFilePath, "rb");
    if (file == NULL) {
        // File doesn't exist yet, not an error
        return;
    }

    fread(&departmentCount, sizeof(int), 1, file);

    Department* prev = NULL;
    for (int i = 0; i < departmentCount; i++) {
        Department* newDepartment = (Department*)malloc(sizeof(Department));
        fread(newDepartment, sizeof(Department), 1, file);
        newDepartment->next = NULL;

        if (prev == NULL) {
            departments = newDepartment;
        } else {
            prev->next = newDepartment;
        }
        prev = newDepartment;
    }

    fclose(file);
}

void exportToCSV() {
    char filename[FILE_PATH_LENGTH];

    printf("\n--- Export to CSV ---\n");
    printf("Enter CSV filename (e.g., employees.csv): ");
    fgets(filename, FILE_PATH_LENGTH, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating CSV file!\n");
        return;
    }

    // Write header
    fprintf(file, "ID,Name,Department,Salary,Status\n");

    // Write employee data
    Employee* current = employees;
    while (current != NULL) {
        fprintf(file, "%s,%s,%s,%.2f,%s\n",
                current->id,
                current->name,
                current->department,
                current->salary,
                current->active ? "Active" : "Inactive");
        current = current->next;
    }

    fclose(file);
    printf("Data exported to %s successfully.\n", filename);
}

void importFromCSV() {
    char filename[FILE_PATH_LENGTH];
    char line[200];
    char* token;
    const char delimiter[] = ",";

    printf("\n--- Import from CSV ---\n");
    printf("Enter CSV filename to import: ");
    fgets(filename, FILE_PATH_LENGTH, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening CSV file!\n");
        return;
    }

    // Skip header line
    fgets(line, sizeof(line), file);

    // Reset employee count before import
    employeeCount = 0;

    // Read data lines
    while (fgets(line, sizeof(line), file) && employeeCount < MAX_EMPLOYEES) {
        Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
        newEmployee->active = 1;
        newEmployee->next = NULL;

        // Parse CSV line
        token = strtok(line, delimiter);
        if (token) strcpy(newEmployee->id, token);

        token = strtok(NULL, delimiter);
        if (token) strcpy(newEmployee->name, token);

        token = strtok(NULL, delimiter);
        if (token) {
            strcpy(newEmployee->department, token);
            // Check if department exists, create if not
            if (!isDepartmentExists(newEmployee->department) && departmentCount < MAX_DEPARTMENTS) {
                Department* newDepartment = (Department*)malloc(sizeof(Department));
                strcpy(newDepartment->name, newEmployee->department);
                newDepartment->employeeCount = 0;
                newDepartment->totalSalary = 0.0;
                newDepartment->next = departments;
                departments = newDepartment;
                departmentCount++;
            }
        }

        token = strtok(NULL, delimiter);
        if (token) newEmployee->salary = atof(token);

        token = strtok(NULL, delimiter);
        if (token) {
            if (strcmp(token, "Active\n") == 0 || strcmp(token, "Active") == 0) {
                newEmployee->active = 1;
            } else {
                newEmployee->active = 0;
            }
        }

        // Add to the linked list
        newEmployee->next = employees;
        employees = newEmployee;
        employeeCount++;
    }

    fclose(file);
    updateDepartmentStats();
    printf("Imported %d employees from %s.\n", employeeCount, filename);
}

void backupData() {
    char backupDir[FILE_PATH_LENGTH];
    char empBackup[FILE_PATH_LENGTH];
    char deptBackup[FILE_PATH_LENGTH];

    printf("\n--- Backup Data ---\n");
    printf("Enter backup directory path: ");
    fgets(backupDir, FILE_PATH_LENGTH, stdin);
    backupDir[strcspn(backupDir, "\n")] = '\0';

    // Remove trailing slash if present
    int len = strlen(backupDir);
    if (len > 0 && backupDir[len - 1] == '/') {
        backupDir[len - 1] = '\0';
    }

    // Construct backup file paths
    snprintf(empBackup, FILE_PATH_LENGTH, "%s/employees_backup.dat", backupDir);
    snprintf(deptBackup, FILE_PATH_LENGTH, "%s/departments_backup.dat", backupDir);

    // Backup employee data
    FILE* empFile = fopen(employeeFilePath, "rb");
    FILE* empBackupFile = fopen(empBackup, "wb");

    if (empFile == NULL || empBackupFile == NULL) {
        printf("Error: Unable to create employee backup!\n");
        return;
    }

    int ch;
    while ((ch = fgetc(empFile)) != EOF) {
        fputc(ch, empBackupFile);
    }

    fclose(empFile);
    fclose(empBackupFile);

    // Backup department data
    FILE* deptFile = fopen(departmentFilePath, "rb");
    FILE* deptBackupFile = fopen(deptBackup, "wb");

    if (deptFile == NULL || deptBackupFile == NULL) {
        printf("Error: Unable to create department backup!\n");
        return;
    }

    while ((ch = fgetc(deptFile)) != EOF) {
        fputc(ch, deptBackupFile);
    }

    fclose(deptFile);
    fclose(deptBackupFile);

    printf("Backup completed successfully!\n");
}

void restoreData() {
    char backupDir[FILE_PATH_LENGTH];
    char empBackup[FILE_PATH_LENGTH];
    char deptBackup[FILE_PATH_LENGTH];

    printf("\n--- Restore Data ---\n");
    printf("Enter backup directory path: ");
    fgets(backupDir, FILE_PATH_LENGTH, stdin);
    backupDir[strcspn(backupDir, "\n")] = '\0';

    // Construct backup file paths
    snprintf(empBackup, FILE_PATH_LENGTH, "%s/employees_backup.dat", backupDir);
    snprintf(deptBackup, FILE_PATH_LENGTH, "%s/departments_backup.dat", backupDir);

    // Restore employee data
    FILE* empBackupFile = fopen(empBackup, "rb");
    FILE* empFile = fopen(employeeFilePath, "wb");

    if (empBackupFile == NULL || empFile == NULL) {
        printf("Error: Unable to restore employee data!\n");
        return;
    }

    int ch;
    while ((ch = fgetc(empBackupFile)) != EOF) {
        fputc(ch, empFile);
    }

    fclose(empBackupFile);
    fclose(empFile);

    // Restore department data
    FILE* deptBackupFile = fopen(deptBackup, "rb");
    FILE* deptFile = fopen(departmentFilePath, "wb");

    if (deptBackupFile == NULL || deptFile == NULL) {
        printf("Error: Unable to restore department data!\n");
        return;
    }

    while ((ch = fgetc(deptBackupFile)) != EOF) {
        fputc(ch, deptFile);
    }

    fclose(deptBackupFile);
    fclose(deptFile);

    printf("Data restored successfully!\n");
}