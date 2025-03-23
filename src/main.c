#include <stdio.h>
#include <stdlib.h>
#include "employee.h"
#include "department.h"
#include "filehandler.h"
#include "ui.h"

int main() {
    int choice;
    
    // Load existing records if any
    loadEmployeesFromFile();
    loadDepartmentsFromFile();
    
    while (1) {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline
        
        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayAllEmployees();
                break;
            case 3:
                filterByDepartment();
                break;
            case 4:
                searchEmployee();
                break;
            case 5:
                updateEmployee();
                break;
            case 6:
                deleteEmployee();
                break;
            case 7:
                manageDepartments();
                break;
            case 8:
                fileMenu();
                break;
            case 9:
                printf("Exiting program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
    }
    
    return 0;
}
