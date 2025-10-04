#pragma once
#include <iostream>
#include "clsUser.h";

using namespace std;

clsUser CurrentUser = clsUser::Find("", "");
short ScreenWidth = 50;
string Green = clsUtil::Green();
string White = clsUtil::White();
string Blue = clsUtil::Blue();
string Yellow = clsUtil::Yellow();
string Red = clsUtil::Red();
string ClientsFileName = "BankClientsData.txt";
string SenderFileName = "InterClientsSenders.txt";
string RecipientFileName = "InterClientsRecipients.txt";
string InterTransLogFileName = "InterTransferLog.txt";


