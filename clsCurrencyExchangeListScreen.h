#pragma once
#include<iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h";
#include "clsCurrency.h";


using namespace std;


class clsCurrencyExchangeListScreen :protected clsScreen
{

private:

	static void DrawCurrencyExchangeTableHeader()
	{
		cout << "\n" << setw(20) << "" << left <<Green<< "_____________________________________________________________________________________________________\n";
		cout <<"\n" << setw(21) << "" << left <<Green << "| "
			<< Blue<<setw(30) << "Country" << left << Green << "| "
			<< Blue<<setw(15) << "Currency Code" << left << Green << "| "
			<< Blue<<setw(30) << "Currency Name" << left << Green << "| "
			<< Blue<<setw(15) << "Rates/(1$)" << left;
		cout << "\n" << setw(20) << "" << left<<Green << "_____________________________________________________________________________________________________\n\n"<<White;

	}

	static void PrintCurrencyExchangeTableRecord(clsCurrency Currency)
	{

		cout << setw(21) << "" << left << Green << "| "
			<< White << setw(30) << Currency.Country() << left << Green << "| "
			<< White << setw(15) << Currency.CurrencyCode() << left << Green << "| "
			<< White << setw(30) << Currency.CurrencyName() << left << Green << "| "
			<< White << setw(15) << Currency.Rate() << left<<Green<<"| ";
	}

	
public:

	static void ShowCurrenciesListScreen()
	{

		vector<clsCurrency>vCurrencys =clsCurrency::GetCurrenciesList() ;
		string Title = "\t\tCurrency Exchange List";
		string Subtitle = "\t\t (" + to_string(vCurrencys.size()) + ") Currencies";

		clsScreen::_DrawScreenHeader(Title, Subtitle);


		DrawCurrencyExchangeTableHeader();

		for (clsCurrency& Currency : vCurrencys)
		{

			PrintCurrencyExchangeTableRecord(Currency);
			cout << endl;


		}
		cout << setw(20) << "" << left << Green << "_____________________________________________________________________________________________________\n" << White;


	}



};

