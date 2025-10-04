#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h";
#include "clsString.h";
#include "clsInputValidate.h";
#include "Global.h";
#include "clsCurrency.h";

using namespace std;

int _EncryptedKey = 2;

class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enum enStructmode { eEmptyMode = 0, eUpdateMode = 1 };

    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    double  _AccountBalance;
    bool   _MarkedForDelete = false;

    struct stAddress
    {
        string Country="";
        string City="";
        string Village="";
        string StreetAddress="";

    };
    struct stBanks
    {
        stAddress BankAddress;
        string BankName="";
        string IBAN="";
        string SwiftCode="";
        double AccountBalance =0;
        string CurrencyCode="";
        double InterTransBankFees=0;
        double InterTransTaxes=0;

    };

    //declaration structs

    struct stInterTransferClientInfo;
    struct stTransferLogRecord;
    struct stInterTransLog;

    //==================================================================================

    static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#")
    {
        vector<string> vClientData= clsString::Split(Line, Separator);
        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], clsUtil::DecryptText(vClientData[5], _EncryptedKey), stod(vClientData[6]));

    }

    static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Separator;
        stClientRecord += Client.LastName + Separator;
        stClientRecord += Client.Email + Separator;
        stClientRecord += Client.Phone + Separator;
        stClientRecord += Client.AccountNumber() + Separator;
        stClientRecord += clsUtil::EncryptText(Client.PinCode, _EncryptedKey) + Separator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static stInterTransferClientInfo _GetEmptyInterRecord()
    {
        stInterTransferClientInfo EmptyInterRecord;

        EmptyInterRecord.FirstName = "";
        EmptyInterRecord.LastName = "";
        EmptyInterRecord.ClientAddress.Country = "";
        EmptyInterRecord.ClientAddress.City = "";
        EmptyInterRecord.ClientAddress.Village = "";
        EmptyInterRecord.ClientAddress.StreetAddress = "";
        EmptyInterRecord.BankClientInfo.BankName = "";
        EmptyInterRecord.BankClientInfo.IBAN = "";
        EmptyInterRecord.BankClientInfo.SwiftCode = "";
        EmptyInterRecord.BankClientInfo.CurrencyCode = "";
        EmptyInterRecord.BankClientInfo.AccountBalance = 0.0000000000000000;
        EmptyInterRecord.BankClientInfo.InterTransBankFees = 0.0000000000000000;
        EmptyInterRecord.BankClientInfo.BankAddress.Country = "";
        EmptyInterRecord.BankClientInfo.BankAddress.City = "";
        EmptyInterRecord.BankClientInfo.BankAddress.Village = "";
        EmptyInterRecord.BankClientInfo.BankAddress.StreetAddress = "";
        EmptyInterRecord.BankClientInfo.InterTransTaxes= 0.00000000;
        EmptyInterRecord.InterStructMode = enStructmode::eEmptyMode;
        return  EmptyInterRecord;
    }

    string _PrepareTransferLogRecord(double Amount, clsBankClient DestinationClient,string UserName, string Separator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Separator;
        TransferLogRecord += AccountNumber() + Separator;
        TransferLogRecord += DestinationClient.AccountNumber() + Separator;
        TransferLogRecord += to_string(Amount) + Separator;
        TransferLogRecord += to_string(AccountBalance) + Separator;
        TransferLogRecord += to_string(DestinationClient.AccountBalance) + Separator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }

    static string  _PrepareInterTransLogRecord(stInterTransferClientInfo SenderStruct, stInterTransferClientInfo RecipientStruct,double SendingAmount,string User ,string Separator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Separator;
        TransferLogRecord += SenderStruct.BankClientInfo.IBAN + Separator;
        TransferLogRecord += SenderStruct.BankClientInfo.SwiftCode + Separator;
        TransferLogRecord += RecipientStruct.BankClientInfo.IBAN + Separator;
        TransferLogRecord += RecipientStruct.BankClientInfo.SwiftCode + Separator;
        TransferLogRecord += to_string(SendingAmount) + Separator;
        TransferLogRecord += SenderStruct.BankClientInfo.CurrencyCode + Separator;
        TransferLogRecord += to_string(SenderStruct.BankClientInfo.AccountBalance) + Separator;
        TransferLogRecord += User;
        return TransferLogRecord;

    }

    static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Separator = "#//#")
    {
        stTransferLogRecord TransferLogRecord;

        vector <string> LoginRegisterDataLine = clsString::Split(Line, Separator);
        TransferLogRecord.SystemDateTime = LoginRegisterDataLine[0];
        TransferLogRecord.SourceAccountNumber = LoginRegisterDataLine[1];
        TransferLogRecord.DestinationAccountNumber = LoginRegisterDataLine[2];
        TransferLogRecord.TransferAmount = LoginRegisterDataLine[3];
        TransferLogRecord.SourceAccountBalance = LoginRegisterDataLine[4];
        TransferLogRecord.DestinationAccountBalance = LoginRegisterDataLine[5];
        TransferLogRecord.ResponsibleActionUserName = LoginRegisterDataLine[6];

        return TransferLogRecord;
    }

    static stInterTransferClientInfo _InterTransConvertClientLineToRecord(string Line, string Separator = "#//#")
    {
        vector<string>vInterClient = clsString::Split(Line, Separator);
        stInterTransferClientInfo ClientRecord;
        ClientRecord.BankClientInfo.IBAN = vInterClient[0];
        ClientRecord.BankClientInfo.SwiftCode = vInterClient[1];
        ClientRecord.FirstName = vInterClient[2];
        ClientRecord.LastName = vInterClient[3];
        ClientRecord.BankClientInfo.AccountBalance = stod(vInterClient[4]);
        ClientRecord.BankClientInfo.CurrencyCode = vInterClient[5];
        ClientRecord.ClientAddress.Country = vInterClient[6];
        ClientRecord.ClientAddress.City = vInterClient[7];
        ClientRecord.ClientAddress.Village = vInterClient[8];//cast string to double
        ClientRecord.ClientAddress.StreetAddress = vInterClient[9];
        ClientRecord.BankClientInfo.BankName = vInterClient[10];
        ClientRecord.BankClientInfo.BankAddress.Country = vInterClient[11];
        ClientRecord.BankClientInfo.BankAddress.City = vInterClient[12];
        ClientRecord.BankClientInfo.BankAddress.Village = vInterClient[13];
        ClientRecord.BankClientInfo.BankAddress.StreetAddress = vInterClient[14];
        ClientRecord.BankClientInfo.InterTransBankFees = stod(vInterClient[15]);
        ClientRecord.InterStructMode = enStructmode::eUpdateMode;

        return ClientRecord;
    }

    static string _InterTransConvertClientRecordToLine(stInterTransferClientInfo InterClient, string Seperator = "#//#")
    {
        string stClientRecord = "";
        stClientRecord += InterClient.BankClientInfo.IBAN + Seperator;
        stClientRecord += InterClient.BankClientInfo.SwiftCode + Seperator;
        stClientRecord += InterClient.FirstName + Seperator;
        stClientRecord += InterClient.LastName + Seperator;
        stClientRecord += to_string(InterClient.BankClientInfo.AccountBalance) + Seperator;
        stClientRecord += InterClient.BankClientInfo.CurrencyCode+ Seperator;
        stClientRecord += InterClient.ClientAddress.Country + Seperator;
        stClientRecord += InterClient.ClientAddress.City + Seperator;
        stClientRecord += InterClient.ClientAddress.Village + Seperator;
        stClientRecord += InterClient.ClientAddress.StreetAddress + Seperator;
        stClientRecord += InterClient.BankClientInfo.BankName + Seperator;
        stClientRecord += InterClient.BankClientInfo.BankAddress.Country + Seperator;
        stClientRecord += InterClient.BankClientInfo.BankAddress.City + Seperator;
        stClientRecord += InterClient.BankClientInfo.BankAddress.Village + Seperator;
        stClientRecord += InterClient.BankClientInfo.BankAddress.StreetAddress + Seperator;
        stClientRecord += to_string(InterClient.BankClientInfo.InterTransBankFees);


        return stClientRecord;
    }

    static stInterTransLog _ConvertInterTransLogLineToRecord(string Line, string Separator = "#//#")
    {

        vector<string> vInterTransLogRecord = clsString::Split(Line, Separator);
        stInterTransLog InterLogRecord;
        InterLogRecord.InterTransferDateTime = vInterTransLogRecord[0];
        InterLogRecord.SenderIBAN = vInterTransLogRecord[1];
        InterLogRecord.SenderSwiftCode = vInterTransLogRecord[2];
        InterLogRecord.RecipientIBAN = vInterTransLogRecord[3];
        InterLogRecord.RecipientSwiftCode = vInterTransLogRecord[4];
        InterLogRecord.SendingAmount = stod(vInterTransLogRecord[5]);
        InterLogRecord.CurrencyCode = vInterTransLogRecord[6];
        InterLogRecord.SenderAccountBalance = stod(vInterTransLogRecord[7]);
        InterLogRecord.ResponsibleActionUser = vInterTransLogRecord[8];

        return InterLogRecord;


    }


    //==================================================================================

    static vector <stInterTransferClientInfo> _InterTransLoadClientsDataFromFile(string FileName)
    {
        vector <stInterTransferClientInfo> vClients;
        fstream MyFile;
        MyFile.open(FileName, ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line = "";
            stInterTransferClientInfo Client;
            while (getline(MyFile, Line))
            {
                Client = _InterTransConvertClientLineToRecord(Line);
                vClients.push_back(Client);
            }
            MyFile.close();
        }

        return vClients;
    }

    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLineToClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }

    static vector<stTransferLogRecord> _LoadTransfersLogListFromFile()
    {
        vector <stTransferLogRecord> vTransferLogRecord;
        fstream MyFile;
        MyFile.open("TransfersLog.txt", ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line;
            stTransferLogRecord TransferRecord;
            while (getline(MyFile, Line))
            {
                TransferRecord = _ConvertTransferLogLineToRecord(Line);
                vTransferLogRecord.push_back(TransferRecord);
            }
            MyFile.close();
        }
        return vTransferLogRecord;

    
    }

    static vector<stInterTransLog> _LoadInterTransLogList()
    {

        vector <stInterTransLog> vTransferLogRecord;
        fstream MyFile;
        MyFile.open(InterTransLogFileName, ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line;
            stInterTransLog TransferRecord;
            while (getline(MyFile, Line))
            {
                TransferRecord = _ConvertInterTransLogLineToRecord(Line);
                vTransferLogRecord.push_back(TransferRecord);
            }
            MyFile.close();
        }
        return vTransferLogRecord;
    }

    static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite
        if (MyFile.is_open())
        {
            for (clsBankClient& C : vClients)
            {
                if (C._MarkedForDelete == false)
                {
                    MyFile << _ConvertClientObjectToLine(C) << endl;
                }
            }
            MyFile.close();
        }

    }

    static void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    static void _InterTransSaveDataToFile(string FileName, vector<stInterTransferClientInfo> vClients)
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out);//overwrite 
        string DataLine;
        if (MyFile.is_open())
        {
            for (stInterTransferClientInfo& C : vClients)
            {

                //we only write records that are not marked for delete.      
                DataLine = _InterTransConvertClientRecordToLine(C);
                MyFile << DataLine << endl;

            }
            MyFile.close();
        }
    }

    static void _InterTransUpdateDataInFile(stInterTransferClientInfo ClientToUpdate, string ClientToUpdateFileName)
    {
        vector<stInterTransferClientInfo>vInterClients = _InterTransLoadClientsDataFromFile(ClientToUpdateFileName);
        for (stInterTransferClientInfo& Client : vInterClients)
        {
            if ((Client.BankClientInfo.IBAN == ClientToUpdate.BankClientInfo.IBAN) && (Client.BankClientInfo.SwiftCode == ClientToUpdate.BankClientInfo.SwiftCode))
            {
                Client = ClientToUpdate;
                _InterTransSaveDataToFile(ClientToUpdateFileName, vInterClients);
                break;
            }
        }
    }
    //==================================================================================

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }

        }

        _SaveClientsDataToFile(_vClients);

    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    //==================================================================================
    void _RegisterTransferLog(double Amount, clsBankClient DestinationClient, string UserName)
    {

        string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);
        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    void _RegisterInterTransLog(stInterTransferClientInfo Sender, stInterTransferClientInfo Recipient,double SendingAmount,string User,string Separator="#//#")
    {

        string stDataLine = _PrepareInterTransLogRecord(Sender, Recipient, SendingAmount,User,Separator);
        clsUtil::AddDataLineToFile(stDataLine,InterTransLogFileName);

    }

public:
    
    struct stTransferLogRecord
    {
        string SystemDateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        string TransferAmount;
        string SourceAccountBalance;
        string DestinationAccountBalance;
        string ResponsibleActionUserName;

    };

    struct stInterTransferClientInfo
    {

        stBanks BankClientInfo;
        stAddress ClientAddress;
        string FirstName="";
        string LastName="";
        enStructmode InterStructMode;
    };

    struct stInterTransLog
    {
        string InterTransferDateTime;
        string SenderIBAN;
        string SenderSwiftCode;
        string RecipientIBAN;
        string RecipientSwiftCode;
        double SendingAmount;
        string CurrencyCode;
        double SenderAccountBalance;
        string ResponsibleActionUser;

    };


    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, double AccountBalance)
        :clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    //============================= Property ======================================
    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }
    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(double AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    double GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

    bool MarkedForDelete()
    {
        return _MarkedForDelete;
    }


    //==================================================================================

    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read mode;
        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    static bool IsClientExist(string AccountNumber)
    {
        //easy methode
        //return !(Find(AccountNumber).IsEmpty());
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        return !(Client.IsEmpty());
    }

    //==================================================================================
    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

    enSaveResults Save()
    {
        switch (_Mode)
        {

            case enMode::EmptyMode:
                return enSaveResults::svFaildEmptyObject;

            case enMode::UpdateMode:
                _Update();
                return enSaveResults::svSucceeded;
      
            case enMode::AddNewMode:
        
                if (clsBankClient::IsClientExist(_AccountNumber))
                {
                    return enSaveResults::svFaildAccountNumberExists;
                }
                else
                {
                    _AddNew();
                    _Mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }
        

        }


    }

    bool Delete()
    {
        vector <clsBankClient> _vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                _SaveClientsDataToFile(_vClients);
                *this = _GetEmptyClientObject();
                return true;
            }
        }
        return false;
    }

    //==================================================================================

    void Deposit(double Amount)
    {
        if (Amount < 0)
        {
            Amount *= -1;
        }
        AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount)
    {
        if (Amount < 0)
        {
            Amount*= -1;
        }
        if (AccountBalance < Amount)
        {
            return false;
        }
        else
        {
            AccountBalance -= Amount;
            Save();
            return true;
        }

    }

    bool Transfer(double Amount, clsBankClient& DestinationClient,string UserName)
    {
        if (Amount < 0)
            Amount *= -1;
        if (Amount > AccountBalance)
        {
            return false;
        }
        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount,DestinationClient, UserName);
        return true;
    }

    //==================================================================================

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    static clsBankClient GetUpdateNewClientObject()
    {
        return clsBankClient(enMode::UpdateMode, "", "", "", "", "", "", 0);
    }

    static double GetTotalBalances()
    {

        vector<clsBankClient>vClients = GetClientsList();

        double TotalBalances=0;
        for (clsBankClient& Client : vClients)
        {
            TotalBalances += Client.AccountBalance;
        }
        return TotalBalances;
    }

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static vector<stTransferLogRecord>GetTransfersLogList()
    {

        return  _LoadTransfersLogListFromFile();

    }

    //==================================================================================

    bool InterTransfer(stInterTransferClientInfo& sender,stInterTransferClientInfo &Recipient, double Amount)
    {
        clsCurrency Currency1=clsCurrency::FindByCountry(sender.ClientAddress.Country);
        clsCurrency Currency2= clsCurrency::FindByCountry(Recipient.ClientAddress.Country);

        double TaxAmount = (Amount * Currency1.GetInterTransTaxesPercentage()) / 100;
        double BankFeesAmount = (Amount * sender.BankClientInfo.InterTransBankFees) / 100;
        double TotalWithdrawAmountOriginalCurrency = Amount + TaxAmount + BankFeesAmount;
        //convert to used first 
        sender.BankClientInfo.InterTransTaxes = TaxAmount;

        if (sender.BankClientInfo.AccountBalance > TotalWithdrawAmountOriginalCurrency)
        {
            sender.BankClientInfo.AccountBalance -= TotalWithdrawAmountOriginalCurrency; 

            double AmountToDeposit = Currency1.ConvertToOtherCurrency(Amount, Currency2);
            Recipient.BankClientInfo.AccountBalance += AmountToDeposit;


            _InterTransUpdateDataInFile(sender,SenderFileName);
            _InterTransUpdateDataInFile(Recipient,RecipientFileName);
            _RegisterInterTransLog(sender, Recipient, Amount,CurrentUser.UserName);
            return true;
        }
        else 
        {
            return false;
        }
    }

    static stInterTransferClientInfo FindByIBANAndSwift(string IBAN, string Swift, string FileName)
    {
        fstream MyFile;
        MyFile.open(FileName, ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                stInterTransferClientInfo Client = _InterTransConvertClientLineToRecord(Line);
                if (Client.BankClientInfo.IBAN == IBAN && Client.BankClientInfo.SwiftCode == Swift)
                {
                    return Client;
                    MyFile.close();
                }
            }

            MyFile.close();
        }
        return _GetEmptyInterRecord();
    }

    static stInterTransferClientInfo FindByIBAN(string IBAN, string FileName)
    {
        fstream MyFile;
        MyFile.open(FileName, ios::in);//read mode;
        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
                stInterTransferClientInfo Client = _InterTransConvertClientLineToRecord(Line);
                if (Client.BankClientInfo.IBAN == IBAN)
                {
                    return Client;
                    MyFile.close();
                }
            }
            MyFile.close();
        }
        return _GetEmptyInterRecord();
    }

    static vector<stInterTransferClientInfo> GetInterTransClientsList(string FileName)
    {

        return _InterTransLoadClientsDataFromFile(FileName);
    }

    static bool IsInterClientExistByIBANAndSwift(string IBAN,string SwiftCode, string FileName)
    {
        stInterTransferClientInfo FindByIBANAndSwift = clsBankClient::FindByIBANAndSwift(IBAN, SwiftCode, FileName);
        return ! (IsInterClientStructEmpty(FindByIBANAndSwift));
    }

    static bool IsInterClientExist(string IBAN,string FileName)
    {
        stInterTransferClientInfo InterClient = clsBankClient::FindByIBAN(IBAN, FileName);

        if (IsInterClientStructEmpty(InterClient))
        {
            return false;
        }
        else
        {
            return true;

        }
    }

    static bool IsInterClientStructEmpty(stInterTransferClientInfo InterClient)
    {

        return (InterClient.InterStructMode == enStructmode::eEmptyMode);
    }

    static vector<stInterTransLog>GetInterTransLogList()
    {
        return _LoadInterTransLogList();
    }



};