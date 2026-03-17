// ============================================================
//   Natnael International Bank - Management System
// ============================================================
//   Author  : Natnael Tezazu
//   Project : C++ Bank Management System
//   Language: C++ (OOP & File Handling)
//   Notes   : Built as part of personal C++ learning journey.
//             Concepts applied: structs, file I/O, loops,
//             functions, input validation.
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>  // for strlen()
#include <cstdio>   // for remove() and rename()
#include <iomanip>  // for setw() and formatted output
using namespace std;

// ============================================================
//   GLOBAL DATA
// ============================================================
const string VERSION = "1.0.0";  // current build version
int userCount = 1; // starts at 1 because index 0 is unused (accounts start at index 1)

struct Account {
    int    accNo;
    char   username[30];
    double balance;
    string type;
};

Account bankUsers[500];

// ============================================================
//   UI HELPERS  -  decorative lines and section headers
// ============================================================

void printLine() {
    cout << "  +----------------------------------------------------------+" << endl;
}

void printDoubleLine() {
    cout << "  +==========================================================" << endl;
}

void printHeader(const string& title) {
    printLine();
    cout << "  |  " << left << setw(57) << title << "|" << endl;
    printLine();
}

void printBanner() {
    cout << endl;
    cout << "  +=========================================================+" << endl;
    cout << "  |       NATNAEL INTERNATIONAL BANK                        |" << endl;
    cout << "  |       Bank Management System  v1.0                      |" << endl;
    cout << "  +----------------------------------------------------------+" << endl;
    cout << "  |       Author : Natnael Tezazu                           |" << endl;
    cout << "  +=========================================================+" << endl;
    cout << endl;
}

// ============================================================
//   FILE I/O
// ============================================================

// Saves the full accounts array to filename.bin using a safe
// write-to-temp-then-rename strategy to avoid data corruption.
void saveToFile(Account arr[]) {
    fstream outFile("temp.bin", ios::out | ios::binary);
    if (!outFile) {
        cerr << "  [ERROR] Could not open file for saving." << endl;
        return;
    }
    outFile.write(reinterpret_cast<const char*>(arr), userCount * sizeof(Account));
    outFile.close();
    remove("filename.bin");
    rename("temp.bin", "filename.bin");
}

// Loads all saved account records from filename.bin into the array.
void loadFromFile(Account arr[]) {
    fstream inFile("filename.bin", ios::in | ios::binary);
    if (!inFile) {
        // No file yet — first run, perfectly normal.
        return;
    }
    inFile.read(reinterpret_cast<char*>(arr), sizeof(Account) * 500);
    inFile.close();
}

// Returns true if a slot in the array is empty (no account stored there).
bool isEmpty(Account arr[], int k) {
    string name = arr[k].username;
    return name.empty() && arr[k].accNo == 0;
}

// Writes a human-readable account list to usersdata.txt
void writeLog() {
    fstream logFile("usersdata.txt", ios::out);
    if (!logFile.is_open()) {
        cerr << "  [ERROR] Could not open usersdata.txt for writing." << endl;
        return;
    }
    logFile << "  Natnael International Bank - Account Registry" << endl;
    logFile << "  Total accounts: " << userCount - 1 << endl;
    logFile << "  ---------------------------------------------------------------" << endl;
    logFile << "  No" << "\t" << "Account No" << "\t" << "Username" << "\t"
            << "Balance (ETB)" << "\t" << "Type" << endl;
    logFile << "  ---------------------------------------------------------------" << endl;
    for (int k = 1; k < userCount; k++) {
        logFile << "  " << k << ".\t"
                << bankUsers[k].accNo   << "\t\t"
                << bankUsers[k].username << "\t\t"
                << bankUsers[k].balance  << " ETB\t\t"
                << bankUsers[k].type     << endl;
        logFile << "  ---------------------------------------------------------------" << endl;
    }
    logFile.close();
}

// ============================================================
//   CORE FEATURES
// ============================================================

void createAccount(int k, Account users[]) {
    printHeader("  NEW ACCOUNT REGISTRATION");
    cout << endl;

    cin.ignore();
    cout << "  Enter full name          : ";
    cin.getline(users[k].username, sizeof(users[k].username));

    cout << "  Enter initial deposit    : ";
    while (!(cin >> users[k].balance) || users[k].balance < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "  [!] Invalid amount. Enter a positive number: ";
    }

    cout << endl;
    printLine();
    cout << "  |  Select Account Type                                    |" << endl;
    printLine();
    cout << "  |  1. Normal Account                                      |" << endl;
    cout << "  |  2. Female's Account                                    |" << endl;
    cout << "  |  3. Children's Account                                  |" << endl;
    cout << "  |  4. Sheria Account                                      |" << endl;
    printLine();
    cout << "  Enter choice: ";

    int type;
    cin >> type;
    switch (type) {
        case 1: users[k].type = "Normal";     break;
        case 2: users[k].type = "Female's";   break;
        case 3: users[k].type = "Children's"; break;
        case 4: users[k].type = "Sheria";     break;
        default:
            cout << "  [!] Invalid choice. Setting to Normal." << endl;
            users[k].type = "Normal";
    }

    users[k].accNo = 1000580 + userCount;
    userCount++;

    cout << endl;
    printLine();
    cout << "  |  Account created successfully!                          |" << endl;
    cout << "  |  Your Account Number: " << left << setw(35) << users[k].accNo << "|" << endl;
    cout << "  |  Please save your account number safely.                |" << endl;
    printLine();
    cout << endl;
}

void deposit() {
    printHeader("  DEPOSIT FUNDS");
    cout << endl;
    cout << "  Enter your account number: ";
    int accNo;
    cin >> accNo;

    bool found = false;
    double amount = 0;

    for (int i = 1; i < userCount; i++) {
        if (accNo == bankUsers[i].accNo) {
            cout << "  Enter deposit amount (ETB): ";
            while (!(cin >> amount) || amount <= 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "  [!] Invalid amount. Must be greater than 0: ";
            }
            bankUsers[i].balance += amount;
            found = true;
            cout << endl;
            printLine();
            cout << "  |  " << fixed << setprecision(2)
                 << amount << " ETB deposited successfully.";
            cout << setw(max(0, (int)(26 - to_string((int)amount).length()))) << "|" << endl;
            cout << "  |  New balance: " << left << setw(43) << bankUsers[i].balance << "|" << endl;
            printLine();
            break;
        }
    }

    if (!found) {
        cout << "  [!] Account not found. Please check the account number." << endl;
    }
    cout << endl;
}

void withdraw() {
    printHeader("  WITHDRAW FUNDS");
    cout << endl;
    cout << "  Enter your account number: ";
    int accNo;
    cin >> accNo;

    bool found = false;
    double amount = 0;

    for (int i = 1; i < userCount; i++) {
        if (accNo == bankUsers[i].accNo) {
            found = true;
            bool valid = false;
            do {
                cout << "  Enter withdrawal amount (ETB): ";
                while (!(cin >> amount) || amount <= 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "  [!] Invalid amount. Must be greater than 0: ";
                }
                if (amount <= bankUsers[i].balance) {
                    bankUsers[i].balance -= amount;
                    valid = true;
                    cout << endl;
                    printLine();
                    cout << "  |  " << amount << " ETB withdrawn successfully.                    |" << endl;
                    cout << "  |  Remaining balance: " << left << setw(37) << bankUsers[i].balance << "|" << endl;
                    printLine();
                } else {
                    cout << "  [!] Insufficient balance. Available: "
                         << bankUsers[i].balance << " ETB." << endl;
                }
            } while (!valid);
            break;
        }
    }

    if (!found) {
        cout << "  [!] Account not found. Please check the account number." << endl;
    }
    cout << endl;
}

void transfer() {
    printHeader("  TRANSFER FUNDS");
    cout << endl;

    int senderAccNo, receiverAccNo;
    bool foundSender = false, foundReceiver = false;

    cout << "  Enter your account number      : ";
    cin >> senderAccNo;

    for (int i = 1; i < userCount; i++) {
        if (senderAccNo == bankUsers[i].accNo) {
            foundSender = true;

            cout << "  Enter receiver's account number: ";
            cin >> receiverAccNo;

            if (receiverAccNo == senderAccNo) {
                cout << "  [!] Cannot transfer to your own account." << endl;
                cout << endl;
                return;
            }

            for (int j = 1; j < userCount; j++) {
                if (receiverAccNo == bankUsers[j].accNo) {
                    foundReceiver = true;
                    double amount = 0;
                    bool valid = false;

                    do {
                        cout << "  Enter amount to transfer (ETB): ";
                        while (!(cin >> amount) || amount <= 0) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "  [!] Invalid amount: ";
                        }
                        if (amount <= bankUsers[i].balance) {
                            bankUsers[i].balance -= amount;
                            bankUsers[j].balance += amount;
                            valid = true;
                            cout << endl;
                            printLine();
                            cout << "  |  Transfer successful!                                   |" << endl;
                            cout << "  |  " << amount << " ETB sent to " << bankUsers[j].username
                                 << setw(max(0, (int)(30 - strlen(bankUsers[j].username)))) << "|" << endl;
                            cout << "  |  Your new balance: " << left << setw(38) << bankUsers[i].balance << "|" << endl;
                            printLine();
                        } else {
                            cout << "  [!] Insufficient balance. Available: "
                                 << bankUsers[i].balance << " ETB." << endl;
                        }
                    } while (!valid);
                    break;
                }
            }
            break;
        }
    }

    if (!foundSender) {
        cout << "  [!] Sender account not found." << endl;
    } else if (!foundReceiver) {
        cout << "  [!] Receiver account not found." << endl;
    }
    cout << endl;
}

void retrieveAccount() {
    printHeader("  ACCOUNT DETAILS");
    cout << endl;
    cout << "  Enter your account number: ";
    int accNo;
    cin >> accNo;

    bool found = false;
    for (int i = 1; i < userCount; i++) {
        if (accNo == bankUsers[i].accNo) {
            found = true;
            cout << endl;
            printLine();
            cout << "  |  Account Number : " << left << setw(39) << bankUsers[i].accNo    << "|" << endl;
            cout << "  |  Account Holder : " << left << setw(39) << bankUsers[i].username << "|" << endl;
            cout << "  |  Balance        : " << left << setw(35) << bankUsers[i].balance
                 << "ETB |" << endl;
            cout << "  |  Account Type   : " << left << setw(39) << bankUsers[i].type     << "|" << endl;
            printLine();
            break;
        }
    }

    if (!found) {
        cout << "  [!] Account not found. Please check the account number." << endl;
    }
    cout << endl;
}

void modifyAccount() {
    printHeader("  MODIFY ACCOUNT");
    cout << endl;
    cout << "  Enter your account number: ";
    int accNo;
    cin >> accNo;

    bool found = false;
    for (int i = 1; i < userCount; i++) {
        if (accNo == bankUsers[i].accNo) {
            found = true;
            cout << endl;
            printLine();
            cout << "  |  What would you like to modify?                         |" << endl;
            printLine();
            cout << "  |  1. Change username                                     |" << endl;
            cout << "  |  2. Change account type                                 |" << endl;
            printLine();
            cout << "  Enter choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "  Enter new username: ";
                    cin.ignore();
                    cin.getline(bankUsers[i].username, sizeof(bankUsers[i].username));
                    break;
                case 2:
                    cout << endl;
                    printLine();
                    cout << "  |  1. Normal     2. Female's   3. Children's   4. Sheria  |" << endl;
                    printLine();
                    cout << "  Enter choice: ";
                    int type;
                    cin >> type;
                    switch (type) {
                        case 1: bankUsers[i].type = "Normal";     break;
                        case 2: bankUsers[i].type = "Female's";   break;
                        case 3: bankUsers[i].type = "Children's"; break;
                        case 4: bankUsers[i].type = "Sheria";     break;
                        default: cout << "  [!] Invalid choice. No changes made." << endl;
                    }
                    break;
                default:
                    cout << "  [!] Invalid choice. No changes made." << endl;
            }

            cout << endl;
            printLine();
            cout << "  |  Account updated successfully.                          |" << endl;
            printLine();
            break;
        }
    }

    if (!found) {
        cout << "  [!] Account not found. Please check the account number." << endl;
    }
    cout << endl;
}

void listAllAccounts() {
    printHeader("  ALL ACCOUNTS");
    cout << endl;
    if (userCount <= 1) {
        cout << "  No accounts registered yet." << endl;
        cout << endl;
        return;
    }
    cout << "  Total accounts: " << userCount - 1 << endl << endl;
    cout << "  " << left
         << setw(5)  << "No"
         << setw(13) << "Acc. No"
         << setw(22) << "Username"
         << setw(18) << "Balance (ETB)"
         << setw(14) << "Type" << endl;
    printLine();
    for (int k = 1; k < userCount; k++) {
        cout << "  " << left
             << setw(5)  << k
             << setw(13) << bankUsers[k].accNo
             << setw(22) << bankUsers[k].username
             << setw(18) << bankUsers[k].balance
             << setw(14) << bankUsers[k].type << endl;
    }
    printLine();
    cout << endl;
}

void showMenu() {
    cout << endl;
    printLine();
    cout << "  |  MAIN MENU                                              |" << endl;
    printLine();
    cout << "  |  1.  Create Account                                     |" << endl;
    cout << "  |  2.  Deposit Funds                                      |" << endl;
    cout << "  |  3.  Withdraw Funds                                     |" << endl;
    cout << "  |  4.  Transfer Funds                                     |" << endl;
    cout << "  |  5.  View Account Details                               |" << endl;
    cout << "  |  6.  Modify Account                                     |" << endl;
    cout << "  |  7.  List All Accounts                                  |" << endl;
    cout << "  |  8.  Exit                                               |" << endl;
    printLine();
    cout << "  Enter your choice (1-8): ";
}

// ============================================================
//   MAIN
// ============================================================

int main() {
    // Load any previously saved accounts from binary file
    loadFromFile(bankUsers);

    // Count how many valid accounts are already stored
    for (int i = 1; i < 500; i++) {
        if (!isEmpty(bankUsers, i)) {
            userCount++;
        }
    }

    printBanner();
    cout << "  Welcome back! Current registered accounts: " << userCount - 1 << endl;

    int option;
    do {
        showMenu();
        while (!(cin >> option)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Please enter a valid number (1-8): ";
        }

        switch (option) {
            case 1:
                createAccount(userCount, bankUsers);
                saveToFile(bankUsers);
                writeLog();
                break;
            case 2:
                deposit();
                saveToFile(bankUsers);
                writeLog();
                break;
            case 3:
                withdraw();
                saveToFile(bankUsers);
                writeLog();
                break;
            case 4:
                transfer();
                saveToFile(bankUsers);
                writeLog();
                break;
            case 5:
                retrieveAccount();
                break;
            case 6:
                modifyAccount();
                saveToFile(bankUsers);
                writeLog();
                break;
            case 7:
                listAllAccounts();
                break;
            case 8:
                cout << endl;
                printLine();
                cout << "  |  Thank you for using Natnael International Bank!        |" << endl;
                cout << "  |  Goodbye.                                               |" << endl;
                printLine();
                cout << endl;
                break;
            default:
                cout << "  [!] Invalid choice. Please enter a number between 1 and 8." << endl;
        }
    } while (option != 8);

    return 0;
}
