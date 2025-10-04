#pragma once
#include <iostream>
#include "clsPerson.h";
#include <vector>
#include "clsString.h";
#include <fstream>
#include <string>
#include "Global.h";
using namespace std;
int _EncryptionKey = 2;


class clsUser : public clsPerson
{

private:

	enum enMode {EmptyMode=1,UpdateMode=2,AddNewMode=3};

	enMode _Mode;
	string _UserName;
	string _Password;
	short _Permissions=0;
    short _Actions=0;
    bool _MarkedForDelete = false;
    string _LoginDateAndTime;
    string _LogOutDateAndTime;
    //==================================================================================

    static clsUser _ConvertLineToUserObject(string Line, string Separator = "#//#")
    {
        vector<string>vUsers = clsString::Split(Line, Separator);
        return clsUser(enMode::UpdateMode, vUsers[0], vUsers[1], vUsers[2], vUsers[3], vUsers[4], clsUtil::DecryptText(vUsers[5],_EncryptionKey), stoi(vUsers[6]));
    }

    static string _ConvertUserObjectToLine(clsUser User, string Separator = "#//#")
    {
        
        string UserRecord = "";
        UserRecord += User.FirstName + Separator;
        UserRecord += User.LastName + Separator;
        UserRecord += User.Email + Separator;
        UserRecord += User.Phone + Separator;
        UserRecord += User.UserName + Separator;
        UserRecord += clsUtil::EncryptText(User.Password,_EncryptionKey) + Separator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;

    }

    static clsUser _ConvertLineToRegisterUserObject(string Line, string Separator = "#//#")
    {

        vector<string>vUsers = clsString::Split(Line, Separator);
        clsUser User = clsUser::GetAddNewUserObject("");
        User.LoginDateAndTime = vUsers[0];
        User.UserName = vUsers[1];
        User.Password = vUsers[2];
        User.Permissions = stoi(clsUtil::DecryptText((vUsers[3]),_EncryptionKey));
        User.LogOutDateAndTime = vUsers[4];
        return User;

    }

    struct stLoginRegisterRecord;

    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Separator = "#//#")
    {
        stLoginRegisterRecord LoginRegisterRecord;

        vector <string> LoginRegisterDataLine = clsString::Split(Line, Separator);
        LoginRegisterRecord.LoginDateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = clsUtil::DecryptText (LoginRegisterDataLine[2], _EncryptionKey);
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);
        LoginRegisterRecord.LogoutDateTime = LoginRegisterDataLine[4];
        return LoginRegisterRecord;
    }

    static string _ConvertLoginRegisterStructToLine(stLoginRegisterRecord LoginRegisterRecord, string Separator = "#//#")
    {
        string LoginRegisterLine = "";
        LoginRegisterLine += LoginRegisterRecord.LoginDateTime + Separator;
        LoginRegisterLine += LoginRegisterRecord.UserName + Separator;
        LoginRegisterLine += clsUtil::EncryptText(LoginRegisterRecord.Password, _EncryptionKey)+ Separator;
        LoginRegisterLine += to_string(LoginRegisterRecord.Permissions) + Separator;
        LoginRegisterLine += LoginRegisterRecord.LogoutDateTime;
        return LoginRegisterLine;
    }


    //==================================================================================

    static  vector <clsUser> _LoadUsersDataFromFile()
    {
        vector <clsUser> vUsers;
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line);
                vUsers.push_back(User);
            }
            MyFile.close();
        }
        return vUsers;

    }

    static vector<stLoginRegisterRecord>_LoadLoginRegisterList()
    {
        vector <stLoginRegisterRecord> vLoginRegisterRecord;

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            stLoginRegisterRecord LoginRegisterRecord;
            while (getline(MyFile, Line))
            {
                LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
                vLoginRegisterRecord.push_back(LoginRegisterRecord);
            }
            MyFile.close();
        }

        return vLoginRegisterRecord;
    }

    //==================================================================================

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite
        string DataLine;
        if (MyFile.is_open())
        {
            for (clsUser &U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConvertUserObjectToLine(U);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }

    static void _SaveUpdatedLoginRegisterDataInFile(vector<stLoginRegisterRecord>vRecords)
    {
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out);//overwrite
        if (MyFile.is_open())
        {
            string DataLine;
            for (stLoginRegisterRecord& Record : vRecords)
            {
                DataLine = _ConvertLoginRegisterStructToLine(Record);
                MyFile << DataLine << endl;
            }
            MyFile.close();
        }

    }
    //==================================================================================

    static void _AddDataLineToFile(string  stDataLine,string FileName="Users.txt")
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;
            MyFile.close();
        }

    }

    //==================================================================================

    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertUserObjectToLine(*this));
    }

    //==================================================================================

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    string _UserActionsDataLine(string Delimiter = "#//#")
    {
        return (LoginDateAndTime + Delimiter +_UserName+Delimiter+_Password+Delimiter+ to_string(_Permissions)+Delimiter+to_string(_Actions) + Delimiter + clsDate::GetSystemDateTimeString());
    }

    string _PrepareLogInRecord(string Separator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord +=clsDate::GetSystemDateTimeString()+ Separator;
        LoginRecord += UserName + Separator;
        LoginRecord +=clsUtil::EncryptText( Password,_EncryptionKey) + Separator;
        LoginRecord += to_string(Permissions)+ Separator;
        LoginRecord += "!Not Logout yet";
        return LoginRecord;
    }


public:


    enum enPermissions 
    {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64,pLoginRegisterScreen=128,pUsersActions=256
    };

    struct stLoginRegisterRecord
    {
        string LoginDateTime;
        string UserName;
        string Password;
        int Permissions=0;
        string LogoutDateTime;

    };

    //============================== properties set and get =========================================

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }
    string GetUserName()
    {
        return _UserName;
    }
    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _Password = Password;
    }
    const string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermission(short Permission)
    {
        _Permissions = Permission;
    }
    const short GetPermission()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermission, put = SetPermission)) short Permissions;

    void SetActions(short Actions)
    {
        _Actions = Actions;
    }
    const short GetActions()
    {
        return _Actions;
    }
    __declspec(property(get = GetActions, put = SetActions)) short Actions;
    string GetLoginDateAndTime()
    {
        return _LoginDateAndTime;
    }
    void SetGetLoginDateAndTime(string LoginDateAndTime)
    {
        _LoginDateAndTime = LoginDateAndTime;
    }
    __declspec(property(get = GetLoginDateAndTime, put = SetGetLoginDateAndTime))string LoginDateAndTime;

    string GetLogOutDateAndTime()
    {
        return _LogOutDateAndTime;
    }
    void SetGetLogOutDateAndTime(string LogOutDateAndTime)
    {
        _LogOutDateAndTime = LogOutDateAndTime;
    }
    __declspec(property(get = GetLogOutDateAndTime, put = SetGetLogOutDateAndTime))string LogOutDateAndTime;

    //==================================================================================

    const bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    const bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    //constructor
    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password,short Permission)
        :clsPerson(FirstName,LastName,Email,Phone)
    {

        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permission;
    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->Permissions == enPermissions::eAll)
            return true;

        if ((Permission & this->Permissions) == Permission)
            return true;
        else
            return false;

    }
    //==================================================================================
    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }
        return _GetEmptyUserObject();
    }

    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;

    }

    void SaveUsersActions()
    {
        _AddDataLineToFile(_UserActionsDataLine(), "UsersActions.txt");
    }
    //==================================================================================
    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }

    }

    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    bool IsMakeThisActions(enPermissions Action)
    {

        if ((_Actions & Action) == Action)
        {
            return true;
        }
        return false;
    }

    //==================================================================================
    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    //==================================================================================

    void RegisterLogIn()
    {
        string stDataLine = _PrepareLogInRecord();
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    static  vector <stLoginRegisterRecord> GetLoginRegisterList()
    {
        return _LoadLoginRegisterList();
    }

    static void UpdateLoginRegisterFile()
    {
        vector<stLoginRegisterRecord>vRegisterLines = GetLoginRegisterList();
        vRegisterLines[vRegisterLines.size() - 1].LogoutDateTime = clsDate::GetSystemDateTimeString();
        _SaveUpdatedLoginRegisterDataInFile(vRegisterLines);
    }









};

