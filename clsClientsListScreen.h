#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h";
#include "clsScreen.h";


using namespace std;



class clsClientsListScreen :protected clsScreen
{

private:

    static void _PrintClientRecordLine(clsBankClient Client)
    {

        cout<< setw(1) << left << "" <<Green << "| " <<White << setw(25) << left << Client.AccountNumber();
        cout<<Green<< "| " << White  << setw(25) << left << Client.FullName();
        cout<<Green<< "| " << White  << setw(15) << left << Client.Phone;
        cout<<Green<< "| " << White  << setw(35) << left << Client.Email;
        cout<<Green<< "| " << White  << setw(20) << left << Client.PinCode;
        cout<<Green<< "| $ " << White<< setw(11) << left << Client.AccountBalance;


    }
    
    static void _PrintClientHeader()
    {

        cout << Green;
        cout <<"\n" << setw(1) << left << "" << "_______________________________________________________";
        cout << "__________________________________________________________________________________________\n" << endl; cout << White;

        cout << setw(1) << left << "" << Green <<"| " <<White << left << setw(25) << "Account Number";
        cout <<Green<< "| " << White << left << setw(25) << "Client Full Name";
        cout <<Green<< "| " << White << left << setw(15) << "Phone";
        cout <<Green<< "| " << White << left << setw(35) << "Email";
        cout <<Green<< "| " << White << left << setw(20) << "Pin Code";
        cout <<Green<< "| " << White << left << setw(11) << "Balance";
        cout << Green;
        cout << "\n" << setw(1) << left << "" << "_______________________________________________________";
        cout << "__________________________________________________________________________________________\n" << endl; cout << White;
    
    }

public:

    static void ShowClientsList()
    {
        if (!clsScreen::_CheckAccessRights(clsUser::enPermissions::pListClients))
        {
            return;
        }
        if ((CurrentUser.Actions & clsUser::enPermissions::pListClients)!= clsUser::enPermissions::pListClients)
        {
             CurrentUser.Actions += clsUser::enPermissions::pListClients;
        }

        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        string Title = "\t\tClient List Screen";
        string SubTitle = "\t\t  (" + to_string(vClients.size()) + ") Client(s).";

        clsScreen::_DrawScreenHeader(Title, SubTitle);
        if (vClients.size() == 0)
        {
            cout << setw(ScreenWidth)<<""<<left<<Red << "No Clients Available In the System!\n"<<White;
        }
        else
        {
            _PrintClientHeader();
            for (clsBankClient& Client : vClients)
            {
                _PrintClientRecordLine(Client);
                cout << endl;
            }
            cout << Green;
            cout <<"\n" << setw(1) << left << "" << "_____________________________________________________";
            cout << "____________________________________________________________________________________________\n" << endl;
            cout << White;

        }

    }




};

