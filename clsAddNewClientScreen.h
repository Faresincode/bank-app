#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsUtil.h";
#include "clsScreen.h";
#include "clsBankClient.h";
#include "clsInputValidate.h";


using namespace std;

class clsAddNewClientScreen : protected clsScreen
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

    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadNumber<float>();

    }


public:

    static void ShowAddNewClientScreen()
    {
        if (!clsScreen::_CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;
        }
        if ((CurrentUser.Actions & clsUser::enPermissions::pAddNewClient) != clsUser::enPermissions::pAddNewClient)
        {
              CurrentUser.Actions += clsUser::enPermissions::pAddNewClient;
        }
        clsScreen::_DrawScreenHeader("\t\tAdd New Client Screen");
        cout << "\n" << setw(ScreenWidth) << "" << left<<"Please Enter Account Number : ";
        string AccountNumber = clsInputValidate::ReadString();
        if (AccountNumber == "exit")
            return;
        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\n" << setw(ScreenWidth) << "" << left<< "\nAccount Number Is Already Used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        if (AccountNumber == "exit")
            return;
        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientInfo(NewClient);
        clsBankClient::enSaveResults SaveResult= NewClient.Save();
        switch (SaveResult)
        {
            case clsBankClient::enSaveResults::svSucceeded:          
                cout << Green << "\n" << setw(ScreenWidth) << "" << left << "Account added Successfully :-)\n" << White;
                _PrintClient(NewClient);
                break;          
            case clsBankClient::enSaveResults::svFaildEmptyObject:
                cout << clsUtil::Yellow() << "\n" << setw(ScreenWidth) << "" << left << "Error account was not saved because it's Empty" << White;
                break;
            case clsBankClient::enSaveResults::svFaildAccountNumberExists:
                cout << Red << "\n" << setw(ScreenWidth) << "" << left << "Error account was not saved because account number is used!" << White;
                break;

        }
    }




};
