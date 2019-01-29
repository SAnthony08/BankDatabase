/******************
//Name: Shawn Anthony
//
//Homework: Project 2
//
//TESTCOMMIT
//
//Record: struct definition for use in bank database
*******************/
#ifndef RECORD_H
#define RECORD_H

struct record
{
    int accountno;
    char name[25];
    char address[80];
    struct record* next;
};

#endif /* RECORD_H */
