#pragma once
#include <iostream>
#include "clsMainScreen.h";
#include "clsBankClient.h";
#include "clsUtil.h";
#include "clsScreen.h";
#include "clsDepositScreen.h";
#include "clsWithdrawScreen.h";
#include "clsTotalBalancesScreen.h";
#include "clsTransferScreen.h";
#include "clsTransferLogScreen.h";
#include "clsInterTransLogScreen.h";
#include "clsInternationalTransferScreen.h";

using namespace std;


class clsTransactionsScreen : protected clsScreen
{


private:

    enum enTransactionsMenuOptions 
    { 
        eDeposit = 1,
        eWithdraw = 2,
        eShowTotalBalance = 3,
        eTransfer=4,
        eTransferLog=5,
        eInternationalTransfer=6,
        eInterTransLog=7,
        eShowMainMenue = 8 
    };

    static short ReadTransactionsMenuOption()
    {
        cout << setw(ScreenWidth) << left << "" << "Choose what do you want to do? [1 to 8]? ";
        short Choice = clsInputValidate::ReadNumberBetween<short>(1, 8, "Enter Number between 1 to 8? ");
        return Choice;
    }

    static void _ShowDepositScreen()
    {

        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalance();
    }

    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }

    static void  _ShowTransferLogScreen()
    {
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    static void _ShowInternationalTransferScreen()
    {
        cout << "\nInternational screen will be here later\n";
        clsInternationalTransferScreen::ShowInternationalTransferScreen();
    }

    static void _ShowInterTransLogScreen()
    {
        clsInterTransLogScreen::ShowInterTransLogScreen();
    }

    static void _GoBackToTransactionsMenu()
    {
        cout << "\n\nPress any key to go back to Transactions Menu...";
        system("pause>0");
        ShowTransactionsMenu();

    }

    static void _PerformTransactionsMenuOption(enTransactionsMenuOptions TransactionsMenuOption)
    {

        switch (TransactionsMenuOption)
        {
            case enTransactionsMenuOptions::eDeposit:
            {
                system("cls");
                _ShowDepositScreen();
                _GoBackToTransactionsMenu();
                break;
            }

            case enTransactionsMenuOptions::eWithdraw:
            {
                system("cls");
                _ShowWithdrawScreen();
                _GoBackToTransactionsMenu();
                break;
            }

            case enTransactionsMenuOptions::eShowTotalBalance:
            {
                system("cls");
                _ShowTotalBalancesScreen();
                _GoBackToTransactionsMenu();
                break;
            }
            case enTransactionsMenuOptions::eTransfer:
            {
                system("cls");
                _ShowTransferScreen();
                _GoBackToTransactionsMenu();
                break;
            }
            case enTransactionsMenuOptions::eTransferLog:
            {
                system("cls");
                _ShowTransferLogScreen();
                _GoBackToTransactionsMenu();
                break;
            }
            case enTransactionsMenuOptions::eInternationalTransfer:
            {
                system("cls");
                _ShowInternationalTransferScreen();
                _GoBackToTransactionsMenu();
                break;

            }
            case enTransactionsMenuOptions::eInterTransLog:
            {
                system("cls");
                _ShowInterTransLogScreen();
                _GoBackToTransactionsMenu();
                break;

            }

            case enTransactionsMenuOptions::eShowMainMenue:
            {

            }
        }


    }


public:


    static void ShowTransactionsMenu()
    {
        if (!clsScreen::_CheckAccessRights(clsUser::enPermissions::pTranactions))
        {
            return;
        }
        if ((CurrentUser.Actions & clsUser::enPermissions::pTranactions) != clsUser::enPermissions::pTranactions)
        {
            CurrentUser.Actions += clsUser::enPermissions::pTranactions;
        }

        system("cls");
        _DrawScreenHeader("\t\tTransactions Screen");
        cout <<"\n"<< setw(ScreenWidth) << left << "" << Green<<"===========================================\n";
        cout <<"\n"<< setw(ScreenWidth) << left << "" <<Blue<< "\t\tTransactions Menu";
        cout <<"\n"<< setw(ScreenWidth) << left << "" << Green<<"===========================================\n"<<White;
        cout <<"\n"<< setw(ScreenWidth) << left << "" << " [1] Deposit.";
        cout <<"\n"<< setw(ScreenWidth) << left << "" << " [2] Withdraw.";
        cout <<"\n"<< setw(ScreenWidth) << left << "" << " [3] Total Balances.";
        cout <<"\n"<< setw(ScreenWidth) << left << "" << " [4] Transfer.";
        cout <<"\n"<< setw(ScreenWidth) << left << "" << " [5] Transfer Log.";
        cout <<"\n"<< setw(ScreenWidth) << left << "" << " [6] International Transfer.";
        cout << "\n" << setw(ScreenWidth) << left << ""<<" [7] International Trans Log";
        cout <<"\n"<< setw(ScreenWidth) << left << "" << " [8] Main Menu.";
        cout <<"\n"<< setw(ScreenWidth) << left << "" << Green<<"===========================================\n\n"<<White;

        _PerformTransactionsMenuOption((enTransactionsMenuOptions)ReadTransactionsMenuOption());
    }



};

