#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "department.h"
#include "filehandler.h"

void displayMainMenu() {
    system("cls");
    printf("\n=== EMPLOYEE RECORD MANAGEMENT SYSTEM ===\n");
    printf("1. Add Employee\n");
    printf("2. Display All Employees\n");
    printf("3. Filter Employees by Department\n");
    printf("4. Search Employee\n");
    printf("5. Update Employee\n");
    printf("6. Delete Employee\n");
    printf("7. Department Management\n");
    printf("8. File Operations\n");
    printf("9. Exit\n");
}

void departmentMenu() {
    int choice;
    
    while (1) {
        system("cls");
        printf("\n=== DEPARTMENT MANAGEMENT ===\n");
        printf("1. Add Department\n");
        printf("2. View All Departments\n");
        printf("3. Delete Department\n");
        printf("4. Return to Main Menu\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline
        
        switch (choice) {
            case 1:
                addDepartment();
                break;
            case 2:
                viewDepartments();
                break;
            case 3:
                deleteDepartment();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
    }
}

void fileMenu() {
    int choice;
    
    while (1) {
        system("cls"); 
        printf("\n=== FILE OPERATIONS ===\n");
        printf("1. Save Data\n");
        printf("2. Export to CSV\n");
        printf("3. Import from CSV\n");
        printf("4. Backup Data\n");
        printf("5. Restore Data\n");
        printf("6. Return to Main Menu\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline
        
        switch (choice) {
            case 1:
                saveEmployeesToFile();
                saveDepartmentsToFile();
                printf("Data saved successfully!\n");
                break;
            case 2:
                exportToCSV();
                break;
            case 3:
                importFromCSV();
                break;
            case 4:
                backupData();
                break;
            case 5:
                restoreData();
                break;
            case 6:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
    }
}
