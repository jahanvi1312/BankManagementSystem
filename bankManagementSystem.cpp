#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;

class Bank {
private:
    static const int MAX_ACCOUNTS = 100;
    int total;
    struct Account {
        string name, accountNumber, address;
        long long contact;
        double balance;
    } accounts[MAX_ACCOUNTS];

    string generateAccountNumber() {
        return "ACC" + to_string(total + 1001);
    }

    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bool isValidName(const string& name) {
        return !name.empty() && name.length() <= 50 && 
               all_of(name.begin(), name.end(), [](char c) { 
                   return isalpha(c) || isspace(c); 
               });
    }

    bool isValidContact(long long contact) {
        return contact >= 1000000000 && contact <= 9999999999;
    }

public:
    Bank() : total(0) {}

    void run();
    void createAccount();
    void showAllAccounts();
    void updateAccount();
    void searchAccount();
    void transaction();
    void deleteAccount();
};

void Bank::run() {
    while (true) {
        cout << "\n===== Bank Management System =====\n";
        cout << "1. Create new account\n";
        cout << "2. View all accounts\n";
        cout << "3. Update account information\n";
        cout << "4. Check account details\n";
        cout << "5. Perform transaction\n";
        cout << "6. Close an account\n";
        cout << "7. Exit\n";
        cout << "Enter your choice (1-7): ";

        int choice;
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1: createAccount(); break;
            case 2: showAllAccounts(); break;
            case 3: updateAccount(); break;
            case 4: searchAccount(); break;
            case 5: transaction(); break;
            case 6: deleteAccount(); break;
            case 7: 
                cout << "Thank you for using the Bank Management System. Goodbye!\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Bank::createAccount() {
    if (total >= MAX_ACCOUNTS) {
        cout << "Error: Maximum number of accounts reached.\n";
        return;
    }

    Account& acc = accounts[total];
    acc.accountNumber = generateAccountNumber();

    cout << "\nCreating new account (Account Number: " << acc.accountNumber << ")\n";

    do {
        cout << "Enter full name: ";
        getline(cin, acc.name);
        if (!isValidName(acc.name)) {
            cout << "Invalid name. Please use only letters and spaces.\n";
        }
    } while (!isValidName(acc.name));

    cout << "Enter address: ";
    getline(cin, acc.address);

    do {
        cout << "Enter contact number (10 digits): ";
        cin >> acc.contact;
        clearInputBuffer();
        if (!isValidContact(acc.contact)) {
            cout << "Invalid contact number. Please enter a 10-digit number.\n";
        }
    } while (!isValidContact(acc.contact));

    do {
        cout << "Enter initial deposit amount: $";
        cin >> acc.balance;
        clearInputBuffer();
        if (acc.balance < 0) {
            cout << "Invalid amount. Please enter a non-negative value.\n";
        }
    } while (acc.balance < 0);

    total++;
    cout << "Account created successfully!\n";
}

void Bank::showAllAccounts() {
    if (total == 0) {
        cout << "No accounts exist in the system.\n";
        return;
    }

    cout << "\n===== All Bank Accounts =====\n";
    cout << left << setw(15) << "Account No." 
         << setw(20) << "Name" 
         << setw(15) << "Balance ($)" 
         << setw(15) << "Contact" << endl;
    cout << string(65, '-') << endl;

    for (int i = 0; i < total; i++) {
        cout << left << setw(15) << accounts[i].accountNumber
             << setw(20) << accounts[i].name
             << setw(15) << fixed << setprecision(2) << accounts[i].balance
             << setw(15) << accounts[i].contact << endl;
    }
}

void Bank::updateAccount() {
    string accNumber;
    cout << "Enter account number to update: ";
    cin >> accNumber;
    clearInputBuffer();

    for (int i = 0; i < total; i++) {
        if (accounts[i].accountNumber == accNumber) {
            cout << "Current details:\n";
            cout << "Name: " << accounts[i].name << endl;
            cout << "Address: " << accounts[i].address << endl;
            cout << "Contact: " << accounts[i].contact << endl;

            do {
                cout << "Enter new name (or press Enter to keep current): ";
                string newName;
                getline(cin, newName);
                if (!newName.empty()) {
                    if (isValidName(newName)) {
                        accounts[i].name = newName;
                    } else {
                        cout << "Invalid name. Please use only letters and spaces.\n";
                        continue;
                    }
                }
                break;
            } while (true);

            cout << "Enter new address (or press Enter to keep current): ";
            string newAddress;
            getline(cin, newAddress);
            if (!newAddress.empty()) {
                accounts[i].address = newAddress;
            }

            do {
                cout << "Enter new contact number (10 digits, or press Enter to keep current): ";
                string newContact;
                getline(cin, newContact);
                if (!newContact.empty()) {
                    long long contact = stoll(newContact);
                    if (isValidContact(contact)) {
                        accounts[i].contact = contact;
                        break;
                    } else {
                        cout << "Invalid contact number. Please enter a 10-digit number.\n";
                    }
                } else {
                    break;
                }
            } while (true);

            cout << "Account updated successfully!\n";
            return;
        }
    }
    cout << "Account not found.\n";
}

void Bank::searchAccount() {
    string accNumber;
    cout << "Enter account number to search: ";
    cin >> accNumber;
    clearInputBuffer();

    for (int i = 0; i < total; i++) {
        if (accounts[i].accountNumber == accNumber) {
            cout << "\nAccount Details:\n";
            cout << "Account Number: " << accounts[i].accountNumber << endl;
            cout << "Name: " << accounts[i].name << endl;
            cout << "Address: " << accounts[i].address << endl;
            cout << "Contact: " << accounts[i].contact << endl;
            cout << "Balance: $" << fixed << setprecision(2) << accounts[i].balance << endl;
            return;
        }
    }
    cout << "Account not found.\n";
}

void Bank::transaction() {
    string accNumber;
    cout << "Enter account number for transaction: ";
    cin >> accNumber;
    clearInputBuffer();

    for (int i = 0; i < total; i++) {
        if (accounts[i].accountNumber == accNumber) {
            cout << "Current balance: $" << fixed << setprecision(2) << accounts[i].balance << endl;
            cout << "1. Deposit\n2. Withdraw\nEnter choice: ";
            int choice;
            cin >> choice;
            clearInputBuffer();

            double amount;
            switch (choice) {
                case 1:
                    cout << "Enter deposit amount: $";
                    cin >> amount;
                    clearInputBuffer();
                    if (amount > 0) {
                        accounts[i].balance += amount;
                        cout << "Deposit successful. New balance: $" << accounts[i].balance << endl;
                    } else {
                        cout << "Invalid amount. Transaction cancelled.\n";
                    }
                    break;
                case 2:
                    cout << "Enter withdrawal amount: $";
                    cin >> amount;
                    clearInputBuffer();
                    if (amount > 0 && amount <= accounts[i].balance) {
                        accounts[i].balance -= amount;
                        cout << "Withdrawal successful. New balance: $" << accounts[i].balance << endl;
                    } else {
                        cout << "Invalid amount or insufficient funds. Transaction cancelled.\n";
                    }
                    break;
                default:
                    cout << "Invalid choice. Transaction cancelled.\n";
            }
            return;
        }
    }
    cout << "Account not found.\n";
}

void Bank::deleteAccount() {
    string accNumber;
    cout << "Enter account number to close: ";
    cin >> accNumber;
    clearInputBuffer();

    for (int i = 0; i < total; i++) {
        if (accounts[i].accountNumber == accNumber) {
            cout << "Are you sure you want to close this account? (y/n): ";
            char confirm;
            cin >> confirm;
            clearInputBuffer();

            if (tolower(confirm) == 'y') {
                for (int j = i; j < total - 1; j++) {
                    accounts[j] = accounts[j + 1];
                }
                total--;
                cout << "Account closed successfully.\n";
            } else {
                cout << "Account closure cancelled.\n";
            }
            return;
        }
    }
    cout << "Account not found.\n";
}

int main() {
    Bank bank;
    bank.run();
    return 0;
}