#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const string filename = "accounts.txt";

struct Account {
    int number;
    string firstName;
    string lastName;
    char type;
    int amount;
};

void create_account() {
    system("cls");
    cout << "+-----------------------+\n";
    cout << "| CREATE NEW ACCOUNT    |\n";
    cout << "+-----------------------+\n";

    Account newAccount;

    cout << "Enter account no. : ";
    cin >> newAccount.number;

    ifstream inputFile(filename);
    int num;
    string firstName, lastName;
    char type;
    int amount;
    bool duplicate = false;
    while (inputFile >> num >> firstName >> lastName >> type >> amount) {
        if (num == newAccount.number) {
            duplicate = true;
            break;
        }
    }
    inputFile.close();
    if (duplicate) {
        cout << "Account with this account number already exists!" << endl;
        cout << "Press Enter to return to the main menu...";
        cin.ignore();
        cin.get();
        system("cls");
        return;
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

    ofstream outputFile(filename, ios::app);
    if (outputFile.is_open()) {
        outputFile << newAccount.number << " " << newAccount.firstName << " " << newAccount.lastName << " " << newAccount.type << " " << newAccount.amount << endl; // Make sure fields are separated by space
        outputFile.close();
    }
    else {
        cout << "Unable to open file!" << endl;
        return;
    }

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
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        cout << "List of all accounts:\n";
        cout << "+---------------------------------------------------------------+\n";
        cout << "| Account No  |  First Name   |  Last Name    |  Type  | Amount |\n";
        cout << "+---------------------------------------------------------------+\n";
        int num;
        string firstName, lastName;
        char type;
        int amount;

        while (inputFile >> num >> firstName >> lastName >> type >> amount) {
            cout << "| " << setw(11) << num << " | " <<
                setw(13) << firstName << " | " <<
                setw(12) << lastName << " |   " <<
                setw(5) << type << " | " <<
                setw(6) << amount << " |\n";
        }

        cout << "+---------------------------------------------------------------+\n";
        inputFile.close();
    }
    else {
        cout << "Unable to open file!" << endl;
    }

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

    ifstream inputFile(filename);
    ofstream tempFile("temp.txt");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cout << "Unable to open file!" << endl;
        return;
    }

    int num;
    string firstName, lastName;
    char type;
    int amount;

    bool found = false;

    while (inputFile >> num >> firstName >> lastName >> type >> amount) {
        if (num == accountNo) {
            found = true;
            amount += depositAmount;
        }
        tempFile << num << " " << firstName << " " << lastName << " " << type << " " << amount << endl;
    }

    inputFile.close();
    tempFile.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (!found) {
        cout << "Account not found!" << endl;
    }
    else {
        cout << "Amount deposited successfully!" << endl;
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

    ifstream inputFile(filename);
    ofstream tempFile("temp.txt");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cout << "Unable to open file!" << endl;
        return;
    }

    int num;
    string firstName, lastName;
    char type;
    int amount;

    bool found = false;

    while (inputFile >> num >> firstName >> lastName >> type >> amount) {
        if (num == accountNo) {
            found = true;
            if (amount >= withdrawAmount) {
                amount -= withdrawAmount;
            }
            else {
                cout << "Insufficient balance!" << endl;
            }
        }
        tempFile << num << " " << firstName << " " << lastName << " " << type << " " << amount << endl;
    }

    inputFile.close();
    tempFile.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (!found) {
        cout << "Account not found!" << endl;
    }
    else {
        cout << "Amount withdrawn successfully!" << endl;
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

    ifstream inputFile(filename);
    ofstream tempFile("temp.txt");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cout << "Unable to open file!" << endl;
        return;
    }

    int num;
    string firstName, lastName;
    char type;
    int amount;

    bool found = false;

    while (inputFile >> num >> firstName >> lastName >> type >> amount) {
        if (num == accountNo) {
            found = true;
            cout << "Account with A/c no. " << num << " has been closed." << endl;
            continue;
        }
        tempFile << num << " " << firstName << " " << lastName << " " << type << " " << amount << endl;
    }

    inputFile.close();
    tempFile.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (!found) {
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

    ifstream inputFile(filename);
    ofstream tempFile("temp.txt");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cout << "Unable to open file!" << endl;
        return;
    }

    int num;
    string firstName, lastName;
    char type;
    int amount;

    bool found = false;

    while (inputFile >> num >> firstName >> lastName >> type >> amount) {
        if (num == accountNo) {
            found = true;
            cout << "Enter new first name: ";
            cin.ignore();
            getline(cin, firstName);
            cout << "Enter new last name: ";
            getline(cin, lastName);
            cout << "Enter new account type (C/S): ";
            cin >> type;
        }
        tempFile << num << " " << firstName << " " << lastName << " " << type << " " << amount << endl;
    }

    inputFile.close();
    tempFile.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (!found) {
        cout << "Account not found!" << endl;
    }
    else {
        cout << "Account modified successfully!" << endl;
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

    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        int num;
        string firstName, lastName;
        char type;
        int amount;

        bool found = false;

        while (inputFile >> num >> firstName >> lastName >> type >> amount) {
            if (num == accountNo) {
                found = true;
                cout << "Account No: " << num << endl;
                cout << "Account Holder's Name: " << firstName << " " << lastName << endl;
                cout << "Account Type: " << type << endl;
                cout << "Balance: " << amount << endl;
                break;
            }
        }

        if (!found) {
            cout << "Account not found!" << endl;
        }

        inputFile.close();
    }
    else {
        cout << "Unable to open file!" << endl;
    }

    cout << "Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
    system("cls");
}

int menu() {
    do {
        int ch;
        cout << "\n1 - NEW ACCOUNT";
        cout << "\n2 - DISPLAY ALL ACCOUNTS";
        cout << "\n3 - DEPOSIT AMOUNT";
        cout << "\n4 - WITHDRAW AMOUNT";
        cout << "\n5 - CLOSE AN ACCOUNT";
        cout << "\n6 - MODIFY AN ACCOUNT";
        cout << "\n7 - BALANCE INQUIRY";
        cout << "\n8 - EXIT\n";
        cout << "\nSelect Your Option (1-8): ";
        cin >> ch;

        switch (ch) {
        case 1:
            create_account();
            break;
        case 2:
            display_accounts();
            break;
        case 3:
            deposit_amount();
            break;
        case 4:
            withdraw_amount();
            break;
        case 5:
            close_account();
            break;
        case 6:
            modify_account();
            break;
        case 7:
            balance_inquiry();
            break;
        case 8:
            system("cls");
            cout << "Exiting the program. Thank you for using our banking system!" << endl;
            return 0;
        default:
            cout << "\nInvalid Choice! \n";
            return 0;
        }

    } while (true);

    return 0;
}

int main() {
    menu();
}
