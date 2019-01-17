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

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "record.h"
#include "llist.h"
#include "getaddress.h"


/********************************************
//Function Name: Default Constructor
//
//Description: Default constructor, sets initial values for member variables
//
//Parameters: None
//
//Return: None
********************************************/
llist::llist()
{
    start = NULL;
    strcpy(filename, "");
}

/********************************************
//Function Name: Constructor
//
//Description: Constructor, sets initial values for member variables
//
//Parameters: char file[], the name of the file corresponding to the list
//
//Return: None
********************************************/
llist::llist(char file[])
{
    strncpy(filename, file, 16);
    start = NULL;
    readfile();
}

/********************************************
//Function Name: Destructor
//
//Description: Destructor for linked list class, writes to file and deallocates memory
//
//Parameters: None
//
//Return: None
********************************************/
llist::~llist()
{
    writefile();
    cleanup();
}

/********************************************
//Function Name: readfile
//
//Description: Reads the specified file for records
//
//Parameters: None
//
//Return: 1 on success
//        0 on failure
********************************************/
int llist::readfile()
{
    char *token;
    int retval, account, validCheck, i;
    char str[150], name[25], address[80];

    const char delim[2] = ",";
    retval = 1;
    std::string temp;
    std::fstream myFile;
    myFile.open(filename);

    if (myFile.is_open())
    {
        while (std::getline(myFile, temp))
        {
            strcpy(str, temp.c_str());
            validCheck = 0;
            for (i = 0; i < (int)strlen(str) - 1; i++)
            {
                if (str[i] == '_')
                {
                    str[i] = '\n';
                }
            }

            for (i = 0; i < (int)strlen(str) - 1; i++)
            {
                if (str[i] == ',')
                {
                    validCheck++;
                }
            }

            if (validCheck == 2)
            {
                token = strtok(str, delim);
                account = atoi(token);

                while (token != NULL)
                {
                    token = strtok(NULL, delim);
                    strncpy(name, token, 25);
                    token = strtok(NULL, delim);
                    strncpy(address, token, 80);
                    token = strtok(NULL, delim);
                }

                if (address[strlen(address) - 1] == '\n')
                {
                    address[strlen(address) - 1] = '\0';
                }

                addRecord(account, name, address);
            }
        }
        myFile.close();
    }
    else
    {
        retval = 0;
    }
    return retval;
}

/********************************************
//Function Name: writefile
//
//Description: Writes database to the file specified by filename in the list
//
//Parameters: None
//
//Return: None
********************************************/
void llist::writefile()
{
    int i;
    struct record *current;
    current = start;

    std::fstream myFile;
    myFile.open(filename, std::fstream::out);

    while (current != NULL)
    {
        for (i = 0; i < (int)strlen(current->address) - 1; i++)
        {
            if (current->address[i] == '\n')
            {
                current->address[i] = '_';
            }
        }
        if (current->next == NULL)
        {
            myFile << current->accountno << "," << current->name << "," << current->address;
            current = current->next;
        }
        else
        {
            myFile << current->accountno << "," << current->name << "," << current->address << std::endl;
            current = current->next;
        }
    }
    myFile.close();
}

/********************************************
//Function Name: reverse
//
//Description: Recursive reverse method, reverses the list pointed to by start
//
//Parameters: record *start, the record to start recursion from
//
//Return: record *result, the result of the recursive call
********************************************/
record * llist::reverse(record * start)
{
    record* result;

    if (!(start && start->next))
    {
        result = start;
    }
    else 
    {
        result = reverse(start->next);
        start->next->next = start;
        start->next = NULL;
    }
    return result;
}

/********************************************
//Function Name: cleanup
//
//Description: Deletes all records using dynamic memory upon call
//
//Parameters: None
//
//Return: None
********************************************/
void llist::cleanup()
{
    struct record * current;
    current = start;
    while (!isempty())
    {
        start = current->next;
        delete current;
        current = start;
    }
}

/********************************************
//Function Name: addRecord
//
//Description: Add the record with provided data to the list
//
//Parameters: int account, the account number to add
//            char name[], the name to add
//            char address[], the address to add
//
//Return: 1 always
********************************************/
int llist::addRecord(int account, char name[], char address[])
{
    struct record *current;
    int addDone = 0;

    if (start == NULL)
    {
        current = new record;
        current->accountno = account;
        strncpy(current->name, name, 25);
        strncpy(current->address, address, 80);
        current->next = NULL;
        start = current;
    }
    else
    {
        struct record *newrec;
        struct record *prevrec;

        prevrec = NULL;
        newrec = new record;
        current = start;

        newrec->accountno = account;
        strncpy(newrec->name, name, 25);
        strncpy(newrec->address, address, 80);

        if (account <= current->accountno)
        {
            newrec->next = current;
            start = newrec;
            addDone = 1;
        }

        while (current != NULL && addDone == 0)
        {

            if (account <= current->accountno)
            {
                newrec->next = current;
                prevrec->next = newrec;
                addDone = 1;
            }

            else
            {
                prevrec = current;
                current = current->next;
            }
        }
        if (addDone == 0)
        {
            prevrec->next = newrec;
            newrec->next = NULL;
        }
    }
    return 1;
}

/********************************************
//Function Name: printRecord
//
//Description: Prints the records corresponding to the given account number
//
//Parameters: int account, the account number to print
//
//Return 0 on failure
//       1 on success
********************************************/
int llist::printRecord(int account)
{
    int retval;
    struct record *current;

    current = start;
    retval = 0;

    while (current != NULL)
    {
        if (current->accountno != account)
        {
            current = current->next;
        }
        else
        {
            std::cout << "\n" << current->accountno << "\n" << current->name << "\n" << current->address << "\n" << std::endl;

            current = current->next;
            retval = 1;
        }
    }
    return retval;
}

/********************************************
//Function Name: Overloaded << operator
//
//Description: Overloaded << operator to print data from llist object
//
//Parameters: ostream &os, the stream to write to
//            llist &llist, the list to write data for 
//
//Return: os, the stream of data to output
********************************************/
std::ostream & operator <<(std::ostream & os, llist& list)
{
    struct record *current = list.start;
    while (current != NULL)
    {
        os << current->accountno << std::endl;
        os << current->name << std::endl;
        os << current->address << '\n' << std::endl;

        current = current->next;
    }
    return os;
}

/********************************************
//Function Name: deleteRecord
//
//Description: Deletes all records sharing the given account number
//
//Parameters: int account, the number to delete records associated with
//
//Return: 0 on failure
//        1 on success
********************************************/
int llist::deleteRecord(int account)
{
    int retval;
    struct record *current, *prevrec;

    retval = 0;
    current = start;
    prevrec = NULL;

    while (current != NULL && current->accountno == account)
    {
        start = current->next;
        delete current;
        current = start;
        retval = 1;
    }

    while (current != NULL)
    {
        while (current != NULL && current->accountno != account)
        {
            prevrec = current;
            current = current->next;
        }
        if (current != NULL)
        {
            prevrec->next = current->next;
            delete current;
            current = prevrec->next;
            retval = 1;
        }
    }
    return retval;
}

/********************************************
//Function Name: reverse
//
//Description: Public non-recursive reverse
//
//Parameters: None
//
//Return: None
********************************************/
void llist::reverse()
{
    start = reverse(start);
}

/********************************************
//Function Name: Overloaded = operator
//
//Description: Overloaded assignment, creates deep copies of records in list on assignment
//             Does not allow self assignment.
//Parameters: llist to copy
//
//Return: A pointer to the new object
********************************************/
llist & llist::operator =(const llist list)
{
    if (this != &list)
    {
        record *newrec, *oldrec, *current;
        if (list.start == NULL)
        {
            start = NULL;
        }
        else
        {
            while (start != NULL)
            {
                record * temp = start;
                start = start->next;
                delete temp;
            }

            oldrec = list.start;

            newrec = new record;
            newrec->accountno = oldrec->accountno;
            strcpy(newrec->name, oldrec->name);
            strcpy(newrec->address, oldrec->address);
            newrec->next = NULL;
            start = newrec;

            current = start;
            oldrec = oldrec->next;

            while (oldrec != NULL)
            {
                newrec = new record;
                newrec->accountno = oldrec->accountno;
                strcpy(newrec->name, oldrec->name);
                strcpy(newrec->address, oldrec->address);
                newrec->next = NULL;

                current->next = newrec;
                current = current->next;
                oldrec = oldrec->next;
            }
        }
        strcpy(filename, list.filename);
    }
    return *this;
}

/********************************************
//Function Name: Copy Constructor
//
//Description: Copy constructor, creates deep copies of records in list on copy
//
//Parameters: llist address to copy
//
//Return: None
********************************************/
llist::llist(const llist & list)
{
    record *newrec, *oldrec, *current;
    if (list.start == NULL)
    {
        start = NULL;
    }
    else
    {
        oldrec = list.start;

        newrec = new record;
        newrec->accountno = oldrec->accountno;
        strcpy(newrec->name, oldrec->name);
        strcpy(newrec->address, oldrec->address);
        newrec->next = NULL;
        start = newrec;

        current = start;
        oldrec = oldrec->next;

        while (oldrec != NULL)
        {
            newrec = new record;
            newrec->accountno = oldrec->accountno;
            strcpy(newrec->name, oldrec->name);
            strcpy(newrec->address, oldrec->address);
            newrec->next = NULL;

            current->next = newrec;
            current = current->next;
            oldrec = oldrec->next;
        }
    }
    strcpy(filename, list.filename);
}

/********************************************
//Function Name: isempty
//
//Description: Function that tells you if the list is empty
//
//Parameters: None
//
//Return: true if empty
//        false if not empty
********************************************/
bool llist::isempty()
{
    bool retval;

    if (start == NULL)
    {
        retval = true;
    }
    else
    {
        retval = false;
    }
    return retval;
}
