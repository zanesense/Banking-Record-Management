#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const string filename = "accounts.txt";
const string adminUser = "admin";
const string adminPass = "password";
const int MAX_ACCOUNTS = 100;

struct Account {
    int number;
    string firstName;
    string lastName;
    char type;
    int amount;
};

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

void load_accounts() {
    accountCount = 0;
    ifstream inputFile(filename);
    int num;
    string firstName, lastName;
    char type;
    int amount;
    while (inputFile >> num >> firstName >> lastName >> type >> amount) {
        if (accountCount < MAX_ACCOUNTS) {
            accounts[accountCount].number = num;
            accounts[accountCount].firstName = firstName;
            accounts[accountCount].lastName = lastName;
            accounts[accountCount].type = type;
            accounts[accountCount].amount = amount;
            accountCount++;
        }
    }
    inputFile.close();
}

void save_accounts() {
    ofstream outputFile(filename);
    for (int i = 0; i < accountCount; i++) {
        outputFile << accounts[i].number << " " << accounts[i].firstName << " " << accounts[i].lastName << " " << accounts[i].type << " " << accounts[i].amount << endl;
    }
    outputFile.close();
}

bool admin_login() {
    string username, password;
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;
    return (username == adminUser && password == adminPass);
}

void create_account() {
    system("cls");
    cout << "+-----------------------+\n";
    cout << "| CREATE NEW ACCOUNT    |\n";
    cout << "+-----------------------+\n";

    if (accountCount >= MAX_ACCOUNTS) {
        cout << "Account limit reached. Cannot create more accounts.\n";
        cout << "Press Enter to return to the main menu...";
        cin.ignore();
        cin.get();
        system("cls");
        return;
    }

    Account newAccount;

    cout << "Enter account no. : ";
    cin >> newAccount.number;

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].number == newAccount.number) {
            cout << "Account with this account number already exists!" << endl;
            cout << "Press Enter to return to the main menu...";
            cin.ignore();
            cin.get();
            system("cls");
            return;
        }
    }

    cout << "Enter account holder's first name : ";
    cin.ignore();
    getline(cin, newAccount.firstName);
    cout << "Enter account holder's last name : ";
    getline(cin, newAccount.lastName);

    cout << "Enter account type (C/S) : ";
    cin >> newAccount.type;

    cout << "Enter initial amount : ";
    cin >> newAccount.amount;
    if ((newAccount.type == 'C' && newAccount.amount < 1000) ||
        (newAccount.type == 'S' && newAccount.amount < 500)) {
        cout << "Minimum initial amount for ";
        cout << (newAccount.type == 'C' ? "current" : "savings");
        cout << " account is ";
        cout << (newAccount.type == 'C' ? "1000" : "500") << endl;
        cout << "Press Enter to return to the main menu...";
        cin.ignore();
        cin.get();
        system("cls");
        return;
    }

    accounts[accountCount] = newAccount;
    accountCount++;
    save_accounts();

    cout << endl;
    cout << "Account Created.\n";
    cout << "A/c no. :  " << newAccount.number << endl;
    cout << "Name    :  " << newAccount.firstName << " " << newAccount.lastName << endl;
    cout << "Type    :  " << newAccount.type << endl;
    cout << "Amount  :  " << newAccount.amount << endl;
    cout << endl;

    cout << "Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
    system("cls");
}

void display_accounts() {
    system("cls");
    cout << "List of all accounts:\n";
    cout << "+---------------------------------------------------------------+\n";
    cout << "| Account No  |  First Name   |  Last Name    |  Type  | Amount |\n";
    cout << "+---------------------------------------------------------------+\n";
    for (int i = 0; i < accountCount; i++) {
        cout << "| " << setw(11) << accounts[i].number << " | " <<
            setw(13) << accounts[i].firstName << " | " <<
            setw(12) << accounts[i].lastName << " |   " <<
            setw(5) << accounts[i].type << " | " <<
            setw(6) << accounts[i].amount << " |\n";
    }
    cout << "+---------------------------------------------------------------+\n";

    cout << "Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
    system("cls");
}

void deposit_amount() {
    system("cls");
    cout << "+-----------------------+\n";
    cout << "| DEPOSIT AMOUNT        |\n";
    cout << "+-----------------------+\n";

    int accountNo, depositAmount;
    cout << "Enter account no. : ";
    cin >> accountNo;
    cout << "Enter deposit amount : ";
    cin >> depositAmount;

    bool found = false;

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].number == accountNo) {
            accounts[i].amount += depositAmount;
            found = true;
            break;
        }
    }

    if (found) {
        save_accounts();
        cout << "Amount deposited successfully!" << endl;
    } else {
        cout << "Account not found!" << endl;
    }

    cout << "Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
    system("cls");
}

void withdraw_amount() {
    system("cls");
    cout << "+-----------------------+\n";
    cout << "| WITHDRAW AMOUNT       |\n";
    cout << "+-----------------------+\n";

    int accountNo, withdrawAmount;
    cout << "Enter account no. : ";
    cin >> accountNo;
    cout << "Enter withdrawal amount : ";
    cin >> withdrawAmount;

    bool found = false;

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].number == accountNo) {
            if (accounts[i].amount >= withdrawAmount) {
                accounts[i].amount -= withdrawAmount;
                found = true;
            } else {
                cout << "Insufficient balance!" << endl;
                cout << "Press Enter to return to the main menu...";
                cin.ignore();
                cin.get();
                system("cls");
                return;
            }
            break;
        }
    }

    if (found) {
        save_accounts();
        cout << "Amount withdrawn successfully!" << endl;
    } else {
        cout << "Account not found!" << endl;
    }

    cout << "Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
    system("cls");
}

void close_account() {
    system("cls");
    cout << "+-----------------------+\n";
    cout << "| CLOSE ACCOUNT         |\n";
    cout << "+-----------------------+\n";

    int accountNo;
    cout << "Enter account no. : ";
    cin >> accountNo;

    bool found = false;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].number == accountNo) {
            found = true;
            for (int j = i; j < accountCount - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            accountCount--;
            break;
        }
    }

    if (found) {
        save_accounts();
        cout << "Account with A/c no. " << accountNo << " has been closed." << endl;
    } else {
        cout << "Account not found!" << endl;
    }

    cout << "Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
    system("cls");
}

void modify_account() {
    system("cls");
    cout << "+-----------------------+\n";
    cout << "| MODIFY ACCOUNT        |\n";
    cout << "+-----------------------+\n";

    int accountNo;
    cout << "Enter account no. : ";
    cin >> accountNo;

    bool found = false;

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].number == accountNo) {
            found = true;
            cout << "Enter new first name: ";
            cin.ignore();
            getline(cin, accounts[i].firstName);
            cout << "Enter new last name: ";
            getline(cin, accounts[i].lastName);
            cout << "Enter new account type (C/S): ";
            cin >> accounts[i].type;
            break;
        }
    }

    if (found) {
        save_accounts();
        cout << "Account modified successfully!" << endl;
    } else {
        cout << "Account not found!" << endl;
    }

    cout << "Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
    system("cls");
}

void balance_inquiry() {
    system("cls");
    cout << "+-----------------------+\n";
    cout << "| BALANCE INQUIRY       |\n";
    cout << "+-----------------------+\n";

    int accountNo;
    cout << "Enter account no. : ";
    cin >> accountNo;

    bool found = false;

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].number == accountNo) {
            found = true;
            cout << "A/c no.: " << accounts[i].number << endl;
            cout << "Account Holder's Name: " << accounts[i].firstName << " " << accounts[i].lastName << endl;
            cout << "Account Type: " << accounts[i].type << endl;
            cout << "Balance: " << accounts[i].amount << endl;
            break;
        }
    }

    if (!found) {
        cout << "Account not found!" << endl;
    }

    cout << "Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
    system("cls");
}

int admin_menu() {
    load_accounts();
    do {
        int ch;
        cout << "\nADMIN MENU\n";
        cout << "1 - DISPLAY ALL ACCOUNTS\n";
        cout << "2 - CLOSE AN ACCOUNT\n";
        cout << "3 - MODIFY AN ACCOUNT\n";
        cout << "4 - EXIT\n";
        cout << "Select Your Option (1-4): ";
        cin >> ch;

        switch (ch) {
        case 1:
            display_accounts();
            break;
        case 2:
            close_account();
            break;
        case 3:
            modify_account();
            break;
        case 4:
            cout << "Exiting admin menu. Thank you!" << endl;
            return 0;
        default:
            cout << "Invalid Choice! \n";
        }

    } while (true);

    return 0;
}

int user_menu() {
    load_accounts();
    do {
        int ch;
        cout << "\nUSER MENU\n";
        cout << "1 - NEW ACCOUNT\n";
        cout << "2 - DEPOSIT AMOUNT\n";
        cout << "3 - WITHDRAW AMOUNT\n";
        cout << "4 - BALANCE INQUIRY\n";
        cout << "5 - EXIT\n";
        cout << "Select Your Option (1-5): ";
        cin >> ch;

        switch (ch) {
        case 1:
            create_account();
            break;
        case 2:
            deposit_amount();
            break;
        case 3:
            withdraw_amount();
            break;
        case 4:
            balance_inquiry();
            break;
        case 5:
            cout << "Exiting user menu. Thank you!" << endl;
            return 0;
        default:
            cout << "Invalid Choice! \n";
        }

    } while (true);

    return 0;
}

int main() {
    int userType;
    cout << "Welcome to the Banking System\n";
    cout << "1 - Admin Login\n";
    cout << "2 - User Menu\n";
    cout << "Select Your Option (1-2): ";
    cin >> userType;

    if (userType == 1) {
        if (admin_login()) {
            admin_menu();
        } else {
            cout << "Invalid admin credentials! Exiting...\n";
        }
    } else if (userType == 2) {
        user_menu();
    } else {
        cout << "Invalid choice! Exiting...\n";
    }

    return 0;
}
