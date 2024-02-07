#include <iostream>
#include <string>
#include <unistd.h>

#define ADMIN_PASSWORD "admin123"

// Structure to represent a bank account
struct Account {
    int accountNumber;
    std::string holderName;
    double balance;
};

// Function to display the main menu
void displayMenu() {
    std::cout << "\n===== Bank Management System =====\n";
    std::cout << "1. Admin Login\n";
    std::cout << "2. Create Account\n";
    std::cout << "3. View Account Details\n";
    std::cout << "4. Deposit\n";
    std::cout << "5. Withdraw\n";
    std::cout << "6. Exit\n";
    std::cout << "==================================\n";
}

// Function to validate admin password
bool adminLogin() {
    std::string password;
    std::cout << "\nEnter Admin Password: ";
    std::cin >> password;

    if (password == ADMIN_PASSWORD) {
        return true; // Successful login
    } else {
        std::cout << "Incorrect Password. Access Denied!\n";
        return false; // Failed login
    }
}

// Function to display a loading screen
void showLoadingScreen() {
    std::cout << "\nLoading";
    for (int i = 0; i < 3; ++i) {
        std::cout << ".";
        std::cout.flush();
        usleep(1000000);  // Sleep for 1 second
    }
    std::cout << std::endl;
}

// Function to create a new account
void createAccount(Account accounts[], int& numAccounts) {
    std::cout << "\nEnter Account Holder Name: ";
    std::cin >> accounts[numAccounts].holderName;
    accounts[numAccounts].accountNumber = numAccounts + 1;
    accounts[numAccounts].balance = 0.0;

    // Display account details
    std::cout << "\nAccount Created Successfully!\n";
    std::cout << "Account Number: " << accounts[numAccounts].accountNumber << std::endl;
    std::cout << "Account Holder: " << accounts[numAccounts].holderName << std::endl;
    std::cout << "Balance: $" << accounts[numAccounts].balance << std::endl;

    // Ask for confirmation
    char confirm;
    std::cout << "\nDo you want to confirm the account creation? (Y/N): ";
    std::cin >> confirm;

    if (confirm == 'Y' || confirm == 'y') {
        std::cout << "Account Confirmed!\n";
        numAccounts++;
    } else {
        std::cout << "Account Not Confirmed. Rolling back changes.\n";
    }
}

// Function to view account details
void viewAccountDetails(Account accounts[], int numAccounts) {
    std::cout << "\nEnter Account Number: ";
    int accountNumber;
    std::cin >> accountNumber;

    if (accountNumber > 0 && accountNumber <= numAccounts) {
        std::cout << "\nAccount Details:\n";
        std::cout << "Account Number: " << accounts[accountNumber - 1].accountNumber << std::endl;
        std::cout << "Account Holder: " << accounts[accountNumber - 1].holderName << std::endl;
        std::cout << "Balance: $" << accounts[accountNumber - 1].balance << std::endl;
    } else {
        std::cout << "Invalid Account Number!\n";
    }
}

// Function to deposit into an account
void deposit(Account accounts[], int numAccounts) {
    std::cout << "\nEnter Account Number: ";
    int accountNumber;
    std::cin >> accountNumber;

    if (accountNumber > 0 && accountNumber <= numAccounts) {
        std::cout << "Enter Deposit Amount: $";
        double amount;
        std::cin >> amount;
        accounts[accountNumber - 1].balance += amount;
        std::cout << "Deposit Successful! New Balance: $" << accounts[accountNumber - 1].balance << std::endl;
    } else {
        std::cout << "Invalid Account Number!\n";
    }
}

// Function to withdraw from an account
void withdraw(Account accounts[], int numAccounts) {
    std::cout << "\nEnter Account Number: ";
    int accountNumber;
    std::cin >> accountNumber;

    if (accountNumber > 0 && accountNumber <= numAccounts) {
        std::cout << "Enter Withdrawal Amount: $";
        double amount;
        std::cin >> amount;

        if (amount <= accounts[accountNumber - 1].balance) {
            accounts[accountNumber - 1].balance -= amount;
            std::cout << "Withdrawal Successful! New Balance: $" << accounts[accountNumber - 1].balance << std::endl;
        } else {
            std::cout << "Insufficient Funds!\n";
        }
    } else {
        std::cout << "Invalid Account Number!\n";
    }
}

int main() {
    Account accounts[10];
    int numAccounts = 0;
    int choice;

    do {
        displayMenu();
        std::cout << "Enter your choice (1-6): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (adminLogin()) {
                    std::cout << "Admin Login;
                if (adminLogin()) {
                    std::cout << "Admin Login Successful!\n";
                    showLoadingScreen();
                }
                break;
            case 2:
                createAccount(accounts, numAccounts);
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
                std::cout << "Exiting Bank Management System. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 6);

    return 0;
}

