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


class clsInternationalTransferScreen : protected clsScreen 
{
private:


	static double _ReadSendingAmount()
	{
		double SendingAmount = 0;
		cout <<"\n" << setw(ScreenWidth) << "" << left << "Enter Sending Amount : ";
		SendingAmount = clsInputValidate::ReadNumber<double>();
		return SendingAmount;
	}
	static string _ReadIBAN()
	{
		string IbanNumber="";
		cout <<"\n" << setw(ScreenWidth) << "" << left << "Enter Account IBAN : ";
		IbanNumber = clsInputValidate::ReadString();


		return IbanNumber;
	}
	static string _ReadSwiftCode()
	{
		string SwiftCode = "";
		cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Swift code : ";
		SwiftCode = clsInputValidate::ReadString();

		return SwiftCode;
	}

	static clsBankClient::stInterTransferClientInfo _ReadSenderInfo()
	{
		cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Read Sender Info\n\n"<<White;
		string SenderIBAN = _ReadIBAN();
		while (!clsBankClient::IsInterClientExist(SenderIBAN, SenderFileName))
		{
			cout <<setw(ScreenWidth)<<""<<left <<Yellow<< "Error No account with this IBAN§ try Again : ";
			SenderIBAN = _ReadIBAN();
		}
		clsBankClient::stInterTransferClientInfo RecipientInfo;
		RecipientInfo=clsBankClient::FindByIBAN(SenderIBAN, SenderFileName);

		return RecipientInfo;
	}

	static clsBankClient::stInterTransferClientInfo _ReadRecipientInfo(clsBankClient::stInterTransferClientInfo RecipientClient)
	{
		cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Read Recipient Info\n\n" << White;

		string ReciepientIBAN = _ReadIBAN();
		string RecipientSwiftCode = _ReadSwiftCode();

		while (!clsBankClient::IsInterClientExistByIBANAndSwift(ReciepientIBAN, RecipientSwiftCode, RecipientFileName) || RecipientClient.BankClientInfo.IBAN== ReciepientIBAN)
		{
			cout << "\n"<<setw(ScreenWidth)<<""<<left <<Red<< "Invalid IBAN/SwiftCode Try Again\n"<<White;
			ReciepientIBAN = _ReadIBAN();
			RecipientSwiftCode = _ReadSwiftCode();

		}
		clsBankClient::stInterTransferClientInfo RecipientInfo;
		RecipientInfo = clsBankClient::FindByIBANAndSwift(ReciepientIBAN, RecipientSwiftCode,RecipientFileName);

		return RecipientInfo;
	}

	static void _InterTransDetailsTicket(clsBankClient::stInterTransferClientInfo SenderClient,clsBankClient::stInterTransferClientInfo BeneficiaryClient, double Amount)
	{
		cout << "\n" << setw(ScreenWidth) << "" << left << Green << "================================================================";
		cout << "\n" << setw(ScreenWidth) << "" << left << Blue <<  "\t\tCurrent Transaction Details Ticket";
		cout << "\n" << setw(ScreenWidth) << "" << left << Green << "================================================================\n";
		cout << "\n" << setw(ScreenWidth) << "" << left << Green<<"================================================================\n";
		cout << "\n" << setw(ScreenWidth) << "" << left << Blue<<"\t\t\tSender Details\n";
		cout << "\n" << setw(ScreenWidth) << "" << left << Green<<"================================================================\n"<<White;
		cout << "\n" << setw(ScreenWidth) << "" << left << "First Name             : " << SenderClient.FirstName;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Last Name              : " << SenderClient.LastName;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Client Country         : " << SenderClient.ClientAddress.Country;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Client City            : " << SenderClient.ClientAddress.City;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Client Village         : " << SenderClient.ClientAddress.Village;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Client street Address  : " << SenderClient.ClientAddress.StreetAddress;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Bank Name              : " << SenderClient.BankClientInfo.BankName;
		cout << "\n" << setw(ScreenWidth) << "" << left << "IBAN Number            : " << SenderClient.BankClientInfo.IBAN;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Swift Code             : " << SenderClient.BankClientInfo.SwiftCode;
		cout << "\n" << setw(ScreenWidth) << "" << left << "BankCountry            : " << SenderClient.BankClientInfo.BankAddress.Country;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Bank City              : " << SenderClient.BankClientInfo.BankAddress.City;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Bank Village           : " << SenderClient.BankClientInfo.BankAddress.Village;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Bank Street Address    : " << SenderClient.BankClientInfo.BankAddress.StreetAddress;
		cout << "\n\n" << setw(ScreenWidth) << "" << left << Green <<"================================================================\n"<<White;
		cout << "\n" << setw(ScreenWidth) << "" << left << Blue<<"\t\t\tBeneficiary Details\n";
		cout << "\n" << setw(ScreenWidth) << "" << left <<Green   <<"=================================================================\n"<<White;
		cout << "\n" << setw(ScreenWidth) << "" << left << "First Name             : " << BeneficiaryClient.FirstName;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Last Name              : " << BeneficiaryClient.LastName;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Client Country         : " << BeneficiaryClient.ClientAddress.Country;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Client City            : " << BeneficiaryClient.ClientAddress.City;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Client Village         : " << BeneficiaryClient.ClientAddress.Village;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Client street Address  : " << BeneficiaryClient.ClientAddress.StreetAddress;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Bank Name              : " << BeneficiaryClient.BankClientInfo.BankName;
		cout << "\n" << setw(ScreenWidth) << "" << left << "IBAN Number            : " << BeneficiaryClient.BankClientInfo.IBAN;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Swift Code             : " << BeneficiaryClient.BankClientInfo.SwiftCode;
		cout << "\n" << setw(ScreenWidth) << "" << left << "BankCountry            : " << BeneficiaryClient.BankClientInfo.BankAddress.Country;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Bank City              : " << BeneficiaryClient.BankClientInfo.BankAddress.City;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Bank Village           : " << BeneficiaryClient.BankClientInfo.BankAddress.Village;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Bank Street Address    : " << BeneficiaryClient.BankClientInfo.BankAddress.StreetAddress;
		cout << "\n\n" << setw(ScreenWidth) << "" << left << Green << "======================== Transaction Details ===================\n" << White;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Sending Amount         : " << Amount;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Currency code          : " << SenderClient.BankClientInfo.CurrencyCode;
		clsCurrency Currency1 = Currency1.FindByCountry(SenderClient.ClientAddress.Country);
		double TaxAmount = (Amount * Currency1.GetInterTransTaxesPercentage()) / 100;
		double BankFeesAmount = (Amount * SenderClient.BankClientInfo.InterTransBankFees) / 100;
		cout << "\n" << setw(ScreenWidth) << "" << left << "bank fee  Amount       : " << BankFeesAmount;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Tax Amount             : " << TaxAmount;
		cout << "\n" << setw(ScreenWidth) << "" << left << "Total Withdraw Amount  : " << Amount + TaxAmount + BankFeesAmount;
		cout << "\n" << setw(ScreenWidth) << "" << left << "New Balance            : " << SenderClient.BankClientInfo.AccountBalance;
		cout << "\n" << setw(ScreenWidth) << "" << left << Blue<<"This Transaction Was Made at : "<<clsDate::GetSystemDateTimeString();
		cout << "\n\n" << setw(ScreenWidth) << "" << left <<Green<< "================================================================\n\n"<<White;


	}

	static void _PrintInterSenderCard(clsBankClient::stInterTransferClientInfo InterClient)
	 {


		 cout << "\n\n" << setw(ScreenWidth) << "" << left       << Green<<"================================================\n";
		 cout << "\n" << setw(ScreenWidth) << "" << left <<Blue << "\tCurrent inter Client Details Screen"<<Green;
		 cout << "\n\n" << setw(ScreenWidth) << "" << left       << "================================================\n";
		 
		 cout << "\n" << setw(ScreenWidth) << "" << left <<Green<<"================================================================\n";
		 cout << "\n" << setw(ScreenWidth) << "" << left <<Blue<< "\t\t\tSender Details\n";
		 cout << "\n" << setw(ScreenWidth) << "" << left <<Green<< "================================================================\n"<<White;

		 cout<<"\n" << setw(ScreenWidth) << "" << left <<Blue<< "First Name            : "<<White << InterClient.FirstName;
		 cout<<"\n" << setw(ScreenWidth) << "" << left <<Blue<< "Last Name             : "<<White << InterClient.LastName;
		 cout<<"\n" << setw(ScreenWidth) << "" << left <<Blue<< "Client Country        : "<<White << InterClient.ClientAddress.Country;
		 cout<<"\n" << setw(ScreenWidth) << "" << left <<Blue<< "Client City           : "<<White << InterClient.ClientAddress.City;
		 cout<<"\n" << setw(ScreenWidth) << "" << left <<Blue<< "Client Village        : "<<White << InterClient.ClientAddress.Village;
		 cout<<"\n" << setw(ScreenWidth) << "" << left <<Blue<< "Client street Address : "<<White << InterClient.ClientAddress.StreetAddress;
		 cout<<"\n" << setw(ScreenWidth) << "" << left << Blue<<"Bank Name             : " <<White<< InterClient.BankClientInfo.BankName;
		 cout<<"\n" << setw(ScreenWidth) << "" << left << Blue<<"IBAN Number           : " << White << InterClient.BankClientInfo.IBAN;
		 cout<<"\n" << setw(ScreenWidth) << "" << left << Blue<<"Swift Code            : " << White <<InterClient.BankClientInfo.SwiftCode;
		 cout<<"\n" << setw(ScreenWidth) << "" << left << Blue<<"Account Balance       : "<<White << InterClient.BankClientInfo.AccountBalance;
		 cout<<"\n" << setw(ScreenWidth) << "" << left << Blue<<"Account Currency      : "<<White << InterClient.BankClientInfo.CurrencyCode;
		 cout<<"\n" << setw(ScreenWidth) << "" << left << Blue<<"BankCountry           : "<<White << InterClient.BankClientInfo.BankAddress.Country;
		 cout<<"\n" << setw(ScreenWidth) << "" << left << Blue<<"Bank City             : "<<White << InterClient.BankClientInfo.BankAddress.City;
		 cout<<"\n" << setw(ScreenWidth) << "" << left << Blue<<"Bank Village          : "<<White << InterClient.BankClientInfo.BankAddress.Village;
		 cout<<"\n" << setw(ScreenWidth) << "" << left << Blue<<"Bank Street Address   : "<<White << InterClient.BankClientInfo.BankAddress.StreetAddress;

		 cout << "\n\n" << setw(ScreenWidth) << "" << left <<Green<< "================================================================\n\n"<<White;


	 }

	static void _PrintInterRecipientCard(clsBankClient::stInterTransferClientInfo InterRecipient)
	 {

		 cout << "\n" << setw(ScreenWidth) << "" << left << Green << "================================================================\n";
		 cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "\t\t\tRecipient Details\n";
		 cout << "\n" << setw(ScreenWidth) << "" << left << Green << "================================================================\n" << White;

		 cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "First Name            : " << White << InterRecipient.FirstName;
		 cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Last Name             : " << White << InterRecipient.LastName;
		 cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Bank Name             : " << White << InterRecipient.BankClientInfo.BankName;
		 cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "IBAN Number           : " << White << InterRecipient.BankClientInfo.IBAN;
		 cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Swift Code            : " << White << InterRecipient.BankClientInfo.SwiftCode;
		 cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Account Currency      : " << White << InterRecipient.BankClientInfo.CurrencyCode;
		 cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "BankCountry           : " << White << InterRecipient.BankClientInfo.BankAddress.Country;
		 cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Bank City             : " << White << InterRecipient.BankClientInfo.BankAddress.City;
		 cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Bank Village          : " << White << InterRecipient.BankClientInfo.BankAddress.Village;
		 cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Bank Street Address   : " << White << InterRecipient.BankClientInfo.BankAddress.StreetAddress;

		 cout << "\n\n" << setw(ScreenWidth) << "" << left << Green << "================================================================\n\n" << White;



	 }

	static void _PrintSedersTableHeader()
	{
		cout <<"\n\n" << setw(ScreenWidth) << "" << left <<Green<< "\tInternational Sender Clients List\n";

		cout << "\n" << setw(20) << left << "" <<Green<< "_____________________________________________________________________________________________________________________\n\n";
		cout << White;

		cout << setw(21) << left << "" << Green << "| " << Blue << setw(25) << "IBAN"<<left;
		cout << Green << "| " << Blue << setw(25) << "Full Name"<<left;
		cout << Green << "| " << Blue << setw(15) << "Swift Code"<<left;
		cout << Green << "| " << Blue << setw(20) << "Balance"<<left;
		cout << Green << "| " << Blue << setw(11) << "Currency"<<left;
		cout << Green;
		cout << "\n" << setw(20) << left << "" << "_____________________________________________________________________________________________________________________\n\n"<<White; 


	}

	static void _PrintSmallSendersRecords(clsBankClient::stInterTransferClientInfo SenderInfo)
	{
		string FullName = SenderInfo.FirstName +" "+ SenderInfo.LastName;
		cout << setw(21) << left << "" << Green << "| " << White  << setw(25) << SenderInfo.BankClientInfo.IBAN<<left;
		cout << Green << "| " << White  << setw(25) << FullName <<left;
		cout << Green << "| " << White  << setw(15) << SenderInfo.BankClientInfo.SwiftCode<<left;
		cout << Green << "| " << White  << setw(20) << SenderInfo.BankClientInfo.AccountBalance<<left;
		cout << Green << "| " << White  << setw(11) << SenderInfo.BankClientInfo.CurrencyCode<<left;
		cout << Green;

	}

	static void _PrintSmallSenderClientsCard()
	{
		vector<clsBankClient::stInterTransferClientInfo>vSendersInfo;
		vSendersInfo = clsBankClient::GetInterTransClientsList(SenderFileName);

		_PrintSedersTableHeader();
		for (clsBankClient::stInterTransferClientInfo& Sender : vSendersInfo)
		{
			_PrintSmallSendersRecords(Sender);
			cout << endl;

		}
		cout << setw(20) << left << "" << Green << "_____________________________________________________________________________________________________________________\n\n"<<White;


	}


public:

	static void ShowInternationalTransferScreen()
	{ 
	
		clsScreen::_DrawScreenHeader("\tInternational Transfer Screen");

		_PrintSmallSenderClientsCard();
		clsBankClient::stInterTransferClientInfo SenderClient= _ReadSenderInfo();
		_PrintInterSenderCard(SenderClient);

		clsBankClient::stInterTransferClientInfo RecipientClient = _ReadRecipientInfo(SenderClient);
		_PrintInterRecipientCard(RecipientClient);

		float SendingAmount = _ReadSendingAmount();
		clsBankClient Client1 = clsBankClient::GetAddNewClientObject("");
		if (Client1.InterTransfer(SenderClient, RecipientClient, SendingAmount))
		{
			cout << "\n" << setw(ScreenWidth) << "" << left << Green << "Amount Send Successfully\n\n" << White;
			_InterTransDetailsTicket(SenderClient, RecipientClient, SendingAmount);

		}
		else
		{
			cout <<"\n\n" << setw(ScreenWidth) << "" << left << Red << "Amount Not enough To make this international transfer\n\n" << White;
		}


	}







};

