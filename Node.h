// Devinee Amin
// dpa180001

#ifndef NODE_H
#define NODE_H
#include <string>
#include <iostream>

class Node
{
    private:
        int outer;
        int inner;
        int exp;
        std::string trig;
        Node *next;
    public:
        //constructors
        Node();
        Node(int out, int in, int e, std::string t, Node *n);

        //mutators
        void setOuter(int);
        void setInner(int);
        void setExp(int);
        void setTrig(std::string);
        void setNext(Node *);

        //accessors
        int getOuter() const { return outer; }
        int getInner() const { return inner; }
        int getExp() const { return exp; }
        std::string getTrig() const { return trig; }
        Node *getNext() const { return next; }

        //overloaded operators
        friend std::ostream &operator<<(std::ostream &, const Node &);
};

#endif
