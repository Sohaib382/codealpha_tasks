#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Transaction {
public:
    string type;
    double amount;
    string date;
    int fromAccount;  // For transfers
    int toAccount;    // For transfers

    Transaction() {
        type = "";
        amount = 0.0;
        fromAccount = -1;
        toAccount = -1;
        // Get current date
        time_t now = time(0);
        date = ctime(&now);
        // Remove newline from date
        if (!date.empty() && date[date.length()-1] == '\n') {
            date.erase(date.length()-1);
        }
    }

    void display() {
        cout << "Type: " << type;
        if (type == "Transfer") {
            cout << " (From: " << fromAccount << " To: " << toAccount << ")";
        }
        cout << endl;
        cout << "Amount: $" << amount << endl;
        cout << "Date: " << date << endl;
        cout << "------------------------" << endl;
    }
};

class Account {
public:
    int accountNumber;
    double balance;
    string accountType;
    Transaction transactions[100];
    int transactionCount;

    Account() {
        balance = 0.0;
        transactionCount = 0;
        accountType = "Savings";
    }

    void addTransaction(string type, double amount, int fromAcc = -1, int toAcc = -1) {
        if (transactionCount < 100) {
            transactions[transactionCount].type = type;
            transactions[transactionCount].amount = amount;
            transactions[transactionCount].fromAccount = fromAcc;
            transactions[transactionCount].toAccount = toAcc;
            transactionCount++;
        }
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            addTransaction("Deposit", amount);
            cout << "Deposit of $" << amount << " successful!" << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid amount!" << endl;
            return false;
        }
        if (amount > balance) {
            cout << "Insufficient balance!" << endl;
            return false;
        }
        balance -= amount;
        addTransaction("Withdrawal", amount);
        cout << "Withdrawal of $" << amount << " successful!" << endl;
        return true;
    }

    void showRecentTransactions(int count = 5) {
        if (transactionCount == 0) {
            cout << "No transactions yet." << endl;
            return;
        }
        
        cout << "\n=== Recent Transactions ===" << endl;
        int start = (transactionCount - count > 0) ? transactionCount - count : 0;
        for (int i = start; i < transactionCount; i++) {
            cout << i + 1 << ". ";
            transactions[i].display();
        }
    }

    void showAllTransactions() {
        if (transactionCount == 0) {
            cout << "No transactions yet." << endl;
            return;
        }
        
        cout << "\n=== All Transactions ===" << endl;
        for (int i = 0; i < transactionCount; i++) {
            cout << i + 1 << ". ";
            transactions[i].display();
        }
    }

    void displayAccountInfo() {
        cout << "\n=== Account Information ===" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Balance: $" << balance << endl;
        cout << "Total Transactions: " << transactionCount << endl;
    }
};

class Customer {
public:
    string name;
    string address;
    string phone;
    int customerId;
    Account account;

    Customer() {
        customerId = 0;
    }

    void displayCustomerInfo() {
        cout << "\n=== Customer Information ===" << endl;
        cout << "Customer ID: " << customerId << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Phone: " << phone << endl;
    }
};

// Function to transfer money between accounts
bool transferMoney(Account &fromAccount, Account &toAccount, double amount) {
    if (amount <= 0) {
        cout << "Invalid amount!" << endl;
        return false;
    }
    
    if (fromAccount.withdraw(amount)) {
        toAccount.deposit(amount);
        // Record the transfer transaction in both accounts with account numbers
        fromAccount.addTransaction("Transfer", amount, fromAccount.accountNumber, toAccount.accountNumber);
        toAccount.addTransaction("Transfer", amount, fromAccount.accountNumber, toAccount.accountNumber);
        cout << "Transfer of $" << amount << " successful!" << endl;
        cout << "From Account: " << fromAccount.accountNumber << " to Account: " << toAccount.accountNumber << endl;
        return true;
    }
    return false;
}

int main() {
    Customer customers[10];
    int customerCount = 0;
    int choice;
    int nextAccountNumber = 1000;

    do {
        cout << "\n===== Banking System =====" << endl;
        cout << "1. Create Customer and Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Transfer Money" << endl;
        cout << "5. View Account Information" << endl;
        cout << "6. View Recent Transactions" << endl;
        cout << "7. View All Transactions" << endl;
        cout << "8. View Customer Information" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                if (customerCount >= 10) {
                    cout << "Maximum customers reached!" << endl;
                    break;
                }
                
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, customers[customerCount].name);
                
                cout << "Enter address: ";
                getline(cin, customers[customerCount].address);
                
                cout << "Enter phone number: ";
                getline(cin, customers[customerCount].phone);
                
                customers[customerCount].customerId = customerCount + 1;
                customers[customerCount].account.accountNumber = nextAccountNumber++;
                
                cout << "Select account type (1 for Savings, 2 for Checking): ";
                int typeChoice;
                cin >> typeChoice;
                customers[customerCount].account.accountType = (typeChoice == 2) ? "Checking" : "Savings";
                
                cout << "Enter initial deposit amount: $";
                double initialDeposit;
                cin >> initialDeposit;
                customers[customerCount].account.deposit(initialDeposit);
                
                cout << "\nCustomer created successfully!" << endl;
                cout << "Customer ID: " << customers[customerCount].customerId << endl;
                cout << "Account Number: " << customers[customerCount].account.accountNumber << endl;
                
                customerCount++;
                break;
            }
            
            case 2: {
                int id;
                double amount;
                cout << "Enter customer ID: ";
                cin >> id;
                
                if (id < 1 || id > customerCount) {
                    cout << "Invalid customer ID!" << endl;
                    break;
                }
                
                cout << "Enter deposit amount: $";
                cin >> amount;
                customers[id-1].account.deposit(amount);
                break;
            }
            
            case 3: {
                int id;
                double amount;
                cout << "Enter customer ID: ";
                cin >> id;
                
                if (id < 1 || id > customerCount) {
                    cout << "Invalid customer ID!" << endl;
                    break;
                }
                
                cout << "Enter withdrawal amount: $";
                cin >> amount;
                customers[id-1].account.withdraw(amount);
                break;
            }
            
            case 4: {
                int fromId, toId;
                double amount;
                cout << "From Customer ID: ";
                cin >> fromId;
                cout << "To Customer ID: ";
                cin >> toId;
                
                if (fromId < 1 || fromId > customerCount || toId < 1 || toId > customerCount) {
                    cout << "Invalid customer ID(s)!" << endl;
                    break;
                }
                
                if (fromId == toId) {
                    cout << "Cannot transfer to the same account!" << endl;
                    break;
                }
                
                cout << "Enter transfer amount: $";
                cin >> amount;
                
                transferMoney(customers[fromId-1].account, customers[toId-1].account, amount);
                break;
            }
            
            case 5: {
                int id;
                cout << "Enter customer ID: ";
                cin >> id;
                
                if (id < 1 || id > customerCount) {
                    cout << "Invalid customer ID!" << endl;
                    break;
                }
                
                customers[id-1].account.displayAccountInfo();
                break;
            }
            
            case 6: {
                int id;
                cout << "Enter customer ID: ";
                cin >> id;
                
                if (id < 1 || id > customerCount) {
                    cout << "Invalid customer ID!" << endl;
                    break;
                }
                
                customers[id-1].account.showRecentTransactions();
                break;
            }
            
            case 7: {
                int id;
                cout << "Enter customer ID: ";
                cin >> id;
                
                if (id < 1 || id > customerCount) {
                    cout << "Invalid customer ID!" << endl;
                    break;
                }
                
                customers[id-1].account.showAllTransactions();
                break;
            }
            
            case 8: {
                int id;
                cout << "Enter customer ID: ";
                cin >> id;
                
                if (id < 1 || id > customerCount) {
                    cout << "Invalid customer ID!" << endl;
                    break;
                }
                
                customers[id-1].displayCustomerInfo();
                break;
            }
            
            case 9:
                cout << "Thank you for using the Banking System!" << endl;
                break;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        
    } while (choice != 9);

    return 0;
}