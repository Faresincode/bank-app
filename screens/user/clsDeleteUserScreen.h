#pragma once
#include "clsUtil.h";
#include "clsUser.h";
#include<iostream>
#include <iomanip>
#include "clsInputValidate.h";
#include "clsScreen.h";


using namespace std;


class clsDeleteUserScreen :protected clsScreen
{



private:


    static void _PrintUser(clsUser User)
    {
        cout << "\n";
        cout << setw(ScreenWidth) << "" << left << Green << "==========================================\n";
        cout << setw(ScreenWidth) << "" << left << Blue<< "User Card : \n";
        cout << setw(ScreenWidth) << "" << left << Green << "==========================================\n" << White;
        cout << setw(ScreenWidth) << "" << left << "FirstName      : " << User.FirstName << "\n";
        cout << setw(ScreenWidth) << "" << left << "LastName       : " << User.LastName << "\n";
        cout << setw(ScreenWidth) << "" << left << "Email          : " << User.Email << "\n";
        cout << setw(ScreenWidth) << "" << left << "Phone          : " << User.Phone << "\n";
        cout << setw(ScreenWidth) << "" << left << "UserName       : " << User.UserName << "\n";
        cout << setw(ScreenWidth) << "" << left << "Password       : " << User.Password << "\n";
        cout << setw(ScreenWidth) << "" << left << "Permission     : " << User.Permissions << "\n";
        cout << setw(ScreenWidth) << "" << left << Green<< "==========================================" << White;
        cout << endl;

    }

    static string _ReadUserName()
    {
        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter UserName? ";
        string UserName = clsInputValidate::ReadString();
        return UserName;
    }


public:

    static void ShowDeleteUserScreen()
    {

        clsScreen::_DrawScreenHeader("\t\tDelete User Screen");
        string UserName = _ReadUserName();
        if (UserName == "exit")
            return;
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\n" << setw(ScreenWidth) << "" << left <<clsUtil::Yellow()<< "Username is Not exist, Choose another one: "<<White;
            UserName = _ReadUserName();
        }
        if (UserName == "exit")
            return;
        clsUser UserToDelete = clsUser::Find(UserName);
        _PrintUser(UserToDelete);
        cout << "\n" << setw(ScreenWidth) << "" << left << "Are you sure you want to delete this User answer [Y/N]: ";
        if (clsInputValidate::IsAnswerIsYes())
        {
            if (UserToDelete.Delete())
            {
                cout << Green << "\n" << setw(ScreenWidth) << "" << left << "User Deleted Successfully :-)\n"<<White;
                _PrintUser(UserToDelete);
            }
            else
            {
                cout << Red << "\n" << setw(ScreenWidth) << "" << left << "\nError User Was not Deleted\n"<<White;
            }
        }


    }


};

