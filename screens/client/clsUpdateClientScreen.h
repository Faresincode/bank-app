#pragma once
#include<iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h";
#include "clsBankClient.h";
using namespace std;


class clsUpdateClientScreen : protected clsScreen
{

private:



    static void _PrintClient(clsBankClient Client)
    {
        cout << "\n";
        cout << setw(ScreenWidth) << "" << left << Green<< "==========================================\n";
        cout << setw(ScreenWidth) << "" << left << Blue<< " Client Card : \n";
        cout << setw(ScreenWidth) << "" << left << Green << "==========================================\n" << White;
        cout << setw(ScreenWidth) << "" << left << " FirstName      : " << Client.FirstName << "\n";
        cout << setw(ScreenWidth) << "" << left << " LastName       : " << Client.LastName << "\n";
        cout << setw(ScreenWidth) << "" << left << " Email          : " << Client.Email << "\n";
        cout << setw(ScreenWidth) << "" << left << " Phone          : " << Client.Phone << "\n";
        cout << setw(ScreenWidth) << "" << left << " Account Number : " << Client.AccountNumber() << "\n";
        cout << setw(ScreenWidth) << "" << left << " Pin code       : " << Client.PinCode << "\n";
        cout << setw(ScreenWidth) << "" << left << " Balance        : " << Client.AccountBalance << "\n";
        cout << setw(ScreenWidth) << "" << left << Green<< "==========================================" << White;
        cout << endl;

    }

    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\n" << setw(ScreenWidth) << "" << left <<Blue<<"To skip Anything enter -> skip\n"<<White;
        string StringInput = "";
        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter FirstName: ";
        
        if ((StringInput = clsInputValidate::ReadString())!="skip")
        {
            Client.FirstName = StringInput;
        }

        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter LastName: ";
        if ((StringInput = clsInputValidate::ReadString()) != "skip")
        {
            Client.LastName= StringInput;
        }
        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Email: ";
        if ((StringInput = clsInputValidate::ReadString()) != "skip")
        {
            Client.Email = StringInput;
        }

        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Phone: ";
        if ((StringInput = clsInputValidate::ReadString()) != "skip")
        {
            Client.Phone = StringInput;
        }
        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter PinCode: ";
        if ((StringInput = clsInputValidate::ReadString()) != "skip")
        {
            Client.PinCode = StringInput;
        }

        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Account Balance: (to skip enter -1): ";
        if (double Balance = clsInputValidate::ReadNumber<double>() != -1)
        {
            Client.AccountBalance = Balance;
        }
    }

    enum enWhatToUpdate { eFirstName = 1, eLastName = 2, eEmail = 3, ePhone = 4, ePinCode = 5, eAccountBalance = 6, eAll = 7 };

    static void _PerformUpdateMenuScreen(enWhatToUpdate WhatToUpdate, clsBankClient& Client)
    {

        switch (WhatToUpdate)
        {
        case enWhatToUpdate::eFirstName:
        {
            cout << "\n" << setw(ScreenWidth)<<""<<left << "Enter FirstName : ";
            Client.FirstName = clsInputValidate::ReadString();
            break;
        }
        case enWhatToUpdate::eLastName:
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << "Enter LastName: ";
            Client.LastName = clsInputValidate::ReadString();
            break;
        }

        case enWhatToUpdate::eEmail:
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Email: ";
            Client.Email = clsInputValidate::ReadString();
            break;
        }
        case enWhatToUpdate::ePhone:
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Phone: ";

            Client.Phone = clsInputValidate::ReadString();

            break;
        }
        case enWhatToUpdate::ePinCode:
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Pin code: ";

            Client.PinCode = clsInputValidate::ReadString();

            break;
        }
        case enWhatToUpdate::eAccountBalance:
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Account Balance: ";
            Client.AccountBalance = clsInputValidate::ReadNumber<double>();
            break;
        }
        case enWhatToUpdate::eAll:
        {
            _ReadClientInfo(Client);

            break;
        }
        default:
        {
            _ReadClientInfo(Client);
            break;
        }


        }

    }

    static void _ShowUpdateMenuScreen(clsBankClient& Client)
    {
        cout << setw(ScreenWidth)<<"" <<left << Green << "==========================================\n";
        cout << setw(ScreenWidth)<<"" <<left << Red<< " Update Menu Screen \n";
        cout << setw(ScreenWidth)<<"" <<left << Green << "==========================================\n" << White;
        cout << setw(ScreenWidth)<<"" <<left << " [1] FirstName       \n";
        cout << setw(ScreenWidth)<<"" <<left << " [2] LastName        \n";
        cout << setw(ScreenWidth)<<"" <<left << " [3] Email           \n";
        cout << setw(ScreenWidth)<<"" <<left << " [4] Phone           \n";
        cout << setw(ScreenWidth)<<"" <<left << " [5] Pin code        \n";
        cout << setw(ScreenWidth)<<"" <<left << " [6] Balance         \n";
        cout << setw(ScreenWidth)<<"" <<left << " [7] All Client Info \n";
        cout << setw(ScreenWidth)<<"" <<left << Green<< "==========================================\n\n";
        cout << setw(ScreenWidth)<<"" <<left << clsUtil::Yellow() << "What do you want to update (answer as following menu from  1 to 7 ) : " << White;

        _PerformUpdateMenuScreen((enWhatToUpdate)clsInputValidate::ReadNumberBetween<short>(1, 7), Client);
    }

public:



    static void ShowUpdateClient()
    {
        if (!clsScreen::_CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;
        }
        if ((CurrentUser.Actions & clsUser::enPermissions::pUpdateClients) != clsUser::enPermissions::pUpdateClients)
        {
            CurrentUser.Actions += clsUser::enPermissions::pUpdateClients;
        }

        string Title = "\t\tUpdate Client Screen\n";
        clsScreen::_DrawScreenHeader(Title);
        clsDeleteClientScreen::_PrintSmallClientsListInfo();
        cout << "\n" << setw(ScreenWidth) << "" << left << "Please Enter client Account Number: ";
        string AccountNumber = clsInputValidate::ReadString();
        if (AccountNumber == "exit")
            return;
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << clsUtil::Yellow() << "\n" << setw(ScreenWidth) << "" << left << "Account number is not found, choose another one:  " << White;
            AccountNumber = clsInputValidate::ReadString();
        }
        if (AccountNumber == "exit")
            return;
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);
        _ShowUpdateMenuScreen(Client1);
        clsBankClient::enSaveResults SaveResult;
        SaveResult = Client1.Save();
        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << Green << "\n" << setw(ScreenWidth) << "" << left << "Account Updated Successfully :-)\n" << White;
            _PrintClient(Client1);
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << Red << "\n" << setw(ScreenWidth) << "" << left << "Error account was not saved because it's Empty" << White;
            break;
        }

        }



    }





};

