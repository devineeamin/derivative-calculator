// Devinee Amin

#include "LList.h"
#include "Node.h"
#include <iostream>

// default constructor
LList::LList()
{
    head = nullptr;
}

//overloaded constructor
LList::LList(Node *h)
{
    Node *ptr = nullptr;
    head = nullptr;

    while(h)
    {
        Node *newNode = new Node(h->getOuter(), h->getInner(), h->getExp(), h->getTrig(), h->getNext());

        if(!head)
        {
            head = newNode;
            ptr = head;
        }
        else
        {
            ptr->setNext(newNode);
            ptr = ptr->getNext();
        }
        h = h->getNext();
    }
}

//destructor
LList::~LList()
{
    Node *ptr = head;

    while(ptr)
    {
        if(head->getNext())
        {
            ptr = head->getNext();
            head->setNext(nullptr);
        }
        else
            ptr = nullptr;

        delete head;
        head = ptr;
    }
}

// mutators
void LList::setHead(Node *h)
{
    head = h;
}

void LList::sort()
{
    // selection sort
    Node *maxPtr = nullptr;
    Node *maxPrev = nullptr;
    Node *currPtr = nullptr;
    Node *startNext = nullptr;
    Node *startPrev = nullptr;
    Node *startPtr = head;

    while(startPtr)
    {
        maxPtr = startPtr;
        maxPrev = startPtr;
        startPrev = head;
        currPtr = startPtr->getNext();
        startNext = startPtr->getNext();

        while(startPtr != head && startPrev->getNext() != startPtr)
            startPrev = startPrev->getNext();
        // find max value
        while(currPtr)
        {
            if(currPtr->getExp() > maxPtr->getExp())
            {
                maxPtr = currPtr;
                while(maxPrev->getNext() != maxPtr)
                    maxPrev = maxPrev->getNext();
            }
            currPtr = currPtr->getNext();
        }
        // swap
        if(maxPtr != startPtr)
        {
            if(head == startPtr)
                head = maxPtr;

            if(startNext == maxPtr)
            {
                startPtr->setNext(maxPtr->getNext());
                maxPtr->setNext(startPtr);
                if(startPtr != startPrev)
                    startPrev->setNext(maxPtr);

                startNext = maxPtr->getNext();
            }
            else
            {
                startPtr->setNext(maxPtr->getNext());
                maxPtr->setNext(startNext);
                maxPrev->setNext(startPtr);
                if(startPtr != startPrev)
                    startPrev->setNext(maxPtr);
            }

        }
        startPtr = startNext;
    }
}

//accessor
Node *LList::getHead()
{
    return head;
}


//overloaded operators
void LList::operator>>(Node *n)
{
    if(!head)
        head = n;
    else
    {
        n->setNext(head);
        head = n;
    }
}

std::ostream &operator<<(std::ostream &out, LList &obj)
{
    Node *currPtr = obj.getHead();
    int i = 0;
    bool firstTerm = true;

    while(currPtr)
    {
        // print if outer coefficient is not 0
        if(obj[i]->getOuter() != 0)
        {
            // if this is the first term
            if(i == 0 || firstTerm)
            {
                if(obj[i]->getOuter() < 0)
                    out << "-";
            }
            else
            {
                if(obj[i]->getOuter() < 0)
                    out << " - ";
                else
                    out << " + ";
            }
            // print node
            out << *obj[i];
            firstTerm = false;
        }
        else if(i == 0)
            firstTerm = true;

        i++;
        currPtr = currPtr->getNext();
    }
    out << std::endl;
    return out;
}

const Node *LList::operator[](int index)
{
    Node *currPtr = this->getHead();

    for(int i = 0; i < index; i++)
        currPtr = currPtr->getNext();

    return currPtr;
}
