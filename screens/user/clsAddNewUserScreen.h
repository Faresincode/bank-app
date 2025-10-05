#pragma once
#include "clsUtil.h";
#include "clsUser.h";
#include<iostream>
#include <iomanip>
#include "clsInputValidate.h";
#include "clsScreen.h";


using namespace std;

class clsAddNewUserScreen :protected clsScreen
{

private:



    static void _ReadUserInfo(clsUser& User)
    {

        cout << "\n" << setw (ScreenWidth)<< "" << left << "Enter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\n" << setw(ScreenWidth) << "" << left << Green << "Enter Permissions\n";
        User.Permissions = _ReadPermissionsToSet();


    }

    static string _ReadUserName()
    {
        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter UserName? ";
        return clsInputValidate::ReadString();
    }

    static void _PrintUser(clsUser User)
    {
        cout << "\n";
        cout << setw(ScreenWidth) << "" << left << Green << "==========================================\n";
        cout << setw(ScreenWidth) << "" << left << Blue<<  "User Card : \n";
        cout << setw(ScreenWidth) << "" << left << Green << "==========================================\n" << White;
        cout << setw(ScreenWidth) << "" << left << "FirstName      : " << User.FirstName << "\n";
        cout << setw(ScreenWidth) << "" << left << "LastName       : " << User.LastName << "\n";
        cout << setw(ScreenWidth) << "" << left << "Email          : " << User.Email << "\n";
        cout << setw(ScreenWidth) << "" << left << "Phone          : " << User.Phone << "\n";
        cout << setw(ScreenWidth) << "" << left << "UserName       : " << User.UserName << "\n";
        cout << setw(ScreenWidth) << "" << left << "Password       : " << User.Password << "\n";
        cout << setw(ScreenWidth) << "" << left << "Permission     : " << User.Permissions << "\n";
        cout << setw(ScreenWidth) << "" << left << Green << "==========================================" << White;
        cout << endl;

    }

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer=' ';
        cout << "\n" << setw(ScreenWidth) << left << "" <<Blue<< "Do you want to give him full access to system? y/n? "<<White;
        if (clsInputValidate::IsAnswerIsYes())
        {
            return -1;
        }
        cout << "\n" << setw(ScreenWidth) << left << "" << "Do you want to give him access to: \n";
        cout << "\n" << setw(ScreenWidth) << left << "" << "Show Clients List? y/n? ";

        if (clsInputValidate::IsAnswerIsYes())
        {
            Permissions += clsUser::enPermissions::pListClients;
        }
        cout << "\n" << setw(ScreenWidth) << left << "" << "Add new Client? y/n? ";
        if (clsInputValidate::IsAnswerIsYes())
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }
        cout << "\n" << setw(ScreenWidth) << left << "" << "Delete Client? y/n? ";
        if (clsInputValidate::IsAnswerIsYes())
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }
        cout << "\n" << setw(ScreenWidth) << left << "" << "Update Clients? y/n? ";
        if (clsInputValidate::IsAnswerIsYes())
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }
        cout << "\n" << setw(ScreenWidth) << left << "" << "Find Client,y/n? ";
        if (clsInputValidate::IsAnswerIsYes())
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout<<"\n" << setw(ScreenWidth) << left << "" << "Transactions? y/n? ";
        if (clsInputValidate::IsAnswerIsYes())
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\n" << setw(ScreenWidth) << left << "" << "Manage Users? y/n? ";
        if (clsInputValidate::IsAnswerIsYes())
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }
        cout << "\n" << setw(ScreenWidth) << left << "" << "Show Login Register? y/n? ";
        if (clsInputValidate::IsAnswerIsYes())
        {
            Permissions += clsUser::enPermissions::pLoginRegisterScreen;
        }
        cout << "\n" << setw(ScreenWidth) << left << "" << "Users Actions? y/n? ";
        if (clsInputValidate::IsAnswerIsYes())
        {
            Permissions += clsUser::enPermissions::pUsersActions;
        }

        return Permissions;
    }

public:


    static void ShowAddNewUserScreen()
    {

        clsScreen::_DrawScreenHeader("\t\tAdd New User Screen");
        string UserName = _ReadUserName();
        if (UserName=="exit")
            return;
        while (clsUser::IsUserExist(UserName))
        {
            cout << "\n" << setw(ScreenWidth) << "" << left << "Account Number Is Already Used, Choose another one: ";
            UserName = _ReadUserName();
        }
        if (UserName == "exit")
            return;
        clsUser NewUser= clsUser::GetAddNewUserObject(UserName);
        _ReadUserInfo(NewUser);        
        clsUser::enSaveResults SaveResult = NewUser.Save();

        switch (SaveResult)
        {
            case clsUser::enSaveResults::svSucceeded:
                cout << "\n" << setw(ScreenWidth) << "" << left<< Green << "User added Successfully :-)\n" << White;
                _PrintUser(NewUser);
                break;
            case clsUser::enSaveResults::svFaildEmptyObject:
                cout  << "\n" << setw(ScreenWidth) << "" << left << clsUtil::Yellow()<<"Error account was not saved because it's Empty\n" << White;
                break;
            case clsUser::enSaveResults::svFaildUserExists:
                cout <<  "\n" << setw(ScreenWidth) << "" << left <<Red << "Error account was not saved because account number is already used!\n" << White;
                break;

        }



    }





};

