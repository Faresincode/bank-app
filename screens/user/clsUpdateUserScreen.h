#pragma once

#include<iostream>
#include <iomanip>
#include "clsInputValidate.h";
#include "clsScreen.h";
#include "clsUtil.h";
#include "clsUser.h";

using namespace std;


class clsUpdateUserScreen : protected clsScreen
{

private:
	static int _ReadPermissionsToSet()
	{

		int Permissions = 0;
		char Answer = ' ';
		cout << "\n" << setw(ScreenWidth) << "" << left << Green << "Read Permissions\n";
		cout << "\n" << setw(ScreenWidth) << left << "" << Blue << "Do you want to give him full access to system? y/n? " << White;
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

		cout << "\n" << setw(ScreenWidth) << left << "" << "Transactions? y/n? ";
		if (clsInputValidate::IsAnswerIsYes())
		{
			Permissions += clsUser::enPermissions::pTranactions;
		}

		cout << "\n" << setw(ScreenWidth) << left << "" << "Manage Users? y/n? ";
		if (clsInputValidate::IsAnswerIsYes())
		{
			Permissions += clsUser::enPermissions::pManageUsers;
		}
		cout << "\n" << setw(ScreenWidth) << left << "" << "LoginRegisterScreen? y/n? ";
		if (clsInputValidate::IsAnswerIsYes())
		{
			Permissions += clsUser::enPermissions::pLoginRegisterScreen;
		}
		cout << "\n" << setw(ScreenWidth) << left << "" << "pUsersActions? y/n? ";
		if (clsInputValidate::IsAnswerIsYes())
		{
			Permissions += clsUser::enPermissions::pUsersActions;
		}


		return Permissions;

	}

	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\n" << setw(ScreenWidth) << "" << left << "Enter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\n" << setw(ScreenWidth) << "" << left << "Enter LastName: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Password: ";
		User.Password = clsInputValidate::ReadString();

		User.Permissions = _ReadPermissionsToSet();


	}

	static string _ReadUserName()
	{
		cout << "\n" <<setw(ScreenWidth) << "" << left << "Enter UserName? ";
		string UserName = clsInputValidate::ReadString();
		return UserName;
	}

	static void _PrintNotFoundLine(string NotFoundVariable = "User", string TextColor = Yellow)
	{
		cout << "\n" << TextColor << clsUtil::Centre() << "" << left << " " << NotFoundVariable << " not found :-) " << White;
	}

	static void _PrintUser(clsUser User)
	{
		cout << "\n";
		cout << setw(ScreenWidth) << "" << left << Green << "==========================================\n";
		cout << setw(ScreenWidth) << "" << left << Blue << " Client Card : \n";
		cout << setw(ScreenWidth) << "" << left << Green<< "==========================================\n" << White;
		cout << setw(ScreenWidth) << "" << left << " UserName       : " << User.UserName << "\n";
		cout << setw(ScreenWidth) << "" << left << " Full Name      : " << User.FullName() << "\n";
		cout << setw(ScreenWidth) << "" << left << " Email          : " << User.Email << "\n";
		cout << setw(ScreenWidth) << "" << left << " Phone          : " << User.Phone << "\n";
		cout << setw(ScreenWidth) << "" << left << " Password       : " << User.Password << "\n";
		cout << setw(ScreenWidth) << "" << left << " Permission     : " << User.Permissions << "\n";
		cout << setw(ScreenWidth) << "" << left << Green << "==========================================" << White;
		cout << endl;

	}

	enum enWhatToUpdate { eFirstName = 1, eLastName = 2, eEmail = 3, ePhone = 4, ePassword = 5,ePermissions=6 ,eAll = 7 };

	static void _PerformUpdateMenuScreen(enWhatToUpdate WhatToUpdate, clsUser& User)
	{
		cout << "\n" << setw(ScreenWidth) << "" << left <<Green << "Update User Info:";
		cout << "__________________________________________\n"<<White;
		switch (WhatToUpdate)
		{
		case enWhatToUpdate::eFirstName:
		{
			cout << "\n" << setw(ScreenWidth)<<""<<left << "Enter FirstName : ";
			User.FirstName = clsInputValidate::ReadString();
			break;
		}
		case enWhatToUpdate::eLastName:
		{
			cout << "\n" << setw(ScreenWidth) << "" << left << "Enter LastName: ";
			User.LastName = clsInputValidate::ReadString();
			break;
		}

		case enWhatToUpdate::eEmail:
		{
			cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Email: ";
			User.Email = clsInputValidate::ReadString();
			break;
		}
		case enWhatToUpdate::ePhone:
		{
			cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Phone: ";

			User.Phone = clsInputValidate::ReadString();

			break;
		}
		case enWhatToUpdate::ePassword:
		{
			cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Password: ";
			User.Password = clsInputValidate::ReadString();
			break;
		}
		case enWhatToUpdate::ePermissions:
			User.Permissions = _ReadPermissionsToSet();
			break;
		case enWhatToUpdate::eAll:
		{
			_ReadUserInfo(User);
			break;
		}
		default:
		{
			_ReadUserInfo(User);
			break;
		}


		}

	}

	static void _ShowUpdateMenuScreen(clsUser& User)
	{
		cout << setw(ScreenWidth) << "" << left << Green << "==========================================\n";
		cout << setw(ScreenWidth) << "" << left << Red << "\t\tUpdate Menu Screen \n";
		cout << setw(ScreenWidth) << "" << left << Green<< "==========================================\n" << White;
		cout << setw(ScreenWidth) << "" << left << " [1] FirstName       \n";
		cout << setw(ScreenWidth) << "" << left << " [2] LastName        \n";
		cout << setw(ScreenWidth) << "" << left << " [3] Email           \n";
		cout << setw(ScreenWidth) << "" << left << " [4] Phone           \n";
		cout << setw(ScreenWidth) << "" << left << " [5] Password        \n";
		cout << setw(ScreenWidth) << "" << left << " [6] Permissions        \n";
		cout << setw(ScreenWidth) << "" << left << " [7] All Client Info \n";
		cout << setw(ScreenWidth) << "" << left << Green << "==========================================\n\n";
		cout << setw(ScreenWidth) << "" << left << Yellow << "What do you want to update (answer as following menu from  1 to 7 ) : " << White;

		_PerformUpdateMenuScreen((enWhatToUpdate)clsInputValidate::ReadNumberBetween<short>(1, 7), User);
	}

public:


	static void ShowUpdateUserScreen()
	{
		clsScreen::_DrawScreenHeader("\t\tUpdate User Screen ");
		cout << "\n" << setw(ScreenWidth) << "" << left << "(To exit enter exit)\n";
		string UserName = _ReadUserName();
		if (UserName == "exit")
			return;
		while (!clsUser::IsUserExist(UserName))
		{
			_PrintNotFoundLine();
			cout << "Choose another one: ";
			UserName = _ReadUserName();
		}
		if (UserName == "exit")
			return;
		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);
		_ShowUpdateMenuScreen(User) ;
		clsUser::enSaveResults SaveResult;
		SaveResult = User.Save();
		switch (SaveResult)
		{
		case clsUser::svFaildEmptyObject:
			cout << "\n" << setw(ScreenWidth) << "" << left << "User Not Updated because Empty Object\n";

			break;
		case clsUser::svSucceeded:
			cout << "\n" << setw(ScreenWidth) << "" << left <<Green<< "User updated succesfuly :-)\n"<<White;
			_PrintUser(User);
			break;
		default:
			_PrintNotFoundLine();
			break;
		}


	}



};

