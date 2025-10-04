
#pragma once
#include<iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h";
#include "clsCurrency.h";
#include "clsInputValidate.h";


using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{

private:

	enum enFindBy { eCode = 1, eCountry = 2, exit = 0 };
	
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout <<"\n"<<setw(ScreenWidth) << "" << left <<Blue<< "Currency Card";
		cout << "\n" << setw(ScreenWidth) << "" << left << Green << "_______________________________________________________\n";
		cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Country       : "<<White<<Currency.Country();
		cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Currency Code : "<<White<<Currency.CurrencyCode();
		cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Currency Name : "<<White<<Currency.CurrencyName();
		cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Rate/(1$)     : " << White<<Currency.Rate();
		cout << "\n" << setw(ScreenWidth) << "" << left << Green << "_______________________________________________________\n";

	}

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout <<"\n" << setw(ScreenWidth) << "" << left << "Currency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\n" << setw(ScreenWidth) << "" << left << "Currency Was not Found :-(\n";
		}
	}

	static enFindBy _ReadFindCurrencySubMenu()
	{
		cout <<"\n" << setw(ScreenWidth) << "" << left << "Find By [1] Code ? [2] Country ? ";
		return (enFindBy)clsInputValidate::ReadNumberBetween<short>(1,2,"invalid enter number between 1 and 2: ");
	}

	static string _ReadCurrencyCode()
	{
		cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Currency code: ";
		return clsInputValidate::ReadString();

	}

	static string _ReadCountry()
	{
		cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Country: ";
		return clsInputValidate::ReadString();
	}
	


public:


	static void ShowFindCurrencyScreen()
	{

		_DrawScreenHeader("\t  Find Currency Screen");
		enFindBy Choice = _ReadFindCurrencySubMenu();
		switch (Choice)
		{
		case enFindBy::eCode:
		{
			clsCurrency Currency = clsCurrency::FindByCode(_ReadCurrencyCode());
			_ShowResults(Currency);
			break;
		}
		case enFindBy::eCountry:
		{
			clsCurrency Currency = clsCurrency::FindByCountry(_ReadCountry());
			_ShowResults(Currency);
			break;
		}
		case enFindBy::exit:
			return;

		}

	}



	


};

