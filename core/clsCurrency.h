#pragma once

#include<iostream>
#include<string>
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;

class clsCurrency
{

private:


	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;
    float _InterTransTaxesPercentage;
    //========================================================

    static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#")
    {
        vector<string> vCurrencyData;
        vCurrencyData = clsString::Split(Line, Separator);

        return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],stod(vCurrencyData[3]),stod(vCurrencyData[4]));

    }

    static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Separator = "#//#")
    {

        string stCurrencyRecord = "";
        stCurrencyRecord += Currency.Country() + Separator;
        stCurrencyRecord += Currency.CurrencyCode() + Separator;
        stCurrencyRecord += Currency.CurrencyName() + Separator;
        stCurrencyRecord += to_string(Currency.Rate()) + Separator;
        stCurrencyRecord += to_string(Currency._InterTransTaxesPercentage);

        return stCurrencyRecord;

    }

    static  vector <clsCurrency> _LoadCurrencysDataFromFile()
    {

        vector <clsCurrency> vCurrencys;

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {

                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

                vCurrencys.push_back(Currency);
            }

            MyFile.close();

        }

        return vCurrencys;

    }


    void _Update()
    {
        vector <clsCurrency> _vCurrencys;
        _vCurrencys = _LoadCurrencysDataFromFile();

        for (clsCurrency& C : _vCurrencys)
        {
            if (C.CurrencyCode() == CurrencyCode())
            {
                C = *this;
                break;
            }

        }

        _SaveCurrencyDataToFile(_vCurrencys);

    }

    static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencys)
    {

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out);//overwrite
        string DataLine;
        if (MyFile.is_open())
        {

            for (clsCurrency& C : vCurrencys)
            {
                DataLine = _ConvertCurrencyObjectToLine(C);
                MyFile << DataLine << endl;
            }

            MyFile.close();

        }

    }


    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0,0);
    }



public:

	clsCurrency(enMode Mode,string Country,string CurrencyCode ,string CurrencyName,float Rate,float InterTransTaxesPercentage)
	{

		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
        _InterTransTaxesPercentage = InterTransTaxesPercentage;

	}
    


    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string Country()
    {
        return _Country;
    }

    string CurrencyCode()
    {
        return _CurrencyCode;
    }

    string CurrencyName()
    {
        return _CurrencyName;
    }

    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }

    float Rate()
    {
        return _Rate;
    }

    void UpdateInterTransTaxesPercentage(float NewInterTransTaxesPercentage)
    {
        _InterTransTaxesPercentage = NewInterTransTaxesPercentage;
        _Update();
    }

    float GetInterTransTaxesPercentage()
    {
        return _InterTransTaxesPercentage;
    }

    static   clsCurrency FindByCode(string CurrencyCode)
    {

        CurrencyCode = clsString::UpperAllString(CurrencyCode);
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
                if (Currency.CurrencyCode() == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }
            }

            MyFile.close();

        }

        return _GetEmptyCurrencyObject();

    }

    static   clsCurrency FindByCountry(string Country)
    {
        Country = clsString::UpperAllString(Country);

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
                if (clsString::UpperAllString(Currency.Country()) == Country)
                {
                    MyFile.close();
                    return Currency;
                }

            }

            MyFile.close();

        }

        return _GetEmptyCurrencyObject();

    }

    static bool IsCurrencyExist(string CurrencyCode)
    {
        clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
        return (!C1.IsEmpty());

    }

    static bool IsCurrencyExistByCountry(string Country )
    {
        clsCurrency C1 = clsCurrency::FindByCountry(Country);
        return (!C1.IsEmpty());

    }

    static vector <clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrencysDataFromFile();
    }

    static vector<string>GetAllCountriesNames()
    {

        vector<clsCurrency>vCurrencyRatesList = GetCurrenciesList();
        vector<string>vRates;
        for (clsCurrency& Currency : vCurrencyRatesList)
        {
            vRates.push_back(Currency.Country());
        }
        return vRates;
    }

    static vector <float> GetAllUSDRates()
    {

        vector<clsCurrency>vCurrencyRatesList = GetCurrenciesList();
        vector<float>vRates;
        for (clsCurrency& Currency : vCurrencyRatesList)
        {
            vRates.push_back(Currency.Rate());
        }
        return vRates;

    }

    static vector<string>GetAllCurrencyCodes()
    {

        vector<clsCurrency>vCurrencyRatesList = GetCurrenciesList();
        vector<string>vRates;
        for (clsCurrency& Currency : vCurrencyRatesList)
        {
            vRates.push_back(Currency.Country());
        }
        return vRates;
    }

    static vector<string>GetAllCurrencyNames()
    {

        vector<clsCurrency>vCurrencyRatesList = GetCurrenciesList();
        vector<string>vRates;
        for (clsCurrency& Currency : vCurrencyRatesList)
        {
            vRates.push_back(Currency.CurrencyName());
        }
        return vRates;
    }


    float ConvertToUSD(float Amount)
    {
        return (float)(Amount / Rate());
    }

    float ConvertToOtherCurrency(float Amount,clsCurrency CurrencyTo)
    {

        float AmountInUSD = ConvertToUSD(Amount);
    
        
        if (CurrencyTo.CurrencyCode() == "USD")
        {
            return AmountInUSD;

        }
        return (float)AmountInUSD * CurrencyTo.Rate();

    }

    float FromUsdToOtherCurrency(float Amount,clsCurrency CurrencyTo)
    {
        return Amount * CurrencyTo.Rate();
    }













};

