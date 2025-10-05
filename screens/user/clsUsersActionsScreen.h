#pragma once
#include <iostream>
#include "clsPerson.h";
#include <vector>
#include <fstream>
#include "clsScreen.h";
#include "clsUser.h";
#include "clsString.h";

using namespace std;


class clsUsersActionsScreen : protected clsScreen
{

private:

    static void _PrintUserActionsCard(clsUser User)
    {

        cout << "\n\n" << setw(ScreenWidth) << "" << left <<Green<< "User Actions";
        cout << "\n" << setw(ScreenWidth) << "" << left <<Green<< "______________________________"<<White;
        cout << "\n" << setw(ScreenWidth) << "" << left << "User Name      :  " << User.UserName;
        cout << "\n" << setw(ScreenWidth) << "" << left << "Password       :  " << User.Password;
        cout << "\n" << setw(ScreenWidth) << "" << left << "Permissions    :  " << User.Permissions;
        cout << "\n" << setw(ScreenWidth) << "" << left << "Actions Number :  " << User.Actions;

        cout << "\n\n" << setw(ScreenWidth) << "" << left <<Blue<< "User History"<<White;

        cout <<"\n" << setw(ScreenWidth) << "" << left << "Login: " << User.LoginDateAndTime;

        if (User.IsMakeThisActions(clsUser::enPermissions::pListClients))
        {
            cout<< "\n"<< setw(ScreenWidth) << "" << left << "List Client";
        }
        if (User.IsMakeThisActions(clsUser::enPermissions::pAddNewClient))
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << "Add New Client";
        }
        if (User.IsMakeThisActions(clsUser::enPermissions::pDeleteClient))
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << "Delete Client";
        }
        if (User.IsMakeThisActions(clsUser::enPermissions::pUpdateClients))
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << "Update Client";
        }
        if (User.IsMakeThisActions(clsUser::enPermissions::pFindClient))
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << "Find Client";
        }
        if (User.IsMakeThisActions(clsUser::enPermissions::pTranactions))
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << "Transactions";
        }
        if (User.IsMakeThisActions(clsUser::enPermissions::pManageUsers))
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << "Manage Users";
        }

        cout << "\n" << setw(ScreenWidth) << "" << left << "Logout: " << User.LogOutDateAndTime;

        cout << "\n" << setw(ScreenWidth) << "" << left << Green << "______________________________\n" << White;

    }


    static clsUser _ConvertLineToUserActionsObject(string Line, string Separator = "#//#")
    {
        clsUser ThisUser=clsUser::GetAddNewUserObject("");
        if (Line == "")
            return ThisUser;
        vector<string>vUsers = clsString::Split(Line, Separator);
        ThisUser.LoginDateAndTime = vUsers[0];
        ThisUser.UserName = vUsers[1];
        ThisUser.Password = vUsers[2];
        ThisUser.Permissions = stoi(vUsers[3]);
        ThisUser.Actions = stoi(vUsers[4]);
        ThisUser.LogOutDateAndTime = vUsers[5];
        return ThisUser;
    }


    static  vector <clsUser> _LoadUsersActionsDataLineFromFile()
    {
        vector <clsUser> vUsers;
        fstream MyFile;
        MyFile.open("UsersActions.txt", ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                vUsers.push_back(_ConvertLineToUserActionsObject(Line));
            }
            MyFile.close();
        }
        return vUsers;

    }



public:

	static void ShowUsersActionsScreen()
	{
        if (!clsScreen::_CheckAccessRights(clsUser::enPermissions::pUsersActions))
        {
            return;
        }
        clsScreen::_DrawScreenHeader("\t\tUsers Actions");

        vector<clsUser>vUsersActions = _LoadUsersActionsDataLineFromFile();
        for (clsUser& User : vUsersActions)
        {
            _PrintUserActionsCard(User);
        }


	}


};

