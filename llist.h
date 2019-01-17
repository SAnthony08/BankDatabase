#ifndef LLIST_H
#define LLIST_H

/******************
//Name: Shawn Anthony
//
//Homework: Project 2
//
//Record: llist definition for use in bank database
*******************/
#include "record.h"

class llist
{
    private:
        record *    start;
        char        filename[16];
        int         readfile();
        void        writefile();
        record *    reverse(record *);
        void        cleanup();

    public:
        llist();
        llist(char[]);
        ~llist();
        int addRecord(int, char[], char[]);
        int printRecord(int);
        friend std::ostream& operator << (std::ostream&, llist&);
        llist & operator = (const llist);
        llist(const llist &);
        int deleteRecord(int);
        void reverse();
        bool isempty();
};

#endif /* LLIST_H */
