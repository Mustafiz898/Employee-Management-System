#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    float salary;
};

void addEmployee();
void displayEmployees();
void searchEmployee();
void deleteEmployee();

int main() {
    int choice;

    while (1) {
        printf("\n===== Employee Management System =====\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: deleteEmployee(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

void addEmployee() {
    FILE *fp = fopen("employee.txt", "a");
    struct Employee e;

    printf("Enter Employee ID: ");
    scanf("%d", &e.id);
    printf("Enter Name: ");
    scanf("%s", e.name);
    printf("Enter Salary: ");
    scanf("%f", &e.salary);

    fprintf(fp, "%d %s %.2f\n", e.id, e.name, e.salary);
    fclose(fp);

    printf("Employee added successfully!\n");
}

void displayEmployees() {
    FILE *fp = fopen("employee.txt", "r");
    struct Employee e;

    if (fp == NULL) {
        printf("No data found!\n");
        return;
    }

    printf("\n===== Employee List =====\n");
    while (fscanf(fp, "%d %s %f", &e.id, e.name, &e.salary) != EOF) {
        printf("ID: %d | Name: %s | Salary: %.2f\n", e.id, e.name, e.salary);
    }

    fclose(fp);
}

void searchEmployee() {
    FILE *fp = fopen("employee.txt", "r");
    struct Employee e;
    int id, found = 0;

    if (fp == NULL) {
        printf("No data found!\n");
        return;
    }

    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %f", &e.id, e.name, &e.salary) != EOF) {
        if (e.id == id) {
            printf("Employee Found!\n");
            printf("ID: %d | Name: %s | Salary: %.2f\n", e.id, e.name, e.salary);
            found = 1;
            break;
        }
    }

    if (!found) printf("Employee not found!\n");

    fclose(fp);
}

void deleteEmployee() {
    FILE *fp = fopen("employee.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Employee e;
    int id, found = 0;

    if (fp == NULL) {
        printf("No data found!\n");
        return;
    }

    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %f", &e.id, e.name, &e.salary) != EOF) {
        if (e.id != id) {
            fprintf(temp, "%d %s %.2f\n", e.id, e.name, e.salary);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("employee.txt");
    rename("temp.txt", "employee.txt");

    if (found)
        printf("Employee deleted successfully!\n");
    else
        printf("Employee not found!\n");
}
