
#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h";
#include "clsMainScreen.h";
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include "clsUtil.h";
#include "clsUser.h";


using namespace std;


class clsListUsersScreen : protected clsScreen
{

private:

    static void _PrintUsersRecordLine(clsUser User)
    {

        cout << setw(1) << left << "" << Green << "| " << White<< setw(25) << left << User.UserName;
        cout << Green << "| " << White << setw(25) << left << User.FullName();
        cout << Green << "| " << White << setw(35) << left << User.Email;
        cout << Green << "| " << White << setw(15) << left << User.Phone;
        cout << Green << "| " << White << setw(20) << left << User.Password;
        cout << Green << "| " << White << setw(11) << left << User.Permissions;

    }

    static void _PrintUsersHeader()
    {

        cout << "\n" << setw(1) << "" <<left<<Green<< "_________________________________________________________________________________________________________________________________________________\n" << endl << White;

        cout << setw(1) << left << "" << Green << "| " << White<< left << setw(25) << "UserName";
        cout << Green << "| " << White << left << setw(25) << "Full Name";
        cout << Green << "| " << White << left << setw(35) << "Email";
        cout << Green << "| " << White << left << setw(15) << "Phone";
        cout << Green << "| " << White << left << setw(20) << "Password";
        cout << Green << "| " << White << left << setw(11) << "Permission";
        cout << Green;
        cout << "\n" << setw(1) << "" << left << Green << "_________________________________________________________________________________________________________________________________________________\n" << endl << White;
    }

public:

	static void ShowListUsersScreen()
	{

		vector<clsUser>vUsers=clsUser::GetUsersList();

		string Title = "\t\tUser List Screen";
		string SubTitle = "\t\t  (" + to_string(vUsers.size()) + ") Client(s).";

		clsScreen::_DrawScreenHeader(Title,SubTitle);

		if (vUsers.size() == 0)
		{
			cout << Red<<"\n" << setw(ScreenWidth) << "" << left << "No user available in the system"<<White;
		}
		else
		{
            _PrintUsersHeader();
			for (clsUser& user : vUsers)
			{
                _PrintUsersRecordLine(user);
                cout << endl;
			}
            cout << setw(1) << "" << left << Green<< "_________________________________________________________________________________________________________________________________________________\n"<< White << endl ;

		}

	}




};

