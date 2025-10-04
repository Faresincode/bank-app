#pragma once
#include <iostream>
#include <iomanip>

#include "clsScreen.h"
#include "clsUser.h"
#include "clsDate.h";

using namespace std;

class clsLoginsRegisterScreen :protected clsScreen
{

private:

	static void _DrawLoginRegisterScreenHeader()
	{

		cout << "\n" << setw(15) << "" << Green << "______________________________________________________________________________________________________________________\n\n" << White;
		cout << setw(16) << "" << left
			<< Green << "| " << Blue << setw(25) << "Login Date And Time" << left
			<< Green << "| " << Blue << setw(25) << "User Name" << left
			<< Green << "| " << Blue << setw(20) << "Password" << left
			<< Green << "| " << Blue << setw(13) << "Permissions" << left
			<< Green << "| " << Blue << setw(25) << "Logout Date And Time" << left;

		cout << "\n" << setw(15) << "" << Green << "______________________________________________________________________________________________________________________\n\n" << White;

	}


	static void _PrintUserRegisterLineRecord(clsUser::stLoginRegisterRecord User)
	{
		cout << setw(16) << "" << left
			<< Green << "| "  << White << setw(25) << User.LoginDateTime << left
			<< Green << "| "  << White << setw(25) << User.UserName << left
			<< Green << "| "  << White << setw(20) << User.Password << left
			<< Green << "| "  << White << setw(13) << User.Permissions << left
			<< Green << "| "  << White  << setw(25) << User.LogoutDateTime<< left;
	}


public:


	static void  ShowLoginRegisterScreen()
	{
		if (!clsScreen::_CheckAccessRights(clsUser::enPermissions::pLoginRegisterScreen))
		{
			return;
		}
		vector<clsUser::stLoginRegisterRecord>vLoginRegisterRecord = clsUser::GetLoginRegisterList();
		string Title = "\t  Login Register Users Screen";
		string SubTitle = "\t\t(" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";
		clsScreen::_DrawScreenHeader(Title, SubTitle);

		if (vLoginRegisterRecord.size() == 0)
		{
			cout << setw(ScreenWidth) << "" << left << Red << "No User Login Register Available\n" << White;
		}
		else
		{
			_DrawLoginRegisterScreenHeader();
			for (clsUser::stLoginRegisterRecord &User : vLoginRegisterRecord)
			{
				_PrintUserRegisterLineRecord(User);
				cout << endl;
			}
			cout << setw(15) << "" << Green << "______________________________________________________________________________________________________________________\n" << White;

		}

	
	}






};

