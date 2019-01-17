/************************************
//Name: Shawn Anthony
//
//Homework: Project 2
//
//Class: ICS 212
//
//Instructor: Ravi Narayan
//
//Date: November 18, 2018
//
//File: databaseui.c
//
//Description: File containing the database ui
//for Project 2 - Bank Records
************************************/

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include "record.h"
#include "getaddress.h"
#include "llist.h"

/********************************
// Main Function for Project 1
//
// UI for managing the database and its commands
//     Handles Adding, Printing, Deleting and Reversal of records
//
// Contains Debug flags for preprocessor debug definition
*********************************/
int main(void)
{
    int quit = 0;
    char input[25];
    char file[16] = "Database.txt\0";

    /*Testing copy constructor and overloaded assignment*/
    llist *A = new llist(file);
    llist B = *A;
    llist Database;
    Database = B;
    delete A;

    #ifdef DEBUG
        std::cout << "List created.\n" << std::endl;
    #endif
  
    while (quit == 0)
    {
        std::cout << "Enter add, print, printall, delete, reverse or quit to manage the database." << std::endl;
	std::cin.getline(input, 25);

        if (strcmp(input, "add\0") == 0)
        {
            int account;
            char name[25];
            char address[200];

            strncpy(address, "", sizeof(address));
            std::cout << "Add Selected, Please provide data to add new record.\n" << std::endl;

            std::cout << "Enter name to add." << std::endl;
            while (getname(name) == 0)
            {
                std::cout << "Name was invalid, enter a new name." << std::endl;
                
            }

            std::cout << "Enter account number to add." << std::endl;
            while (getaccount(account) == 0)
            {
                std::cout << "Account number was invalid, enter a new number." << std::endl;
            }

            std::cout << "Enter address to add, Enter ~ when done." << std::endl;
            while (getaddress(address, 200) == 0)
            {
                std::cout << "Address was invalid, enter a new address." << std::endl;
            }
            
            Database.addRecord(account, name, address);
            std::cout << "Record added to Database. \n" << std::endl;

            #ifdef DEBUG
                std::cout << "\nThe value of input = " << input << std::endl;
                std::cout << "The function called was addRecord" << std::endl;
                std::cout << "The value of account = " << account << std::endl;
                std::cout << "The value of name = " << name << std::endl;
                std::cout << "The value of addres: \n" << address << std::endl;
            #endif      
        }

        if (strcmp(input, "print\0") == 0)
        {
            int account;
            std::cout << "Print Selected." << std::endl;
            
            if (!Database.isempty())
            {
                std::cout << "Enter account number to print." << std::endl;
                while (getaccount(account) == 0)
                {
                    std::cout << "Account number was invalid, enter a new number." << std::endl;
                }

                std::cout << "Attempting to print records matching the account number." << std::endl;
                if (Database.printRecord(account) == 1)
                {
                    std::cout << "Records matching the account number have been printed." << std::endl;
                }
                else
                {
                    std::cout << "No records with that number to print." << std::endl;
                }
            }
            else
            {
                std::cout << "Database is empty, no records available to print" << std::endl;
            }

            #ifdef DEBUG
                std::cout << "\nThe value of input = " << input << std::endl;
                std::cout << "The function called was printRecord" << std::endl;
                std::cout << "The value of account = " << account << "\n" << std::endl;
            #endif
        }

        if (strcmp(input, "printall\0") == 0)
        {
            std::cout << "\nPrintAll Selected." << std::endl;
            std::cout << "Printing all records in database." << '\n' << std::endl;
            
            std::cout << Database;

            #ifdef DEBUG
                std::cout << "\nThe value of input = " << input << std::endl;
                std::cout << "Overloaded << operator used to print list." << "\n" << std::endl;
            #endif
        }
        if (strcmp(input, "delete\0") == 0)
        {
            int account;

            std::cout << "Delete Selected." << std::endl;
            if (!Database.isempty())
            {
		std::cout << "Enter an account number to delete" << std::endl;
                while (getaccount(account) == 0)
                {
                    std::cout << "Account number was invalid, enter a new number." << std::endl;
                }

                if (Database.deleteRecord(account) == 1)
                {
                    std::cout << "Records matching the account number have been deleted." << std::endl;
                }
                else
                {
                    std::cout << "No record with that number to delete." << std::endl;
                }
            }
            else
            {
                std::cout << "Database is empty, no records available to delete." << std::endl;
            }

            #ifdef DEBUG
                std::cout << "\nThe value of input = " << input << std::endl;
                std::cout << "The function called was delete" << std::endl;
                std::cout << "The value of account = " << account << "\n" << std::endl;
            #endif
        }

        if (strcmp(input, "reverse\0") == 0)
        {
            std::cout << "Reversing the records in the list." << std::endl;
            Database.reverse();
            std::cout << "Records have been reversed.\n" << std::endl;
           
	    #ifdef DEBUG
            std::cout << "\nThe value of input = " << input << std::endl;
            std::cout << "The function called was reverse.\n" << std::endl;
            #endif
        }
        if (strcmp(input, "quit\0") == 0)
        {
            quit = 1;
        }
    }
    #ifdef DEBUG  
        std::cout << "Linked list terminated with destructor" << std::endl;
    #endif
    return 0;
}
