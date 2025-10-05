#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsUtil.h";
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "iomanip";

using namespace std;


class clsTotalBalancesScreen : protected clsScreen
{

private:

    static void _PrintTotalBalancesAsText(double TotalBalances)
    {
        cout << "\n" << setw(ScreenWidth)<<""<<left << clsUtil::NumberToText(TotalBalances) << endl;
    }

    static void _PrintTotalBalancesLine(double TotalBalances)
    {
        cout << "\n" << setw(ScreenWidth)<<""<<left <<clsUtil::Tabs(4)<< "  Total Balances = " << TotalBalances << endl;
    }
     
    static string _TotalClientListHeader(short TotalClientAvailable)
    {
        return Blue+ "\t  Total Client list[" +to_string (TotalClientAvailable) + "] Clients\n" + White;
    }
     
    static void _PrintClientHeaderBalance()
    {
        cout << "\n" << setw(ScreenWidth)<< ""  <<left << Green << "____________________________________________________________________\n" << White;
        cout << "\n" << setw(ScreenWidth) << "" << left << Green << "| " << White << left << setw(15) << "Account number";
        cout << Green << "| " << White << left << setw(30) << "Full Name";
        cout << Green << "| " << White<< left << setw(15) << "Account Balance";
        cout << "\n" << setw(ScreenWidth) << "" << left << Green << "____________________________________________________________________\n" << White;

    }
   
    static void _PrintNoClientAvailable()
    {
        cout << "\n" << setw(ScreenWidth)<<""<<left << Red << "No client available in the system\n" << White;

    }
    
    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << setw(ScreenWidth)<<""<<left;
        cout << Green << "| " << White << left << setw(15) << Client.AccountNumber();
        cout << Green << "| " << White << left << setw(30) << Client.FullName();
        cout << Green << "| " << White << left << setw(15) << Client.AccountBalance;
        cout << endl;
    }

public:



    static void ShowTotalBalance()
    {
        vector<clsBankClient>vClients = clsBankClient::GetClientsList();
        clsScreen::_DrawScreenHeader("\t\tTotal Balances Screen", _TotalClientListHeader(vClients.size()));
        _PrintClientHeaderBalance();

        if (vClients.size() == 0)
        {
            _PrintNoClientAvailable();
        }
        else
        {
            for (clsBankClient& Client : vClients)
            {
                _PrintClientRecordBalanceLine(Client);
            }
            cout << Green << setw(ScreenWidth)<<""<<left << "____________________________________________________________________\n" << White;

        }
        double TotalBalances = clsBankClient::GetTotalBalances();
        _PrintTotalBalancesLine(TotalBalances);
        _PrintTotalBalancesAsText(TotalBalances);

    }



};

