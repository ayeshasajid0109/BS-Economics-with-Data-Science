#include<stdio.h>
#include<stdlib.h>
// Structure to store household data
struct household {
    int id;             // Household ID
    float income;       // Monthly income
    float expense;      // Monthly expense
    float savings;      // Savings
};

// Function prototypes
void inputData(struct household h[], int n);
void displayData(struct household h[], int n);
void averageIncome(struct household h[], int n);
void highestIncome(struct household h[], int n);
void searchHouse(struct household h[], int n);
void saveToFile(struct household h[], int n);
void loadFromFile(struct household h[], int *n);
int isDuplicate(struct household h[], int n, int id);
int main() {
    int n, choice;
    printf("=====================================\n");
    printf(" ECONOMIC SURVEY MANAGEMENT SYSTEM\n");
    printf("=====================================\n");
    printf("Enter number of households: ");
    scanf("%d", &n);
    struct household h[100]; // fixed size for safety
    inputData(h, n);
    do {
        printf("\n========== MENU ==========\n");
        printf("1. Display All Records\n");
        printf("2. Average Income\n");
        printf("3. Highest Income\n");
        printf("4. Search Household\n");
        printf("5. Save Records to File\n");
        printf("6. Load Records from File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: displayData(h, n); break;
            case 2: averageIncome(h, n); break;
            case 3: highestIncome(h, n); break;
            case 4: searchHouse(h, n); break;
            case 5: saveToFile(h, n); break;
            case 6: loadFromFile(h, &n); break;
            case 7: printf("\nProject Ended Successfully!\n"); break;
            default: printf("\nInvalid Choice!\n");
        }
    } while(choice != 7);
    return 0;
}
// Check for duplicate ID
int isDuplicate(struct household h[], int n, int id) {
    for(int i = 0; i < n; i++) {
        if(h[i].id == id) {
            return 1;
        }
    }
    return 0;

// Function for taking household data
void inputData(struct household h[], int n) {
    for(int i = 0; i < n; i++) {
        printf("\nEnter data for household %d\n", i + 1);
        // Household ID validation
        do {
            printf("Enter household ID: ");
            scanf("%d", &h[i].id);
            if(isDuplicate(h, i, h[i].id)) {
                printf("Error: Duplicate ID! Enter again.\n");
            }
        } while(isDuplicate(h, i, h[i].id));
        // Income validation
        do {
            printf("Enter monthly income: ");
            scanf("%f", &h[i].income);
            if(h[i].income < 0) {
                printf("Error: Income cannot be negative!\n");
            }
        } while(h[i].income < 0);
        // Expense validation
        do {
            printf("Enter monthly expense: ");
            scanf("%f", &h[i].expense);
            if(h[i].expense < 0) {
                printf("Error: Expense cannot be negative!\n");
            }
        } while(h[i].expense < 0);
        h[i].savings = h[i].income - h[i].expense;
    }
}
// Function to display all records
void displayData(struct household h[], int n) {
    printf("\n========== ALL RECORDS ==========\n");
    for(int i = 0; i < n; i++) {
        printf("\nHousehold ID: %d", h[i].id);
        printf("\nIncome: %.2f", h[i].income);
        printf("\nExpense: %.2f", h[i].expense);
        printf("\nSavings: %.2f", h[i].savings);
        if(h[i].income < 30000) {
            printf("\nStatus: Below Poverty Line");
        } else {
            printf("\nStatus: Economically Stable");
        }
        printf("\n-----------------------------\n");
    }
}
// Function to calculate average income
void averageIncome(struct household h[], int n) {
    float total = 0, average;
    for(int i = 0; i < n; i++) {
        total += h[i].income;
    }
    average = total / n;
    printf("\nAverage Income = %.2f\n", average);
}
// Function to find highest income household
void highestIncome(struct household h[], int n) {
    float highest = h[0].income;
    int index = 0;
    for(int i = 1; i < n; i++) {
        if(h[i].income > highest) {
            highest = h[i].income;
            index = i;
        }
    }
    printf("\nHighest Income Household\n");
    printf("Household ID: %d", h[index].id);
    printf("\nIncome: %.2f\n", h[index].income);
}
// Function to search household by ID
void searchHouse(struct household h[], int n) {
    int search, found = 0;
    printf("\nEnter household ID to search: ");
    scanf("%d", &search);
    for(int i = 0; i < n; i++) {
        if(search == h[i].id) {
            printf("\nRecord Found!\n");
            printf("Household ID: %d", h[i].id);
            printf("\nIncome: %.2f", h[i].income);
            printf("\nExpense: %.2f", h[i].expense);
            printf("\nSavings: %.2f\n", h[i].savings);
            found = 1;
        }
    }
    if(found == 0) {
        printf("\nRecord Not Found!\n");
    }
}
// Save data to file
void saveToFile(struct household h[], int n) {
    FILE *fp = fopen("households.txt", "w");
    if(fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    for(int i = 0; i < n; i++) {
        fprintf(fp, "%d %.2f %.2f %.2f\n", h[i].id, h[i].income, h[i].expense, h[i].savings);
    }
    fclose(fp);
    printf("Data saved to households.txt successfully!\n");
}
// Load data from file
void loadFromFile(struct household h[], int *n) {
    FILE *fp = fopen("households.txt", "r");
    if(fp == NULL) {
        printf("No saved file found!\n");
        return;
    }
    *n = 0;
    while(fscanf(fp, "%d %f %f %f", &h[*n].id, &h[*n].income, &h[*n].expense, &h[*n].savings) != EOF) {
        (*n)++;
    }
    fclose(fp);
    printf("Data loaded successfully!\n");
}