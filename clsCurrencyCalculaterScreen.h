#pragma once

#include<iostream>
#include <vector>
#include <fstream>
#include "clsScreen.h";
#include "clsCurrency.h";
#include "clsInputValidate.h";

using namespace std;

class clsCurrencyCalculaterScreen : protected clsScreen
{

private:

    static float _ReadAmount()
    {
        cout << "\n" << setw(ScreenWidth) << "" << left << "Enter Amount to Exchange: ";
        float Amount = 0;
        Amount = clsInputValidate::ReadNumber<float>();
        return Amount;
    }

    static clsCurrency _GetCurrency(string Message)
    {
        string CurrencyCode;
        cout << "\n" << setw(ScreenWidth) << "" << left << Message <<" ";
        CurrencyCode = clsInputValidate::ReadString();
        if (CurrencyCode == "exit")
            return clsCurrency::FindByCode("");
        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\n" << setw(ScreenWidth) << "" << left <<Yellow<< "Currency is not found, choose another one: "<<White;
            CurrencyCode = clsInputValidate::ReadString();
            if (CurrencyCode == "exit")
                return clsCurrency::FindByCode("");
        }
        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return Currency;

    }

    static  void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
    {

        cout << "\n" << setw(ScreenWidth) << "" << left  << Title << "\n";
        cout << "\n" << setw(ScreenWidth) << "" << left <<Green<< "_____________________________\n"<<White;
        cout << "\n"<<setw(ScreenWidth)   << "" << left << "Country       : " << Currency.Country();
        cout << "\n" << setw(ScreenWidth) << "" << left << "Code          : " << Currency.CurrencyCode();
        cout << "\n" << setw(ScreenWidth) << "" << left << "Name          : " << Currency.CurrencyName();
        cout << "\n" << setw(ScreenWidth) << "" << left << "Rate(1$) =    : " << Currency.Rate();
        cout << "\n" << setw(ScreenWidth) << "" << left <<Green<< "_____________________________\n\n"<<White;

    }

    static void _PrintCalculationsResults(float Amount, clsCurrency Currency1, clsCurrency Currency2)
    {

        _PrintCurrencyCard(Currency1, "Convert From:");

        float AmountInUSD = Currency1.ConvertToUSD(Amount);
        
        cout << "\n" << setw(ScreenWidth) << "" << left << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInUSD << " USD\n";

        if (Currency2.CurrencyCode() == "USD")
        {
            return;
        }

        cout << "\n" << setw(ScreenWidth) << "" << left << "Converting from USD to:\n";

        _PrintCurrencyCard(Currency2, "Currency Card To:");

        float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount,Currency2);

        cout << "\n" << setw(ScreenWidth) << "" << left  << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInCurrency2 << " " << Currency2.CurrencyCode();

    }


public:

    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'y';

        while (Continue == 'y' || Continue == 'Y')
        {
            system("cls");
            _DrawScreenHeader("\t    Update Currency Screen");
            cout << "\n" << setw(ScreenWidth) << "" << left <<Blue<< "To exit enter -> exit: \n\n"<<White;
            clsCurrency CurrencyFrom = _GetCurrency("Please Enter Currency1 Code: ");
            if (CurrencyFrom.IsEmpty())
            {
                return;
            }
            clsCurrency CurrencyTo = _GetCurrency("Please Enter Currency2 Code : ");
            if (CurrencyTo.IsEmpty())
            {
                return;
            }
            float Amount = _ReadAmount();
            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

            cout << "\n\n" << setw(ScreenWidth) << "" << left << "Do you want to perform another calculation? y/n ? ";
            Continue=clsInputValidate::ReadCharacter();

        }


    }






};

