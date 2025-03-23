#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "common.h"
// File paths
extern char employeeFilePath[FILE_PATH_LENGTH];
extern char departmentFilePath[FILE_PATH_LENGTH];

// Function prototypes for file operations
void saveEmployeesToFile();
void loadEmployeesFromFile();
void saveDepartmentsToFile();
void loadDepartmentsFromFile();
void exportToCSV();
void importFromCSV();
void backupData();
void restoreData();

#endif // FILEHANDLER_H
