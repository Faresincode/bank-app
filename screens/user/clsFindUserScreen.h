#pragma once
#include "clsUtil.h";
#include "clsUser.h";
#include<iostream>
#include <iomanip>
#include "clsInputValidate.h";
#include "clsScreen.h";


using namespace std;

class clsFindUserScreen : protected clsScreen
{


private:


    static void _PrintUser(clsUser User)
    {
        cout << "\n";
        cout << setw(ScreenWidth) << "" << left << Green << "==========================================\n";
        cout << setw(ScreenWidth) << "" << left << Blue<<  " Client Card : \n";
        cout << setw(ScreenWidth) << "" << left << Green << "==========================================\n" << White;
        cout << setw(ScreenWidth) << "" << left << " UserName       : " << User.UserName << "\n";
        cout << setw(ScreenWidth) << "" << left << " Full Name      : " << User.FullName() << "\n";
        cout << setw(ScreenWidth) << "" << left << " Email          : " << User.Email << "\n";
        cout << setw(ScreenWidth) << "" << left << " Phone          : " << User.Phone << "\n";
        cout << setw(ScreenWidth) << "" << left << " Password       : " << User.Password << "\n";
        cout << setw(ScreenWidth) << "" << left << " Permission     : " << User.Permissions << "\n";
        cout << setw(ScreenWidth) << "" << left << Green<< "==========================================" << White;
        cout << endl;

    }

    static void _PrintNotFoundLine(string NotFoundVariable="User",string TextColor=clsUtil::Yellow())
    {
        cout <<"\n" << TextColor << setw(ScreenWidth) << "" << left << " " << NotFoundVariable << " not found :-) " << White;
    }

    static string _ReadUserName()
    {
        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter UserName? ";
        string UserName=clsInputValidate::ReadString();
        return UserName;
    }

public:

    static void ShowFindUserScreen()
    {
        clsScreen::_DrawScreenHeader("\t\tFind User Screen");
        cout << "\n" << setw(ScreenWidth) << "" << left << "(To exit enter exit)\n";
        string UserName = _ReadUserName();
        if (UserName == "exit")
            return;
        while (!clsUser::IsUserExist(UserName))
        {
            _PrintNotFoundLine("UserName");
            cout<<"Choose another one: ";
            UserName = _ReadUserName();
        }
        if (UserName == "exit")
            return;
        clsUser User = clsUser::Find(UserName);
        if (!User.IsEmpty())
        {
            cout << "\n" << Green << setw(ScreenWidth) << "" << left << " User Found :-)"<<White;
            _PrintUser(User);
        }
        else
        {
            _PrintNotFoundLine("User");
        }
    }







};

