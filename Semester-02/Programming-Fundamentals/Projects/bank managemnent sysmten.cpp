#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Account
{
    int accountNumber;
    char name[50];
    float balance;
};

struct Account accounts[100];
int totalAccounts = 0;


// Function to check duplicate account number
int checkAccountNumber(int accNo)
{
    for(int i = 0; i < totalAccounts; i++)
    {
        if(accounts[i].accountNumber == accNo)
        {
            return 1;   // Duplicate account number
        }
    }

    return 0;   // Account number is unique
}


// Function to validate name
int validateName(char name[])
{
    for(int i = 0; name[i] != '\0'; i++)
    {
        if(!isalpha(name[i]) && name[i] != ' ')
        {
            return 0;
        }
    }

    return 1;
}


// Function to find account index
int findAccount(int accNo)
{
    for(int i = 0; i < totalAccounts; i++)
    {
        if(accounts[i].accountNumber == accNo)
        {
            return i;
        }
    }

    return -1;
}


// Create Account
void createAccount()
{
    int accNo;

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);


    if(checkAccountNumber(accNo))
    {
        printf("\nAccount Number Already Exists!");
        return;
    }


    accounts[totalAccounts].accountNumber = accNo;


    while(1)
    {
        printf("Enter Account Holder Name: ");
        scanf(" %[^\n]", accounts[totalAccounts].name);


        if(validateName(accounts[totalAccounts].name))
        {
            break;
        }
        else
        {
            printf("\nInvalid Name! Use alphabets only.\n");
        }
    }


    printf("Enter Initial Deposit: ");
    scanf("%f", &accounts[totalAccounts].balance);


    totalAccounts++;

    printf("\nAccount Created Successfully!\n");
}


// Display Account
void displayAccount()
{
    int accNo;

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);


    int index = findAccount(accNo);


    if(index == -1)
    {
        printf("\nAccount Not Found!");
        return;
    }


    printf("\n----- Account Details -----");
    printf("\nAccount Number: %d", accounts[index].accountNumber);
    printf("\nAccount Holder: %s", accounts[index].name);
    printf("\nBalance: %.2f", accounts[index].balance);
}


// Deposit Money
void deposit()
{
    int accNo;
    float amount;


    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);


    int index = findAccount(accNo);


    if(index == -1)
    {
        printf("\nAccount Not Found!");
        return;
    }


    printf("Enter Deposit Amount: ");
    scanf("%f", &amount);


    if(amount <= 0)
    {
        printf("\nInvalid Amount!");
        return;
    }


    accounts[index].balance += amount;


    printf("\nDeposit Successful!");
    printf("\nUpdated Balance: %.2f", accounts[index].balance);
}


// Withdraw Money
void withdraw()
{
    int accNo;
    float amount;


    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);


    int index = findAccount(accNo);


    if(index == -1)
    {
        printf("\nAccount Not Found!");
        return;
    }


    printf("Enter Withdrawal Amount: ");
    scanf("%f", &amount);


    if(amount <= 0)
    {
        printf("\nInvalid Amount!");
        return;
    }


    if(amount > accounts[index].balance)
    {
        printf("\nInsufficient Balance!");
    }
    else
    {
        accounts[index].balance -= amount;

        printf("\nWithdrawal Successful!");
        printf("\nRemaining Balance: %.2f",
               accounts[index].balance);
    }
}


// Main Function
int main()
{
    int choice;


    while(1)
    {
        printf("\n\n========== BANK MANAGEMENT SYSTEM ==========");
        printf("\n1. Create Account");
        printf("\n2. Display Account Details");
        printf("\n3. Deposit Money");
        printf("\n4. Withdraw Money");
        printf("\n5. Exit");


        printf("\n\nEnter Your Choice: ");
        scanf("%d", &choice);


        switch(choice)
        {
            case 1:
                createAccount();
                break;


            case 2:
                displayAccount();
                break;


            case 3:
                deposit();
                break;


            case 4:
                withdraw();
                break;


            case 5:
                printf("\nThank You For Using Bank Management System!");
                return 0;


            default:
                printf("\nInvalid Choice! Try Again.");
        }
    }


    return 0;
}