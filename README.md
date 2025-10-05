# Bank Management System in C++
A comprehensive C++ console banking system featuring 🔥 client management, multi-currency transactions, international transfers with IBAN/SWIFT validation, user authentication with role-based permissions, and complete transaction logging. 👌 Educational OOP project demonstrating file-based data persistence.


## Features 🔥

**Client Management**
- Add, update, delete, and search clients
- View client list with balances
- Encrypted PIN storage
<img width="800" height="400" alt="main-menue-screen" src="https://github.com/user-attachments/assets/ad33cef2-fa33-4a5a-8011-acec01a62474" />

**Transactions**
- Deposit and withdrawal operations
- Local account transfers
- International transfers with IBAN/SWIFT validation
- Currency conversion across 200+ currencies
- Transaction logging

<img width="800" height="400" alt="transactions-menue-screen" src="https://github.com/user-attachments/assets/92c99169-8171-4f38-83b1-fea06fbdc64b" />

**Currency Exchange**
- 200+ world currencies support
- Real-time currency conversion
- Exchange rate management
- Currency calculator
<img width="800" height="400" alt="currency-main-menue-screen" src="https://github.com/user-attachments/assets/62e8e8b0-207c-416d-91e3-77bef44efb71" />


**User Management**
- Multi-user authentication
- 9 permission levels
- Password encryption
- Login/logout tracking
- User activity monitoring
- 3-attempt login limit
<img width="800" height="400" alt="manage-user-menue-screen" src="https://github.com/user-attachments/assets/dea4cdb1-f581-4aa6-a30d-9d693199af6f" />

**Reporting**
- Total balances report
- Transfer logs
- Login history
- User action tracking
<img width="800" height="400" alt="transfer-log-list-screen" src="https://github.com/user-attachments/assets/18a5cf7f-82b7-43a8-acf4-bb98c887640f" />

<img width="800" height="400" alt="login-register-screen" src="https://github.com/user-attachments/assets/0a95a43a-8e54-4b41-bea8-27fa57e713bd" />


## Getting Started

**Prerequisites**
- C++ Compiler (Visual Studio 2019+)
- Windows OS

**Installation**
```bash
git clone https://github.com/Faresincode/bank-app
cd bank-management-system

Compile and run Bank Project.cpp
Default Login

Username: User1
Password: 1234
Permissions: Full Access


**Project Structure**

├── Bank Project.cpp                    # Main entry point
├── Global.h                            # Global configuration
│
├── Core Classes/
│   ├── clsBankClient.h                # Client operations
│   ├── clsUser.h                      # User management
│   ├── clsCurrency.h                  # Currency operations
│   ├── clsPerson.h                    # Base person class
│   └── clsScreen.h                    # Base screen class
│
├── Client Screens/
│   ├── clsAddNewClientScreen.h
│   ├── clsUpdateClientScreen.h
│   ├── clsDeleteClientScreen.h
│   ├── clsFindClientScreen.h
│   └── clsClientsListScreen.h
│
├── Transaction Screens/
│   ├── clsTransactionsScreen.h
│   ├── clsDepositScreen.h
│   ├── clsWithdrawScreen.h
│   ├── clsTransferScreen.h
│   ├── clsTotalBalancesScreen.h
│   ├── clsTransferLogScreen.h
│   ├── clsInternationalTransferScreen.h
│   └── clsInterTransLogScreen.h
│
├── Currency Screens/
│   ├── clsCurrencyExchangeMainScreen.h
│   ├── clsCurrencyExchangeListScreen.h
│   ├── clsFindCurrencyScreen.h
│   ├── clsUpdateCurrencyScreen.h
│   └── clsCurrencyCalculaterScreen.h
│
├── User Screens/
│   ├── clsLoginScreen.h
│   ├── clsManageUsersScreen.h
│   ├── clsAddNewUserScreen.h
│   ├── clsUpdateUserScreen.h
│   ├── clsDeleteUserScreen.h
│   ├── clsFindUserScreen.h
│   ├── clsListUsersScreen.h
│   ├── clsLoginsRegisterScreen.h
│   └── clsUsersActionsScreen.h
│
├── Utility Classes/
│   ├── clsUtil.h                      # Utility functions
│   ├── clsString.h                    # String operations
│   ├── clsMath.h                      # Math operations
│   ├── clsDate.h                      # Date/time handling
│   ├── clsInputValidate.h             # Input validation
│   └── clsPrint.h                     # Print utilities
│
├── Main Screens/
│   ├── clsMainScreen.h                # Main menu
│
└── Data Files/
    ├── Clients.txt                    # Client database
    ├── Users.txt                      # User accounts
    ├── Currencies.txt                 # Currency rates
    ├── LoginRegister.txt              # Login history
    ├── UsersActions.txt               # User actions log
    ├── TransfersLog.txt               # Local transfers
    ├── InterClientsSenders.txt        # Int'l senders
    ├── InterClientsRecipients.txt     # Int'l recipients
    └── InterTransferLog.txt           # Int'l transfers

Usage 👌
Exit Anytime: Type exit at most prompts to return
Skip Updates: Type skip when updating to keep current values
International Transfers:

Transactions → International Transfer
Enter sender IBAN
Enter recipient IBAN and SWIFT
Enter amount
System calculates fees and taxes automatically

Technical Details

Language: C++
Storage: Text files with #//# delimiter
Encryption: Shift cipher (key=2)
Permissions: Bitwise operations
Console Colors: ANSI escape codes

Data Format
FirstName#//#LastName#//#Email#//#Phone#//#Account#//#EncryptedPIN#//#Balance

Security

Password encryption
Permission-based access control
Session tracking
Complete audit logging
Failed login protection

Notes

Backup .txt files before operations
Basic encryption - not for production
100MB GitHub file size limit
Keep Currencies.txt when resetting system

License
Educational purposes
Author
Your Name - @Faresincode


