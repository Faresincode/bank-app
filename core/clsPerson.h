#pragma once
#include <iostream>
using namespace std;

class clsPerson
{

private:

	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;


public:


    clsPerson(string FirstName, string LastName, string Email, string Phone)
    {

        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone;
    }

    //Property Set and Get 
    void SetFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }
    const string GetFirstName()
    {
        return _FirstName;
    }
    __declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;

    //Property Set and Get 
    void SetLastName(string LastName)
    {
        _LastName = LastName;
    }
    const string GetLastName()
    {
        return _LastName;
    }
    __declspec(property(get = GetLastName, put = SetLastName)) string LastName;

    //Property Set and Get 
    void SetEmail(string Email)
    {
        _Email = Email;
    }
    const string GetEmail()
    {
        return _Email;
    }
    __declspec(property(get = GetEmail, put = SetEmail)) string Email;

    //Property Set and Get 
    void SetPhone(string Phone)
    {
        _Phone = Phone;
    }
    const string GetPhone()
    {
        return _Phone;
    }
    __declspec(property(get = GetPhone, put = SetPhone)) string Phone;

    //Get Full Name
    string FullName()
    {
        return _FirstName + " " + _LastName;
    }

    virtual void Print()
    {
        cout << "\nInfo:";
        cout << "\n___________________";
        cout << "\nFirstName: " << _FirstName;
        cout << "\nLastName : " << _LastName;
        cout << "\nFull Name: " << FullName();
        cout << "\nEmail    : " << _Email;
        cout << "\nPhone    : " << _Phone;
        cout << "\n___________________\n";

    }





};

