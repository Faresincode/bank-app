#pragma once
#include <iostream>
#include "clsBankClient.h";
#include <iomanip>
#include "clsUtil.h";
#include "clsScreen.h";

using namespace std;

class clsDepositScreen : protected clsScreen
{
private:


    static void _PrintClient(clsBankClient Client)
    {
        cout << "\n";
        cout << setw(ScreenWidth) << "" << left << Green << "==========================================\n";
        cout << setw(ScreenWidth) << "" << left << Blue<< "Client Card : \n";
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
        cout <<"\n"<<setw(ScreenWidth)<<""<<left << "Please enter Account Number? ";
        cin >> AccountNumber;
        return AccountNumber;
    }

    static double ReadDepositAmount()
    {
        cout << "\n" << setw(ScreenWidth) << "" << left << "Please enter deposit amount? ";
        double Amount = clsInputValidate::ReadNumber<double>();
        while (Amount < 0)
        {
            cout << "\n" << setw(ScreenWidth) << "" << left <<Red<< "Error! enter Positive deposit amount? "<<White;
            Amount = clsInputValidate::ReadNumber<double>();
        }
        return Amount;
    }


public:


	static void ShowDepositScreen()
	{
        clsScreen::_DrawScreenHeader("\t\tDeposit Screen");
        string AccountNumber = _ReadAccountNumber();
        if (AccountNumber == "exit")
            return;
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout <<"\n"<<setw(ScreenWidth)<<""<<left <<Red<< "Client with [" << AccountNumber << "] does not exist.\n"<<White;
            AccountNumber = _ReadAccountNumber();
        }
        if (AccountNumber == "exit")
            return;
        cout << White;
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
        double Amount = ReadDepositAmount();
        cout << "\n" << setw(ScreenWidth) << "" << left << "Are you sure you want to perform this Action? (y/n)? ";
        if (clsInputValidate::IsAnswerIsYes())
        {
            Client.Deposit(Amount);
            cout << "\n" << setw(ScreenWidth) << "" << left <<Green << "Amount Deposited Successfully.\n"<<White;
            cout << "\n" << setw(ScreenWidth) << "" << left  << "New Balance Is: " << Client.AccountBalance;
        }
        else
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << Red << "Operation was cancelled.\n";
        }

	}



};

