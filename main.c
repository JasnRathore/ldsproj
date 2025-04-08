#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NAME_LENGTH 50
#define DEPT_LENGTH 30
#define ID_LENGTH 10

typedef struct Employee {
    char id[ID_LENGTH];
    char name[NAME_LENGTH];
    char department[DEPT_LENGTH];
    float salary;
    struct Employee* next;
} Employee;

Employee* head = NULL;
int employeeCount = 0;

void clearScreen() {
    system("cls");
}

void toLowerString(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void addEmployee() {
    Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
    if (newEmployee == NULL) {
        printf("Error: Memory allocation failed!\n");
        return;
    }

    clearScreen();
    printf("\n--- Add New Employee ---\n");
    
    printf("Enter ID: ");
    fgets(newEmployee->id, ID_LENGTH, stdin);
    newEmployee->id[strcspn(newEmployee->id, "\n")] = '\0';
    
    // Check if ID already exists
    Employee* current = head;
    while (current != NULL) {
        if (strcmp(current->id, newEmployee->id) == 0) {
            printf("Error: Employee ID already exists!\n");
            free(newEmployee);
            return;
        }
        current = current->next;
    }
    
    printf("Enter Name: ");
    fgets(newEmployee->name, NAME_LENGTH, stdin);
    newEmployee->name[strcspn(newEmployee->name, "\n")] = '\0';
    
    printf("Enter Department: ");
    fgets(newEmployee->department, DEPT_LENGTH, stdin);
    newEmployee->department[strcspn(newEmployee->department, "\n")] = '\0';
    
    printf("Enter Salary: ");
    scanf("%f", &newEmployee->salary);
    getchar(); // consume newline
    
    newEmployee->next = head;
    head = newEmployee;
    employeeCount++;
    
    printf("Employee added successfully!\n");
}

void displayAllEmployees() {
    if (head == NULL) {
        printf("No employees available.\n");
        return;
    }

    clearScreen();
    printf("\n--- All Employees ---\n");
    printf("%-10s %-30s %-20s %-10s\n", "ID", "Name", "Department", "Salary");
    printf("---------------------------------------------------------\n");
    
    Employee* current = head;
    while (current != NULL) {
        printf("%-10s %-30s %-20s $%.2f\n",
               current->id,
               current->name,
               current->department,
               current->salary);
        current = current->next;
    }
}

void searchEmployee() {
    char searchId[ID_LENGTH];
    
    clearScreen();
    printf("\n--- Search Employee ---\n");
    printf("Enter Employee ID to search: ");
    fgets(searchId, ID_LENGTH, stdin);
    searchId[strcspn(searchId, "\n")] = '\0';
    
    Employee* current = head;
    while (current != NULL) {
        if (strcmp(current->id, searchId) == 0) {
            printf("\nEmployee Found:\n");
            printf("ID: %s\n", current->id);
            printf("Name: %s\n", current->name);
            printf("Department: %s\n", current->department);
            printf("Salary: $%.2f\n", current->salary);
            return;
        }
        current = current->next;
    }
    
    printf("Employee with ID %s not found.\n", searchId);
}

void updateEmployee() {
    char searchId[ID_LENGTH];
    
    clearScreen();
    printf("\n--- Update Employee ---\n");
    printf("Enter Employee ID to update: ");
    fgets(searchId, ID_LENGTH, stdin);
    searchId[strcspn(searchId, "\n")] = '\0';
    
    Employee* current = head;
    while (current != NULL) {
        if (strcmp(current->id, searchId) == 0) {
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
            
            printf("Enter new Department (or press Enter to keep current): ");
            fgets(buffer, DEPT_LENGTH, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strlen(buffer) > 0) {
                strcpy(current->department, buffer);
            }
            
            printf("Enter new Salary (or 0 to keep current): ");
            float newSalary;
            scanf("%f", &newSalary);
            getchar(); // consume newline
            if (newSalary > 0) {
                current->salary = newSalary;
            }
            
            printf("Employee updated successfully!\n");
            return;
        }
        current = current->next;
    }
    
    printf("Employee with ID %s not found.\n", searchId);
}

void deleteEmployee() {
    char searchId[ID_LENGTH];
    
    clearScreen();
    printf("\n--- Delete Employee ---\n");
    printf("Enter Employee ID to delete: ");
    fgets(searchId, ID_LENGTH, stdin);
    searchId[strcspn(searchId, "\n")] = '\0';
    
    Employee* prev = NULL;
    Employee* current = head;
    
    while (current != NULL) {
        if (strcmp(current->id, searchId) == 0) {
            printf("Are you sure you want to delete employee %s? (y/n): ", current->name);
            char confirm;
            scanf("%c", &confirm);
            getchar(); // consume newline
            
            if (confirm == 'y' || confirm == 'Y') {
                if (prev == NULL) {
                    // Deleting the head
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current);
                employeeCount--;
                printf("Employee deleted successfully!\n");
            } else {
                printf("Deletion cancelled.\n");
            }
            return;
        }
        prev = current;
        current = current->next;
    }
    
    printf("Employee with ID %s not found.\n", searchId);
}

void filterByDepartment() {
    if (head == NULL) {
        printf("No employees available.\n");
        return;
    }

    char deptName[DEPT_LENGTH];
    int found = 0;
    
    clearScreen();
    printf("\n--- Filter by Department ---\n");
    printf("Enter Department to filter by: ");
    fgets(deptName, DEPT_LENGTH, stdin);
    deptName[strcspn(deptName, "\n")] = '\0';
    
    printf("\n--- Employees in %s Department ---\n", deptName);
    printf("%-10s %-30s %-20s %-10s\n", "ID", "Name", "Department", "Salary");
    printf("---------------------------------------------------------\n");
    
    Employee* current = head;
    while (current != NULL) {
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
        current = current->next;
    }
    
    if (!found) {
        printf("No employees found in the %s department.\n", deptName);
    }
}

void saveToFile() {
    FILE* file = fopen("employees.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    
    fwrite(&employeeCount, sizeof(int), 1, file);
    
    Employee* current = head;
    while (current != NULL) {
        fwrite(current, sizeof(Employee), 1, file);
        current = current->next;
    }
    
    fclose(file);
    printf("Employee data saved successfully.\n");
}

void loadFromFile() {
    FILE* file = fopen("employees.dat", "rb");
    if (file == NULL) {
        return; 
    }
    
    // Clear existing list
    Employee* current = head;
    while (current != NULL) {
        Employee* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
    employeeCount = 0;
    
    fread(&employeeCount, sizeof(int), 1, file);
    
    Employee* prev = NULL;
    for (int i = 0; i < employeeCount; i++) {
        Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
        fread(newEmployee, sizeof(Employee), 1, file);
        newEmployee->next = NULL;
        
        if (prev == NULL) {
            head = newEmployee;
        } else {
            prev->next = newEmployee;
        }
        prev = newEmployee;
    }
    
    fclose(file);
}

void displayMainMenu() {
    clearScreen();
    printf("\n=== EMPLOYEE MANAGEMENT SYSTEM ===\n");
    printf("1. Add Employee\n");
    printf("2. Display All Employees\n");
    printf("3. Filter Employees by Department\n");
    printf("4. Search Employee\n");
    printf("5. Update Employee\n");
    printf("6. Delete Employee\n");
    printf("7. Save Data\n");
    printf("8. Exit\n");
}

void freeMemory() {
    Employee* current = head;
    while (current != NULL) {
        Employee* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    int choice;
    
    loadFromFile();
    
    while (1) {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();         
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
                saveToFile();
                break;
            case 8:
                freeMemory();
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