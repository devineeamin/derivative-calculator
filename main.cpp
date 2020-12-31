// Devinee Amin
// Reads equations from a file and calculates the derivative of each

#include "LList.h"
#include "Node.h"
#include <iostream>
#include<fstream>
#include <string>
using namespace std;

void parseEqu(LList *&equLList, string equStr);
void calculateDerivative(LList *&deriEqu);

int main()
{
    LList *originalEqu = nullptr;
    LList *derivativeEqu = nullptr;
    string equation, inFileName;
    ofstream outFile;
    ifstream inFile;

    // open input file
    cout << "Enter the name of the input file: ";
    cin >> inFileName;
    inFile.open(inFileName);
    if(!inFile)
    {
        cout << "Input File cannot open";
        return 0;
    }

    // open output files
    outFile.open("derive.txt");
    if(!outFile)
    {
        cout << "Output File cannot open";
        return 0;
    }

    // read one equation at a time
    while(getline(inFile, equation))
    {
        originalEqu = new LList;

        // parse equation
        parseEqu(originalEqu, equation);

        // sort equation LList
        originalEqu->sort();

        // calculate derivative
        derivativeEqu = new LList(originalEqu->getHead());
        calculateDerivative(derivativeEqu);

        // output derivative to file
        outFile << *derivativeEqu;

        delete originalEqu;
        delete derivativeEqu;
    }
    outFile.close();
    inFile.close();

    return 0;
}

// parseEqu function: parses an equation from a file to create a
// Node object for each term, which together forms a LList object
void parseEqu(LList *&equLList, string equStr)
{
    Node *term = nullptr;
    string currTerm = "";
    long int posSign;
    long int negSign;
    long int signPos = -1;
    long int xPos = -1;
    long int trigPos = -1;
    long int carrotPos = 0;
    string outCoef = "";
    string inCoef = "";
    int trigCounter = -11;
    bool end = false;
    bool isTrig = false;

    while(!end)
    {
        // reset variables
        signPos = -1;
        xPos = -1;
        trigPos = -1;
        carrotPos = -1;
        isTrig = false;
        term = new Node();

        // find position term ends
        posSign = equStr.find(" + ", 1);
        negSign = equStr.find(" - ", 1);
        if(posSign != -1 && negSign == -1)
            signPos = posSign + 1;
        else if(posSign == -1 && negSign != -1)
            signPos = negSign + 1;
        else if(posSign == -1 && negSign == -1)
        {
            currTerm = equStr;
            end = true;
        }
        else
        {
            if(posSign < negSign)
                signPos = posSign + 1;
            if(posSign > negSign)
                signPos = negSign + 1;
        }

        if(!end)
        {
            currTerm = equStr.substr(0, signPos - 1);
            equStr = equStr.substr(signPos);
        }

        // trig identifier
        if(currTerm.find("sin") != string::npos)
        {
            trigPos = currTerm.find("sin");
            isTrig = true;
            term->setTrig("sin");
        }
        if(currTerm.find("cos") != string::npos)
        {
            trigPos = currTerm.find("cos");
            isTrig = true;
            term->setTrig("cos");
        }
        if(currTerm.find("tan") != string::npos)
        {
            trigPos = currTerm.find("tan");
            isTrig = true;
            term->setTrig("tan");
        }

        // find x
        xPos = currTerm.find('x');

        // if not trig
        if(!isTrig)
        {
            // exponent
            carrotPos = currTerm.find('^');
            if(carrotPos != -1)
                term->setExp(stoi(currTerm.substr(carrotPos + 1)));
            else if(xPos != -1)
                term->setExp(1);
            else
                term->setExp(0);

            // outer coefficient
            if(xPos != -1)
            {
                if(currTerm.at(0) == '-')
                {
                    // if first term
                    if(currTerm.at(1) != ' ')
                        outCoef = currTerm.substr(0, xPos);
                    else
                    {
                        outCoef = currTerm.substr(2, xPos-2);
                        if(outCoef == "")
                            outCoef = "-1";
                        else
                            outCoef = "-" + outCoef;
                    }
                }
                else if(currTerm.at(0) == '+')
                    outCoef = currTerm.substr(2, xPos-2);
                else
                    outCoef = currTerm.substr(0, xPos);
                if(outCoef == "")
                    outCoef = "1";
            }
            else if(isdigit(currTerm.at(0)) == 0)
                outCoef = currTerm.substr(2);
            else
                outCoef = currTerm;

            term->setOuter(stoi(outCoef));
        }
        // if trig
        else
        {
            // exponent
            term->setExp(trigCounter);
            trigCounter--;

            // inner coefficient
            inCoef = currTerm.substr(trigPos+4, xPos - (trigPos+4));
            if(inCoef == "")
                inCoef = "1";
            term->setInner(stoi(inCoef));

            // outer coefficient
            if(currTerm.at(0) == '-')
            {
                // if first term
                if(currTerm.at(1) != ' ')
                    outCoef = currTerm.substr(0, trigPos);
                else
                {
                    outCoef = currTerm.substr(2, trigPos-2);
                    if(outCoef == "")
                        outCoef = "-1";
                    else
                        outCoef = "-" + outCoef;
                }
            }
            else if(currTerm.at(0) == '+')
                outCoef = currTerm.substr(2, trigPos-2);
            else
                outCoef = currTerm.substr(0, trigPos);
            if(outCoef == "")
                outCoef = "1";
            term->setOuter(stoi(outCoef));
        }

        // add Node to LList
        *equLList >> term;
    }
}

// calculateDerivative function: calculates the derivative
// for each given equation
void calculateDerivative(LList *&deriEqu)
{
    Node *currNode = deriEqu->getHead();

    while(currNode)
    {
        // non-trig and non-constant term
        if(currNode->getTrig() == "" && currNode->getExp() != 0)
        {
            cout << "Outer: " << currNode->getOuter() << endl;
            cout << "setOuter: " << currNode->getOuter() * currNode->getExp() << endl;
            currNode->setOuter(currNode->getOuter() * currNode->getExp());
            cout << "setExp: " << currNode->getExp() - 1 << endl;
	        currNode->setExp(currNode->getExp() - 1);
        }
        // constant term
        else if(currNode->getTrig() == "" && currNode->getExp() == 0)
        {
            currNode->setOuter(0);
        }
        //trig term
        else if(currNode->getTrig() != "")
        {
            if(currNode->getTrig() == "sin")
            {
                currNode->setTrig("cos");
                currNode->setOuter(currNode->getOuter() * currNode->getInner());
            }
            else if(currNode->getTrig() == "cos")
            {
                currNode->setTrig("sin");
                currNode->setOuter(currNode->getOuter() * currNode->getInner() * -1);
            }
            else if(currNode->getTrig() == "tan")
            {
                currNode->setTrig("sec^2");
                currNode->setOuter(currNode->getOuter() * currNode->getInner());
            }
        }
        currNode = currNode->getNext();
    }
}
