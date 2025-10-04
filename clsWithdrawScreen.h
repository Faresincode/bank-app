#pragma once
#include <iostream>
#include <iomanip>
#include "clsUtil.h";
#include "clsScreen.h";
#include "clsBankClient.h";


using namespace std;

class clsWithdrawScreen : protected clsScreen
{

private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\n";
        cout << setw(ScreenWidth) << "" << left << Green << "==========================================\n";
        cout << setw(ScreenWidth) << "" << left << Blue << "Client Card : \n";
        cout << setw(ScreenWidth) << "" << left << Green << "==========================================\n" << White;
        cout << setw(ScreenWidth) << "" << left << "FirstName      : " << Client.FirstName << "\n";
        cout << setw(ScreenWidth) << "" << left << "LastName       : " << Client.LastName << "\n";
        cout << setw(ScreenWidth) << "" << left << "Email          : " << Client.Email << "\n";
        cout << setw(ScreenWidth) << "" << left << "Phone          : " << Client.Phone << "\n";
        cout << setw(ScreenWidth) << "" << left << "Account Number : " << Client.AccountNumber() << "\n";
        cout << setw(ScreenWidth) << "" << left << "Pin code       : " << Client.PinCode << "\n";
        cout << setw(ScreenWidth) << "" << left << "Balance        : " << Client.AccountBalance << "\n";
        cout << setw(ScreenWidth) << "" << left << Green << "==========================================" << White;
        cout << endl;

    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        getline(cin >> ws, AccountNumber);
        return AccountNumber;
    }

    static double ReadWithdrawAmount()
    {
        cout << "\n" << setw(ScreenWidth) << "" << left << "Please enter Withdraw amount? ";
        return clsInputValidate::ReadNumber<double>();
    }

    static void PrintClientAccountBalanceLine(clsBankClient Client)
    {
        cout << "\n" << setw(ScreenWidth) << "" << left << "Your Balance is: " << Client.AccountBalance<<"\n";

    }

    static void PrintInsufficientBalanceLine()
    {
        cout << "\n" << setw(ScreenWidth) << "" << left << Red << "Insufficient Balance!" << White<<"\n";
    }

    static bool IsSureToPerformAction()
    {
        cout << "\n" << setw(ScreenWidth) << "" << left << "Are you sure you want to perform this Action? (y/n)? ";
        return clsInputValidate::IsAnswerIsYes();

    }

public:


    static void ShowWithdrawScreen()
    {
        clsScreen::_DrawScreenHeader("\t\tWithdraw Screen");
        cout << "\n" << setw(ScreenWidth) << "" << left << "Please Enter Account Number: ";
        string AccountNumber = _ReadAccountNumber();
        if (AccountNumber == "exit")
            return;
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << clsUtil::Yellow() << "Account Number not found enter other one: "<<White;
            AccountNumber = _ReadAccountNumber();
        }
        if (AccountNumber == "exit")
            return;
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        double Amount = ReadWithdrawAmount();

        while (Amount > Client.AccountBalance)
        {
            PrintInsufficientBalanceLine();
            cout << setw(ScreenWidth) << "" << left << "Enter amount under " << Client.AccountBalance;
            Amount = ReadWithdrawAmount();
        }
       
        if (IsSureToPerformAction())
        {
            if(Client.Withdraw(Amount))
            {
                cout << "\n" << setw(ScreenWidth) << "" << left <<Green<< "Amount Withdraw Successfully"<<White;
                PrintClientAccountBalanceLine(Client);
            }
            else
            {
                PrintInsufficientBalanceLine();
                cout << "\n" << setw(ScreenWidth) << "" << left << "Amount to withdraw is: " << Amount;
                PrintClientAccountBalanceLine(Client);
            }

        }
        else
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << clsUtil::Yellow() << "Operation was cancelled.\n";
        }

    }






};

