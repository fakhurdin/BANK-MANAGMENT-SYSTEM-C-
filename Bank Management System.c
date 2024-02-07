#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ADMIN_PASSWORD "admin123"

// Structure to represent a bank account
struct Account {
    int accountNumber;
    char holderName[50];
    double balance;
};

// Function to display the main menu
void displayMenu() {
    printf("\n===== Bank Management System =====\n");
    printf("1. Admin Login\n");
    printf("2. Create Account\n");
    printf("3. View Account Details\n");
    printf("4. Deposit\n");
    printf("5. Withdraw\n");
    printf("6. Exit\n");
    printf("==================================\n");
}

// Function to validate admin password
int adminLogin() {
    char password[20];
    printf("\nEnter Admin Password: ");
    scanf("%s", password);

    if (strcmp(password, ADMIN_PASSWORD) == 0) {
        return 1; // Successful login
    } else {
        printf("Incorrect Password. Access Denied!\n");
        return 0; // Failed login
    }
}

// Function to display a loading screen
void showLoadingScreen() {
    printf("\nLoading");
    for (int i = 0; i < 3; ++i) {
        printf(".");
        fflush(stdout);
        usleep(1000000);  // Sleep for 1 second
    }
    printf("\n");
}

// Function to create a new account
void createAccount(struct Account *accounts, int *numAccounts) {
    printf("\nEnter Account Holder Name: ");
    scanf("%s", accounts[*numAccounts].holderName);
    accounts[*numAccounts].accountNumber = *numAccounts + 1;
    accounts[*numAccounts].balance = 0.0;

    // Display account details
    printf("\nAccount Created Successfully!\n");
    printf("Account Number: %d\n", accounts[*numAccounts].accountNumber);
    printf("Account Holder: %s\n", accounts[*numAccounts].holderName);
    printf("Balance: $%.2lf\n", accounts[*numAccounts].balance);

    // Ask for confirmation
    char confirm;
    printf("\nDo you want to confirm the account creation? (Y/N): ");
    scanf(" %c", &confirm);

    if (confirm == 'Y' || confirm == 'y') {
        printf("Account Confirmed!\n");
        (*numAccounts)++;
    } else {
        printf("Account Not Confirmed. Rolling back changes.\n");
    }
}

// Function to view account details
void viewAccountDetails(struct Account *accounts, int numAccounts) {
    printf("\nEnter Account Number: ");
    int accountNumber;
    scanf("%d", &accountNumber);

    if (accountNumber > 0 && accountNumber <= numAccounts) {
        printf("\nAccount Details:\n");
        printf("Account Number: %d\n", accounts[accountNumber - 1].accountNumber);
        printf("Account Holder: %s\n", accounts[accountNumber - 1].holderName);
        printf("Balance: $%.2lf\n", accounts[accountNumber - 1].balance);
    } else {
        printf("Invalid Account Number!\n");
    }
}

// Function to deposit into an account
void deposit(struct Account *accounts, int numAccounts) {
    printf("\nEnter Account Number: ");
    int accountNumber;
    scanf("%d", &accountNumber);

    if (accountNumber > 0 && accountNumber <= numAccounts) {
        printf("Enter Deposit Amount: $");
        double amount;
        scanf("%lf", &amount);
        accounts[accountNumber - 1].balance += amount;
        printf("Deposit Successful! New Balance: $%.2lf\n", accounts[accountNumber - 1].balance);
    } else {
        printf("Invalid Account Number!\n");
    }
}

// Function to withdraw from an account
void withdraw(struct Account *accounts, int numAccounts) {
    printf("\nEnter Account Number: ");
    int accountNumber;
    scanf("%d", &accountNumber);

    if (accountNumber > 0 && accountNumber <= numAccounts) {
        printf("Enter Withdrawal Amount: $");
        double amount;
        scanf("%lf", &amount);

        if (amount <= accounts[accountNumber - 1].balance) {
            accounts[accountNumber - 1].balance -= amount;
            printf("Withdrawal Successful! New Balance: $%.2lf\n", accounts[accountNumber - 1].balance);
        } else {
            printf("Insufficient Funds!\n");
        }
    } else {
        printf("Invalid Account Number!\n");
    }
}

int main() {
    struct Account accounts[10];
    int numAccounts = 0;
    int choice;

    do {
        displayMenu();
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (adminLogin()) {
                    printf("Admin Login Successful!\n");
                    showLoadingScreen();
                }
                break;
            case 2:
                createAccount(accounts, &numAccounts);
                break;
            case 3:
                viewAccountDetails(accounts, numAccounts);
                break;
            case 4:
                deposit(accounts, numAccounts);
                break;
            case 5:
                withdraw(accounts, numAccounts);
                break;
            case 6:
                printf("Exiting Bank Management System. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 6);

    return 0;
}
