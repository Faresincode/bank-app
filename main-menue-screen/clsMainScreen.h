#pragma once
#include<iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsClientsListScreen.h";
#include "clsAddNewClientScreen.h";
#include "clsDeleteClientScreen.h";
#include "clsUpdateClientScreen.h";
#include "clsFindClientScreen.h";
#include "clsTransactionsScreen.h";
#include "clsManageUsersScreen.h";
#include "clsUsersActionsScreen.h";
#include "clsLoginsRegisterScreen.h";
#include "clsCurrencyExchangeMainScreen.h";

using namespace std;
 

class clsMainScreen : protected clsScreen
{


private:
    enum enMainMenueOptions 
    {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7,eLoginRegister=8, eUserActions=9,eCurrencyExchange=10,eExit = 11,
    };

    static  void _GoBackToMainMenu()
    {
        cout << "Press any key to go back to Main Menu...";
        system("pause>0");
        ShowMainMenu();
    }

    static short _ReadMainMenuOption()
    {
        cout << setw(ScreenWidth) << left << "" << "Choose what do you want to do? [1 to 11]? ";
        short Choice = clsInputValidate::ReadNumberBetween<short>(1, 11, "Enter Number between 1 to 11? ");
        return  Choice;

    }

    static void _ShowAllClientsScreen()
    {
        clsClientsListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }
    
    static void _ShowDeleteClientScreen()
    {
         clsDeleteClientScreen::ShowDeleteClient();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClient();
    }

    static void _ShowFindClientScreen()
    {

        clsFindClientScreen::FindClientScreen();
    }

    static void _ShowTransactionsMenu()
    {
        clsTransactionsScreen::ShowTransactionsMenu();
    }

    static void _ShowManageUsersMenu()
    {
        clsManageUsersScreen::ShowManageUsersMenu();
    }

    static void _Logout()
    {
        //cout << "this will make sure that the current user is empty befor go out \n";
        CurrentUser = clsUser::Find("", "");
    }
    
    static void _ShowUsersActionsScreen()
    {
        clsUsersActionsScreen::ShowUsersActionsScreen();
    }

    static void _ShowLoginUsersRegisterScreen()
    {
        clsLoginsRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeMainScreen()
    {
        clsCurrencyExchangeScreen::ShowCurrenciesMenue();
    }


    static void _PerformMainMenuOption(enMainMenueOptions MainMenuOption)
    {
        switch (MainMenuOption)
        {
        case enMainMenueOptions::eListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenu();
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenueOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenu();
            _GoBackToMainMenu();
            break;

        case enMainMenueOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenu();
            _GoBackToMainMenu();
            break;
        case enMainMenueOptions::eLoginRegister:
            system("cls");
            _ShowLoginUsersRegisterScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenueOptions::eUserActions:
            system("cls");
            _ShowUsersActionsScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenueOptions::eCurrencyExchange:
            system("cls");
            _ShowCurrencyExchangeMainScreen();
            _GoBackToMainMenu();
            break;
        case enMainMenueOptions::eExit:
            system("cls");
            CurrentUser.SaveUsersActions();
            _Logout();
            clsUser::UpdateLoginRegisterFile();
            break;

        }

    }

public:


    static void ShowMainMenu()
    {

        system("cls");
        clsScreen::_DrawScreenHeader("\t\tMain Screen");

        cout << setw(ScreenWidth) << left << "" <<Green<< "===========================================\n";
        cout << setw(ScreenWidth) << left << "" <<Red<<"\t\t    Main Menu\n";
        cout << setw(ScreenWidth) << left << "" << Green<<"===========================================\n"<<White;
        cout << setw(ScreenWidth) << left << "" << " [1]  Show Client List.\n";
        cout << setw(ScreenWidth) << left << "" << " [2]  Add New Client.\n";
        cout << setw(ScreenWidth) << left << "" << " [3]  Delete Client.\n";
        cout << setw(ScreenWidth) << left << "" << " [4]  Update Client Info.\n";
        cout << setw(ScreenWidth) << left << "" << " [5]  Find Client.\n";
        cout << setw(ScreenWidth) << left << "" << " [6]  Transactions.\n";
        cout << setw(ScreenWidth) << left << "" << " [7]  Manage Users.\n";
        cout << setw(ScreenWidth) << left << "" << " [8]  Login Register.\n";
        cout << setw(ScreenWidth) << left << "" << " [9]  User Action.\n";
        cout << setw(ScreenWidth) << left << "" << " [10] Currency Exchange.\n";
        cout << setw(ScreenWidth) << left << "" << " [11] Logout.\n";
        cout << setw(ScreenWidth) << left << "" <<Green<< "===========================================\n"<<White;

        _PerformMainMenuOption((enMainMenueOptions)_ReadMainMenuOption());
    }



};

