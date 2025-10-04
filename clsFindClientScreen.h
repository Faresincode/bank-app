#pragma once
#include<iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h";
#include "clsBankClient.h";


using namespace std;


class clsFindClientScreen : protected clsScreen
{

private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\n";
        cout << setw(ScreenWidth) << "" << left << Green<< "==========================================\n";
        cout << setw(ScreenWidth) << "" << left << Blue << " Client Card : \n";
        cout << setw(ScreenWidth) << "" << left << Green << "==========================================\n" << White;
        cout << setw(ScreenWidth) << "" << left << " FirstName      : " << Client.FirstName << "\n";
        cout << setw(ScreenWidth) << "" << left << " LastName       : " << Client.LastName << "\n";
        cout << setw(ScreenWidth) << "" << left << " Email          : " << Client.Email << "\n";
        cout << setw(ScreenWidth) << "" << left << " Phone          : " << Client.Phone << "\n";
        cout << setw(ScreenWidth) << "" << left << " Account Number : " << Client.AccountNumber() << "\n";
        cout << setw(ScreenWidth) << "" << left << " Pin code       : " << Client.PinCode << "\n";
        cout << setw(ScreenWidth) << "" << left << " Balance        : " << Client.AccountBalance << "\n";
        cout << setw(ScreenWidth) << "" << left << Green << "==========================================" << White;
        cout << endl;

    }


public:

    static void FindClientScreen()
    {
        if (!clsScreen::_CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;
        }
        if ((CurrentUser.Actions & clsUser::enPermissions::pFindClient) != clsUser::enPermissions::pFindClient)
        {
            CurrentUser.Actions += clsUser::enPermissions::pFindClient;
        }

        _DrawScreenHeader("\t\tFind Client Screen");
        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Account Number: ";
        string AccountNumber = clsInputValidate::ReadString();
        if (AccountNumber == "exit")
            return;
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << Yellow << "\n" << setw(ScreenWidth) << "" << left << "Account number is not found, choose another one:  " << White;
            AccountNumber = clsInputValidate::ReadString();   
        }
        if (AccountNumber == "exit")
            return;
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        if (!Client.IsEmpty())
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << Green << "Client Found :-)\n";
            _PrintClient(Client);
        }
        else
        {
            cout <<"\n"<< setw(ScreenWidth)<<""<<left << Red << "Client Was not Found :-(\n" << White;
        }
    }




};

