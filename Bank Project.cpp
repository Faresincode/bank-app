
#include <iostream>
#include "clsMainScreen.h";
#include "clsUser.h";
#include "clsLoginScreen.h";
#include "clsDate.h";
#include "clsPerson.h";
#include "clsCurrency.h";
#include <windows.h>
#include <fstream>
#include "clsMath.h";

#include "clsInputValidate.h";


using namespace std;



int main()
{
    
    while (!clsLoginScreen::ShowLoginScreen())
    {

        break; 


    }



    return 0;

}


