#include "CD.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"

int pickAccount();
std::string getName();
int getBalance();
int getaccountNumber();
void SwitchAccountType(BankAccount*& account, int choice, double initialBalance, const std::string& name, int accountNumber);
int printMenu();
void executeChoice(int choice, BankAccount*& account);

int main() {
    int choice;
    std::string name;
    double initialBalance;
    int accountNumber;

    int menuChoice = 0;                 //Menu choice Selection
    BankAccount* account = nullptr;     //Account Pointer

    /* Create Initial Account */
    choice = pickAccount();             //Get Choice
    name = getName();                   //Get Name
    initialBalance = getBalance();      //Get Balance
    accountNumber = getaccountNumber(); //Get accountNumber
    SwitchAccountType(account, choice, initialBalance, name, accountNumber);

    /* Operate Account */
    while (menuChoice != 6) {
        menuChoice = printMenu();
        executeChoice(menuChoice, account);
    }

    delete account;
    return 0;
}

int pickAccount() {
    int choice; //Input variable
    //Print inputs
    std::cout << "\nPick an Account type:\n";
    std::cout << "1. Savings Account\n";
    std::cout << "2. High Interest Savings Account\n";
    std::cout << "3. Certificate of Deposit\n";
    std::cout << "4. Service Charge Checking Account\n";
    std::cout << "5. No Service Charge Checking Account\n";
    std::cout << "6. High Interest Checking Account\n";
    std::cout << "Enter your choice (1-6): ";

    //Error catching
    while (!(std::cin >> choice) || choice < 1 || choice > 6) {
        std::cout << "Invalid choice. Please enter a number between 1 and 6: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n'); 
    }

    return choice;
}

std::string getName() {
    std::string name;
    std::cout << "Enter account holder's name: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, name);
    return name;
}

int getBalance() {
    double initialBalance;
    std::cout << "Enter initial balance: ";
    std::cin >> initialBalance;
    initialBalance = (initialBalance < 0) ? 0 : initialBalance;
    return initialBalance;
}

int getaccountNumber() {
    int accountNumber;
    std::cout << "Enter account number: ";
    std::cin >> accountNumber;
    return accountNumber;
}

void SwitchAccountType(BankAccount*& account, int choice, double initialBalance, const std::string& name, int accountNumber) {
    delete account; //Clear memory
    switch (choice) {   //Create account
        case 1:
            account = new SavingsAccount(initialBalance, name, accountNumber);
            break;
        case 2:
            account = new HighInterestSavings(initialBalance, name, accountNumber);
            break;
        case 3:
            account = new CertificateOfDeposit(initialBalance, name, accountNumber);
            break;
        case 4:
            account = new ServiceChargeChecking(initialBalance, name, accountNumber);
            break;
        case 5:
            account = new NoServiceChargeChecking(initialBalance, name, accountNumber);
            break;
        case 6:
            account = new HighInterestChecking(initialBalance, name, accountNumber);
            break;
    }
}

int printMenu() {
    int choice;
    std::cout << "\n\nMenu Options:\n";
    std::cout << "1. Withdraw\n";
    std::cout << "2. Deposit\n";
    std::cout << "3. Display Account Information\n";
    std::cout << "4. Change Account Type\n";
    std::cout << "5. Create Monthly Statement (Enter Next Month)\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice (1-6): ";

    // Error checking
    while (!(std::cin >> choice) || choice < 1 || choice > 6) {
        std::cout << "Invalid choice. Please enter a number between 1 and 6: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cin.ignore(10000, '\n');

    return choice;
}

void executeChoice(int choice, BankAccount*& account) {
    double amount;

    switch (choice) {
        case 1: // Withdraw
            if (account) {
                std::cout << "Enter amount to withdraw: ";
                while (!(std::cin >> amount) || amount < 0) {
                    std::cout << "Invalid amount. Please enter a non-negative number: ";
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                }
                account->withdraw(amount);
            } else {
                std::cout << "No account selected.\n";
            }
            break;
        case 2: // Deposit
            if (account) {
                std::cout << "Enter amount to deposit: ";
                while (!(std::cin >> amount) || amount < 0) {
                    std::cout << "Invalid amount. Please enter a non-negative number: ";
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                }
                account->deposit(amount);
            } else {
                std::cout << "No account selected.\n";
            }
            break;
        case 3: // Display Account Information
            if (account) {
                account->display();
            } else {
                std::cout << "No account selected.\n";
            }
            break;
        case 4: // Change Account Type
            {
                int newChoice = pickAccount();
                double initialBalance = account->getBalance();
                std::string name = account->getName();
                int accountNumber = account->getAccountNumber();
                SwitchAccountType(account, newChoice, initialBalance, name, accountNumber);
            }
            break;
        case 5: // Create Monthly Statement (Enter Next Month)
            if (account) {
                account->createMonthlyStatement();
            } else {
                std::cout << "No account selected.\n";
            }
            break;
        case 6: // Exit
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
    }
}
