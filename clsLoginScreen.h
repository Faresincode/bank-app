#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "clsDate.h";
#include "clsUtil.h";

using namespace std;

class clsLoginScreen :protected clsScreen
{

private:

    static string _ReadUserName()
    {
        cout << setw(ScreenWidth) << "" << left << "Enter Username? ";
        return clsInputValidate::ReadString();
    }

    static string _ReadPassword()
    {
        cout << setw(ScreenWidth) << "" << left << "Enter Password? ";
        return  clsInputValidate::ReadString();
    }

    static bool IsWantToExit(string InputToCheckIfExist)
    {
        if (InputToCheckIfExist == "exit")
        {
            system("cls");
            clsScreen::_DrawScreenHeader("\tThank's for trying To Use Our App");
            return true;
        }
        return false;
    }

    static  bool _Login()
    {
        bool LoginFailed = false; string Username = "", Password = ""; short FailedLoginCount = 0;
        cout << "\n" << setw(ScreenWidth) << "" << left <<Blue<< "To Exit enter (exit)\n\n"<<White;
        do
        {
            if (LoginFailed)
            {
                FailedLoginCount++;
                cout << "\n" << setw(ScreenWidth) << "" << left <<Red<< "Invalid Username/Password! "<<White;
                cout << "\n" << setw(ScreenWidth) << "" << left << Yellow << "You have " << (3- FailedLoginCount) << " Trial (s) to LogIn\n" << White;
            }
            if (FailedLoginCount == 3)
            {
                cout << "\n" << setw(ScreenWidth) << "" << left << Yellow << "You are locked after 3 failed trails bey bey Koko " << White << endl;
                return false;
            }
            Username = _ReadUserName();
            if (IsWantToExit(Username))
            {
                return false;
            }

            Password = _ReadPassword();
            if (IsWantToExit(Password))
            {
                return false;
            }

            CurrentUser = clsUser::Find(Username, Password);
            LoginFailed = CurrentUser.IsEmpty();

        } while (LoginFailed);
        CurrentUser.LoginDateAndTime = clsDate::GetSystemDateTimeString();
        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenu();
      
        return true;
    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t\tLogin Screen");
        return _Login();
    }



};
