#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "clsInputValidate.h";
#include "clsUtil.h";
#include "clsScreen.h";
#include "clsDate.h";
#include "clsBankClient.h";
#include "Global.h";

using namespace std;



class clsInterTransLogScreen : protected clsScreen
{

private:

	static void _PrintTableLine()
	{

		cout << setw(1) << "" << left << Green << "___________________________________________________________________________________________________________________________________________________\n" << White;

	}

	static void _DrawInterTransTableHeader()
	{
		cout << "\n";
		_PrintTableLine();
		cout << "\n" << setw(1) << "" << left << Green << "| " << White << left << setw(22) << "Transfer Date Time";
		cout << Green << "| " << White << left << setw(23) << "S.IBAN";
		cout << Green << "| " << White << left << setw(10) << "S.Swift";
		cout << Green << "| " << White << left << setw(23) << "D.IBAN";
		cout << Green << "| " << White << left << setw(10) << "D.swift";
		cout << Green << "| " << White << left << setw(10) << "Amount";
		cout << Green << "| " << White << left << setw(10) << "Currency";
		cout << Green << "| " << White << left << setw(12) << "S.Balance";
		cout << Green << "| " << White << left << setw(10) << "User";
		cout << "\n";
		_PrintTableLine();
	}

	static void _PrintInterTransLogRecord(clsBankClient::stInterTransLog InterTrans)
	{

		cout << "\n" << setw(1) << "" << left << Green << "| " << White << left << setw(22) << InterTrans.InterTransferDateTime;
		cout << Green << "| " << White << left << setw(23) << InterTrans.SenderIBAN;
		cout << Green << "| " << White << left << setw(10) << InterTrans.SenderSwiftCode;
		cout << Green << "| " << White << left << setw(23) << InterTrans.RecipientIBAN;
		cout << Green << "| " << White << left << setw(10) << InterTrans.RecipientSwiftCode;
		cout << Green << "| " << White << left << setw(10) << InterTrans.SendingAmount;
		cout << Green << "| " << White << left << setw(10) << InterTrans.CurrencyCode;
		cout << Green << "| " << White << left << setw(12) << InterTrans.SenderAccountBalance;
		cout << Green << "| " << White << left << setw(10) << InterTrans.ResponsibleActionUser;

	}



public:

	static void ShowInterTransLogScreen()
	{

		vector<clsBankClient::stInterTransLog>vInterTransLogRecords = clsBankClient::GetInterTransLogList();
		string Title = "\tInternational Transfer Log Screen";
		string Subtitle = "\t\t(" + to_string(vInterTransLogRecords.size()) + ") Records";

		clsScreen::_DrawScreenHeader(Title, Subtitle);

		if (vInterTransLogRecords.size() == 0)
		{
			cout << "\n" << setw(ScreenWidth) << "" << left << Red << "No International Transfer Available in the system\n" << White;
		}
		else
		{
			_DrawInterTransTableHeader();
			for (clsBankClient::stInterTransLog& Record : vInterTransLogRecords)
			{

				_PrintInterTransLogRecord(Record);
				cout << endl;
			}

			_PrintTableLine();
		}




	}



};

