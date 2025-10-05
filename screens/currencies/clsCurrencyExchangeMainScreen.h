

#pragma once
#include<iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h";
#include "clsMainScreen.h";
#include "clsCurrencyExchangeListScreen.h";
#include "clsFindCurrencyScreen.h";
#include "clsUpdateCurrencyScreen.h";
#include "clsCurrencyCalculaterScreen.h";

using namespace std;


class clsCurrencyExchangeScreen :protected clsScreen
{

private:

	enum enCurrenciesMainMenueOptions {eListCurrencies=1,eFindCurrency=2,eUpdateRate=3,eCurrencyCalculator=4,eMainMenue=5};


    static short _ReadCurrencyExchangeMenuOption()
    {
        cout << setw(ScreenWidth) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadNumberBetween<short>(1, 5, "Enter Number between 1 to 5? ");
        return  Choice;
    }

    static void _GoBackToCurrenciesMenu()
    {
        cout << "\n\nPress any key to go back to Exchange Menu...\n";
        system("pause >0");
        ShowCurrenciesMenue();

    }

    static void _ShowCurrenciesListScreen()
    {
        clsCurrencyExchangeListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateCurrencyRateScreen()
    {
        clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        clsCurrencyCalculaterScreen::ShowCurrencyCalculatorScreen();

    }

    static void _PerformCurrenciesMainMenuOptions(enCurrenciesMainMenueOptions ExchangeMenuOptions)
    {
        switch (ExchangeMenuOptions)
        {
        case clsCurrencyExchangeScreen::eListCurrencies:
            system("cls");
            _ShowCurrenciesListScreen();
            _GoBackToCurrenciesMenu();
            break;
        case clsCurrencyExchangeScreen::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrenciesMenu();
            break;
        case clsCurrencyExchangeScreen::eUpdateRate:
            system("cls");
            _ShowUpdateCurrencyRateScreen();
            _GoBackToCurrenciesMenu();
            break;
        case clsCurrencyExchangeScreen::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrenciesMenu();
            break;
        case clsCurrencyExchangeScreen::eMainMenue:
            break;

        default:

            break;
        }
        


    }





public:



    static void ShowCurrenciesMenue()
    {

        system("cls");
        clsScreen::_DrawScreenHeader("\t     Currency Exchange Screen");

        cout << setw(ScreenWidth) << left << "" << Green << "===========================================\n";
        cout << setw(ScreenWidth) << left << "" << Red << "\t     Currency Exchange Menu\n";
        cout << setw(ScreenWidth) << left << "" << Green << "===========================================\n" << White;
        cout << setw(ScreenWidth) << left << "" << " [1] List Currencies.\n";
        cout << setw(ScreenWidth) << left << "" << " [2] Find Currency.\n";
        cout << setw(ScreenWidth) << left << "" << " [3] Update Rate.\n";
        cout << setw(ScreenWidth) << left << "" << " [4] Currency Calculator.\n";
        cout << setw(ScreenWidth) << left << "" << " [5] Main Menu.\n";
        cout << setw(ScreenWidth) << left << "" << Green << "===========================================\n" << White;

        _PerformCurrenciesMainMenuOptions((enCurrenciesMainMenueOptions)_ReadCurrencyExchangeMenuOption());
    }




};

