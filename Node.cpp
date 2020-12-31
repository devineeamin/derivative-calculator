// Devinee Amin
// dpa180001

#include "Node.h"
#include <cmath>
#include <iostream>

// default constructor
Node::Node()
{
    outer = 0;
    inner = 0;
    exp = 0;
    trig = "";
    next = nullptr;
}
// overloaded constructor
Node::Node(int out, int in, int e, std::string t, Node *n)
{
    outer = out;
    inner = in;
    exp = e;
    trig = t;
    next = n;
}

//mutators
void Node::setOuter(int out)
{
    outer = out;
}

void Node::setInner(int in)
{
    inner = in;
}

void Node::setExp(int e)
{
    exp = e;
}

void Node::setTrig(std::string t)
{
    trig = t;
}

void Node::setNext(Node *n)
{
    next = n;
}

//overloaded operator
std::ostream &operator<<(std::ostream &out, const Node &n)
{
    // outer coefficient
    if(abs(n.getOuter()) > 1)
        out << abs(n.getOuter());
    if(abs(n.getOuter()) == 1 && n.getTrig() == "" && n.getExp() == 0)
        out << abs(n.getOuter());

    // trig
    if(n.getTrig() != "")
    {
        out << n.getTrig() << " ";
        if(abs(n.getInner()) != 1)
            out << abs(n.getInner());
        out << "x";
    }
    // not trig
    else
    {
        // exponent
        if(n.getExp() == 1)
            out << "x";
        else if(n.getExp() == 0)
            out << "";
        else
            out << "x^" << n.getExp();
    }

    return out;
}
