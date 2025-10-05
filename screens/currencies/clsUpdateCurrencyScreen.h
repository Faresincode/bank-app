#pragma once
#include <iostream>
#include "clsScreen.h";
#include "iomanip";
#include "clsInputValidate.h";
#include "clsCurrency.h";

using namespace std;


class clsUpdateCurrencyScreen : protected clsScreen
{

private:

	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Currency Card";
		cout << "\n" << setw(ScreenWidth) << "" << left << Green << "_______________________________________________________";
		cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Country       : " << White << Currency.Country();
		cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Currency Code : " << White << Currency.CurrencyCode();
		cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Currency Name : " << White << Currency.CurrencyName();
		cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Rate/(1$)     : " << White << Currency.Rate();
		cout << "\n" << setw(ScreenWidth) << "" << left << Green << "_______________________________________________________\n"<<White;

	}

	static string _ReadCurrencyCode()
	{

		cout <<"\n" << setw(ScreenWidth) << "" << left << "Enter Currency code : ";
		return clsInputValidate::ReadString();
	}

	static float _ReadRate()
	{
		cout <<"\n" << setw(ScreenWidth) << "" << left << "Enter New Rate: ";
		float NewRate = 0;
		NewRate = clsInputValidate::ReadNumber<float>();
		return NewRate;
	}


public:


	static void ShowUpdateCurrencyScreen()
	{

		clsScreen::_DrawScreenHeader("\t\tUpdate Currency Screen");

		string CurrencyCode = _ReadCurrencyCode();
		if (CurrencyCode == "exit")
			return;
		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\n" << setw(ScreenWidth) << "" << left << Red << "Currency Not Found try again. " << White;
			CurrencyCode = _ReadCurrencyCode();
			if (CurrencyCode == "exit")
				return;
		}
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		cout << setw(ScreenWidth) << "" << left << "Are you sure you want to update this currency rate? ";
		if (clsInputValidate::IsAnswerIsYes())
		{

			cout << "\n" << setw(ScreenWidth) << "" << left << Blue << "Update Currency rate" << White;
			cout << "\n" << setw(ScreenWidth) << "" << left << Green << "__________________________________________\n" << White;

			Currency.UpdateRate(_ReadRate());
			cout << "\n" << setw(ScreenWidth) << "" << left << Green << "Currency Rate Updates Successfully\n" << White;
			_PrintCurrency(Currency);

		}



	}




};

