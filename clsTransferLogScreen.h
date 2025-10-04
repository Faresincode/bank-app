#pragma once
#include<iostream>
#include <iomanip>
#include "clsInputValidate.h";
#include "clsScreen.h";
#include "clsBankClient.h";

using namespace std;




class clsTransferLogScreen :protected clsScreen
{


private:


	static void _PrintTableLine()
	{

		cout << setw(20) << "" << left << Green << "______________________________________________________________________________________________________________________\n" << White;

	}

	static void _DrawTransferTableHeader()
	{
		cout << "\n";
		_PrintTableLine();
		cout << "\n" << setw(21) << "" << left << Green << "| " << White << left << setw(20) << "Transfer Date Time";
		cout << Green << "| " << White << left << setw(13) << "S.Account";
		cout << Green << "| " << White << left << setw(13) << "D.Account";
		cout << Green << "| " << White << left << setw(15) << "Amount";
		cout << Green << "| " << White << left << setw(15) << "S.Balance";
		cout << Green << "| " << White << left << setw(15) << "D.Balance";
		cout << Green << "| " << White << left << setw(10) << "User";
		cout << "\n";
		_PrintTableLine();
	}

	static void _PrintTransferLogRecord(clsBankClient::stTransferLogRecord TransferLogRecord)
	{

		cout << "\n" << setw(21) << "" << left << Green << "| " << White << left << setw(20) << TransferLogRecord.SystemDateTime;
		cout << Green << "| " << White << left << setw(13) << TransferLogRecord.SourceAccountNumber;
		cout << Green << "| " << White << left << setw(13) << TransferLogRecord.DestinationAccountNumber;
		cout << Green << "| " << White << left << setw(15) << TransferLogRecord.TransferAmount;
		cout << Green << "| " << White << left << setw(15) << TransferLogRecord.SourceAccountBalance;
		cout << Green << "| " << White << left << setw(15) << TransferLogRecord.DestinationAccountBalance;
		cout << Green << "| " << White << left << setw(10) << TransferLogRecord.ResponsibleActionUserName;

	}




public:


	static void ShowTransferLogScreen()
	{

		vector<clsBankClient::stTransferLogRecord>vTransferLogRecords = clsBankClient::GetTransfersLogList();
		string Title = "\t\tTransfer Log Screen";
		string Subtitle = "\t\t     (" + to_string(vTransferLogRecords.size()) + ") Records";

		clsScreen::_DrawScreenHeader(Title, Subtitle);

		if (vTransferLogRecords.size() == 0)
		{
			cout << "\n" << setw(ScreenWidth) << "" << left << Red << "No Transfer Available in the system\n" << White;
		}
		else
		{
			_DrawTransferTableHeader();
			for (clsBankClient::stTransferLogRecord& Record : vTransferLogRecords)
			{

				_PrintTransferLogRecord(Record);
				cout << endl;
			}

			_PrintTableLine();
		}




	}




};

