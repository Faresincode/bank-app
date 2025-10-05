#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsBankClient.h";

using namespace std;



class clsDeleteClientScreen : protected clsScreen
{
private:


    static void _PrintSpecificClientRecordLine(clsBankClient Client)
    {

        cout << setw(ScreenWidth) << left << "" << Green << "| " << White << setw(15) << left << Client.AccountNumber();
        cout << Green << "| " << White<< setw(23) << left << Client.FullName()<<Green<<"|"<<White;

    }

    static void _PrintSpecificClientHeader()
    {

        cout << Green;
        cout <<"\n" << setw(ScreenWidth) << left << "" << "___________________________________________\n\n";
        cout << White;

        cout << setw(ScreenWidth) << left << "" << Green << "| " << White << left << setw(15) << "Account Number";
        cout << Green << "| " << White << left << setw(23) << "Client Name"<<Green<<"|"<<White;
        cout << Green;
        cout << "\n" << setw(ScreenWidth) << left << "" << "___________________________________________\n";
        cout << White;
    }

    static void _PrintClient(clsBankClient & Client)
    {
        cout <<"\n"  << setw(ScreenWidth) << "" << left << clsUtil::Yellow() << "Client Card : ";
        cout <<"\n" << setw(ScreenWidth) << "" << left<< Green << "___________________________________________" << White;
        cout <<"\n" << setw(ScreenWidth) << "" << left<< " FirstName   : " << Client.FirstName;
        cout <<"\n" << setw(ScreenWidth) << "" << left<< " LastName    : " << Client.LastName;
        cout <<"\n" << setw(ScreenWidth) << "" << left<< " Email       : " << Client.Email;
        cout <<"\n" << setw(ScreenWidth) << "" << left<< " Phone       : " << Client.Phone;
        cout <<"\n" << setw(ScreenWidth) << "" << left<< " Acc. Number : " << Client.AccountNumber();
        cout <<"\n" << setw(ScreenWidth) << "" << left<< " Password    : " << Client.PinCode;
        cout <<"\n" << setw(ScreenWidth) << "" << left<< " Balance     : " << Client.AccountBalance;
        cout <<"\n" << setw(ScreenWidth) << "" << left<< Green << "___________________________________________\n" << White;


    }
    
    static void _PrintSmallClientsListInfo()
    {
        vector<clsBankClient>vClients = clsBankClient::GetClientsList();

        if (vClients.size() == 0)
        {
            cout << setw(ScreenWidth)<<""<<left <<Red<< "No Clients Available In the System!\n"<<White;
        }
        else
        {
            _PrintSpecificClientHeader();
            for (clsBankClient& Client : vClients)
            {
                _PrintSpecificClientRecordLine(Client);
                cout << endl;
            }
            cout << Green;
            cout << setw(ScreenWidth) << left << "" << "___________________________________________";
            cout << White;
            cout << endl;
        }
    }

    friend class clsUpdateClientScreen;

public:

    static void ShowDeleteClient()
    {
        if (!clsScreen::_CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;
        }
        if ((CurrentUser.Actions & clsUser::enPermissions::pDeleteClient) != clsUser::enPermissions::pDeleteClient)
        {
            CurrentUser.Actions += clsUser::enPermissions::pDeleteClient;
        }

        string Title = "\t\tDelete Client Screen\n";
        clsScreen::_DrawScreenHeader(Title);
        _PrintSmallClientsListInfo();
        cout << "\n" << setw(ScreenWidth) << "" << left<<"Please Enter Account Number that you want to delete: ";
        string AccountNumber = clsInputValidate::ReadString();
        if (AccountNumber == "exit")
            return;
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\n" << setw(ScreenWidth) << "" << left <<"Account number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        if (AccountNumber == "exit")
            return;
        clsBankClient DeleteClient = clsBankClient::Find(AccountNumber);
        _PrintClient(DeleteClient);
        cout <<"\n" << setw(ScreenWidth) << "" << left<< "Are you sure you want to delete the client answer [Y/N]: ";
        if (clsInputValidate::IsAnswerIsYes())
        {
            if (DeleteClient.Delete())
            {
                cout << "\n" << setw(ScreenWidth) << "" << left <<Green << "Client Deleted Successfully :-)\n";
                _PrintClient(DeleteClient);
            }
            else
            {
                cout << Red << "\n" << setw(ScreenWidth) << "" << left  << "\nError Client Was not Deleted\n";
            }
            cout << White;
        }
    }



};

