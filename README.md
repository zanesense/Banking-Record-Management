# Bank Management System

Welcome to the **Bank Management System**! This is a console-based application designed to manage bank accounts efficiently. The system allows you to create, modify, and delete accounts, as well as handle transactions such as deposits and withdrawals.

![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/zanesense/banking-record-management)
![GitHub Repo stars](https://img.shields.io/github/stars/zanesense/banking-record-management)

## Features

- **Create New Account**: Add a new customer account to the system.
- **Display All Accounts**: View a list of all customer accounts with details.
- **Deposit Amount**: Add money to a customer's account.
- **Withdraw Amount**: Withdraw money from a customer's account.
- **Close Account**: Delete a customer's account from the system.
- **Modify Account**: Update customer account details.
- **Balance Inquiry**: Check the balance of a specific account.

## Getting Started

### Prerequisites

- C++ Compiler (e.g., GCC)
- Text Editor or IDE (e.g., VS Code, CLion)

### Installation

1. **Clone the repository:**
    ```sh
    git clone https://github.com/yourusername/bank-management-system.git
    cd bank-management-system
    ```

2. **Compile the program:**
    ```sh
    g++ -o bank_system main.cpp
    ```

3. **Run the executable:**
    ```sh
    ./bank_system
    ```

### Usage

1. **Main Menu**: Upon running the program, you will be presented with the main menu:
    ```
    1 - NEW ACCOUNT
    2 - DISPLAY ALL ACCOUNTS
    3 - DEPOSIT AMOUNT
    4 - WITHDRAW AMOUNT
    5 - CLOSE AN ACCOUNT
    6 - MODIFY AN ACCOUNT
    7 - BALANCE INQUIRY
    8 - EXIT
    ```

2. **Create Account**: Select option 1 to create a new account. Follow the prompts to enter account details.

3. **Display Accounts**: Select option 2 to view all accounts. The details of each account will be displayed in a tabular format.

4. **Deposit Amount**: Select option 3 to deposit money. Enter the account number and the amount to deposit.

5. **Withdraw Amount**: Select option 4 to withdraw money. Enter the account number and the amount to withdraw.

6. **Close Account**: Select option 5 to close an account. Enter the account number to be closed.

7. **Modify Account**: Select option 6 to modify account details. Enter the account number and the new details.

8. **Balance Inquiry**: Select option 7 to check the balance of a specific account. Enter the account number to view details.

9. **Exit**: Select option 8 to exit the application.

## File Structure

- `main.cpp`: The main program file containing all the functionalities.
- `accounts.txt`: The file where account information is stored.

## Contributing

Contributions are welcome! Please fork this repository and submit a pull request with your changes.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

**Thank you for using the Bank Management System! We hope it meets your banking needs efficiently.**
