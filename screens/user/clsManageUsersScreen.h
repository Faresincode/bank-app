#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h";
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include "clsUtil.h";
#include "clsListUsersScreen.h";
#include "clsFindUserScreen.h";
#include "clsAddNewUserScreen.h";
#include "clsDeleteUserScreen.h";
#include "clsUpdateUserScreen.h";
#include "clsTransactionsScreen.h";



using namespace std;

class clsManageUsersScreen : protected clsScreen
{

private:

    enum enManageUsersMenueOptions
    {
        eListUsers = 1,
        eAddNewUser = 2,
        eDeleteUser = 3,
        eUpdateUser = 4,
        eFindUser = 5,
        eMainMenu = 6
    };

    static short _ReadManageUserMenuOption()
    {

        cout << setw(ScreenWidth) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        //short Choice = clsInputValidate::ReadShortNumberBetween(1, 8, "Enter Number between 1 to 8? ");
        //return Choice;
        return  clsInputValidate::ReadNumberBetween<short>(1, 6, "Enter Number between 1 to 8? ");

    }

    static void _GoBackToManageUsersMenu()
    {
        cout << "\n\nPress any key to go back to Manage Users Menu...";
        system("pause>0");
        ShowManageUsersMenu();
    }

    static void _ShowListUsersScreen()
    {
        clsListUsersScreen::ShowListUsersScreen();
    }
    
    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::ShowFindUserScreen();
    }
   
    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }
    
    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _PerformManageUsersMenuOption(enManageUsersMenueOptions ManageUsersMenuOption)
    {

        switch (ManageUsersMenuOption)
        {
            case enManageUsersMenueOptions::eListUsers:
            {
                system("cls");
                _ShowListUsersScreen();
                _GoBackToManageUsersMenu();
                break;
            }

            case enManageUsersMenueOptions::eAddNewUser:
            {
                system("cls");
                _ShowAddNewUserScreen();
                _GoBackToManageUsersMenu();
                break;
            }

            case enManageUsersMenueOptions::eDeleteUser:
            {
                system("cls");
                _ShowDeleteUserScreen();
                _GoBackToManageUsersMenu();
                break;
            }

            case enManageUsersMenueOptions::eUpdateUser:
            {
                system("cls");
                _ShowUpdateUserScreen();
                _GoBackToManageUsersMenu();
                break;
            }

            case enManageUsersMenueOptions::eFindUser:
            {
                system("cls");
                _ShowFindUserScreen();
                _GoBackToManageUsersMenu();
                break;
            }
            case enManageUsersMenueOptions::eMainMenu:
            {
                //do nothing here the main screen will handle it :-) ;
            }
        }

    }

public:


    static void ShowManageUsersMenu()
    {
        if (!clsScreen::_CheckAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;
        }
        if ((CurrentUser.Actions & clsUser::enPermissions::pManageUsers) != clsUser::enPermissions::pManageUsers)
        {
            CurrentUser.Actions += clsUser::enPermissions::pManageUsers;
        }

        system("cls");
        clsScreen::_DrawScreenHeader("\t\tManage Users Screen");
        cout << setw(ScreenWidth) << left << "" << Green << "===========================================\n";
        cout << setw(ScreenWidth) << left << "" << Red << "\t\tManage Users Menu\n";
        cout << setw(ScreenWidth) << left << "" << Green<< "===========================================\n" << White;
        cout << setw(ScreenWidth) << left << "" << " [1] Show Users List.\n";
        cout << setw(ScreenWidth) << left << "" << " [2] Add New User.\n";
        cout << setw(ScreenWidth) << left << "" << " [3] Delete Users.\n";
        cout << setw(ScreenWidth) << left << "" << " [4] Update Users Info.\n";
        cout << setw(ScreenWidth) << left << "" << " [5] Find User.\n";
        cout << setw(ScreenWidth) << left << "" << " [6] Main Menu.\n";
        cout << setw(ScreenWidth) << left << "" << Green << "===========================================\n" << White;

        _PerformManageUsersMenuOption((enManageUsersMenueOptions)_ReadManageUserMenuOption());
    }





};

