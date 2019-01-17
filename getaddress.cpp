/************************
//Name: Shawn Anthony
//
//Homework: Project 2
//
//Class: ICS 212
//
//Instructor: Ravi Narayan
//
//Date: November 15, 2018
//
//File: getaddress.cpp
//
//Description: File containing functions to obtain input
//  from the user for the databaseui
************************/

#include <istream>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <sstream>
#include "getaddress.h"

/************************
//Function Name: getaddress
//
//Description:  A databaseui function
//	This function obtains an address from the user
//
//Parameters: address, the array to contain the address at end of function
//	      num, the number of characters to obtain
//
//Return: 1 on success
//        0 on failure
************************/
int getaddress(char address[], int num)
{
    int size, i, retval, done, valid;
    char temp[80];
    char comp[2];

    done = 0;
    retval = 1;
    valid = 0;
    strncpy(address, "", 80);

    while (done == 0)
    {

        std::cin.getline(temp, 80);

        size = strlen(temp);
        comp[0] = temp[0];
        comp[1] = '\0';

        if (strcmp(comp, "~") == 0)
        {
            done = 1;
        }

        for (i = 0; i < size - 2; i++)
        {
            if (isdigit(temp[i]) == 0 && isalpha(temp[i]) == 0 && !isspace(temp[i]))
            {
                retval = 0;
            }
        }

        comp[0] = temp[size - 1];
        if (strcmp(comp, "~") == 0)
        {
            strncat(address, temp, size - 2);
            done = 1;
        }
        else
        {
            strcat(address, temp);
        }
    }

    for (i = 0; i < strlen(address); i++)
    {
        if (address[i] != '\n' && valid == 0)
        {
            valid = 1;
        }
    }

    if (valid == 1)
    {
        retval = 1;
    }
    else
    {
        retval = 0;
    }

    if (address[strlen(address) - 1] == '\n')
    {
        address[strlen(address) - 1] = '\0';
    }

    return retval;
}

/************************
//Function Name: getname
//
//Description:  A databaseui function
//      This function obtains a name from the user
//
//Parameters: name, the array to contain the address at end of function
//
//Return: true on success
//        false on failure
************************/
bool getname(char name[])
{
    int i = 0;
    bool retval = true;

    std::cin.getline(name, 25);
    name[strlen(name)] = '\n';

    if (strlen(name) == 1)
    {
        retval = false;
    }

    while (name[i] != '\n')
    {
        if (!isalpha(name[i]) && !isblank(name[i]))
        {
            retval = false;
        }
        i++;
    }
    name[i] = '\0';
    return retval;
}

/************************
//Function Name: getaccount
//
//Description:  A databaseui function
//      This function obtains an account number from the user
//
//Parameters: accountno, the pointer to int to contain the address at end of function
//
//Return: true on success
//        false on failure
************************/
bool getaccount(int& accountno)
{
    std::string userinput;
    bool isValid = true;

    std::getline(std::cin, userinput);
    for (int i = 0; i < (int)userinput.length(); i++)
    {
        if (isdigit(userinput[i]) == 0)
        {
            isValid = false;
        }
    }
    if (isValid == true)
    {
        std::istringstream(userinput) >> accountno;
        if (accountno < 1)
        {
            isValid = false;
        }
    }
    return isValid;
}

