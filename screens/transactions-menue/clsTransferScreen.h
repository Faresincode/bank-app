#pragma once
#include "clsUtil.h";
#include "clsUser.h";
#include<iostream>
#include <iomanip>
#include "clsInputValidate.h";
#include "clsScreen.h";
#include "clsFindClientScreen.h";

using namespace std;


class clsTransferScreen : protected clsScreen
{

private:


	static string _ReadAccountNumber(string MessageToShow= "Please Enter Account Number ")
	{
		string AccountNumber;
		cout <<"\n" << setw(ScreenWidth) << "" << left << MessageToShow;
		AccountNumber = clsInputValidate::ReadString();
		if (AccountNumber == "exit")
			return "";
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\n" << setw(ScreenWidth) << "" << left << "Account number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
			if (AccountNumber == "exit")
				return "";
		}
		return AccountNumber;
	}

	static float ReadAmount(clsBankClient SourceClient)
	{
		float Amount;
		cout <<"\n" << setw(ScreenWidth) << "" << left << "Enter Transfer Amount? ";
		Amount = clsInputValidate::ReadNumber<float>();
		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\n" <<setw(ScreenWidth)<<""<<left << "Amount Exceeds the available Balance, Enter another Amount ? ";
			Amount = clsInputValidate::ReadNumber<float>();
		}
		return Amount;
	}


	static void _PrintClient(clsBankClient Client)
	{

		cout <<"\n"<<setw(ScreenWidth) << "" << left <<Blue<< "Client Card:"<<White;
		cout <<"\n"<<setw(ScreenWidth) << "" << left <<Green<< "___________________________________________"<<White;
		cout <<"\n"<<setw(ScreenWidth) << "" << left << "Full Name       : " <<Client.FullName();
		cout <<"\n"<<setw(ScreenWidth) << "" << left << "Account Number  : " << Client.AccountNumber();
		cout <<"\n"<<setw(ScreenWidth) << "" << left << "Account Balance : " << Client.AccountBalance;
		cout <<"\n" << setw(ScreenWidth) << "" << left <<Green<< "___________________________________________\n"<<White;

	}

public:

	static void ShowTransferScreen()
	{

		_DrawScreenHeader("\t\tTransfer Screen");
		cout << "\n" << setw(ScreenWidth) << "" << left <<Blue<< "To exit enter -> exit\n"<<White;

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
		if (SourceClient.IsEmpty())
			return;
		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());
		if (DestinationClient.IsEmpty())
			return;

		_PrintClient(DestinationClient);

		float Amount = ReadAmount(SourceClient);

		cout << "\n" << setw(ScreenWidth) << "" << left << "Are you sure you want to perform this operation? y/n? ";
		if (clsInputValidate::IsAnswerIsYes())
		{
			if (SourceClient.Transfer(Amount, DestinationClient,CurrentUser.UserName))
			{
				cout <<"\n" << setw(ScreenWidth) << "" << left << "Transfer done successfully\n";
			}
			else
			{
				cout << "\n" << setw(ScreenWidth) << "" << left << "Transfer Faild \n";
			}
		}

		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);

	}



};

