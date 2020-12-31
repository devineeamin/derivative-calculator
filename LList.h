// Devinee Amin

#ifndef LLIST_H
#define LLIST_H
#include "Node.h"
#include <iostream>

class LList
{
    private:
        Node *head;
    public:
        LList();
        LList(Node *);
        void setHead(Node *);
        void sort();
        Node *getHead();
        ~LList();

        // overloaded operators
        void operator>>(Node *);
        friend std::ostream &operator<<(std::ostream &, LList &);
        const Node *operator[](const int);
};

#endif
