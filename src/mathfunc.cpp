#include "mathfunc.h"
#include <stack>
#include <vector>

#include <iostream>

#define inf 1e9

// helpers:
bool isValidString(const std::string& str)
{
    return true;
    std::string validChars = "()0123456789+-/*x";
    std::string opChars = "()+-/*";
    int balance = 0;
    bool isBeforOp = false;

    //if (opChars.find(str[0]) == std::string::npos || opChars.find(str[str.size() - 1]) == std::string::npos) { std::cout << "try2:1"; return false;}
    for (char c : str)
    {
        if (validChars.find(c) == std::string::npos) { std::cout << "try2:2"; return false;}
        if (c == '(') balance++;
        if (c == ')') balance--;
        if (balance < 0) { std::cout << "try2:3"; return false;};

        if (opChars.find(c) != std::string::npos)
        {
            if(isBeforOp) { std::cout << "try2:4"; return false;}
            isBeforOp = true;
        }
    }
    return balance == 0;
}

std::vector<int> getPriVec(std::string str)
{
    std::vector<int> vec(str.size(), inf);
    int parVal = 0;
    for(int i = 0; i < vec.size(); ++i)
    {
        if(str[i] == '(') { parVal++; continue; }
        if(str[i] == ')') { parVal--; continue; }

        if(str[i] == '+' || str[i] == '-') vec[i] = parVal + 1;
        else if(str[i] == '*' || str[i] == '/') vec[i] = parVal + 2;
    }

    return vec;
}

bool isOp(char c)
{
    std::string ops = "/*-+";
    return ops.find(c) != std::string::npos;
}

Operation toOp(char c)
{
    switch (c)
    {
        case '+' : return Operation::Add;
        case '-' : return Operation::Subtraction;
        case '*' : return Operation::Multiple;
        case '/' : return Operation::Divide;
        default  : return Operation::None; 
    }
}

size_t getMinInd(std::vector<int> vec)
{
    size_t index = 0;
    for(int i = 0; i < vec.size(); ++i)
        if(vec[index] >= vec[i]) index = i;

    return index;
}

// build tree : 
void Node::buildTree(std::string str)
{
    static int a = 0;a++;
    int b = 0;
    std::cout << "not ex1 " << a <<b<< "\n"; b++;
    std::vector<int> priVec = getPriVec(str);
    size_t minInd = getMinInd(priVec);

    if(isOp(str[minInd]))
    {
        std::cout << "not ex2 "<<a<<b<<"\n";b++;
        op = new Operation;
        *op = toOp(str[minInd]);
        left = new Node(str.substr(0, minInd));
        right = new Node(str.substr(minInd + 1));
    }
    else
    {
        std::cout << "not ex3 "<<a<<b<<"\n";b++;
        value = new double;
        if(str.size() == 1 && str[0] == 'x') isValueX = true;
        else
        {
            if(str.size() > 1 && str.front() == '(' && str.back() == ')')
               str = str.substr(1, str.size() - 2);

            *value = std::stod(str);
        }
    }
}

void MathFunction::translateMath()
{
    if (isValidString(funcStr) == false) exit(1);
    node.buildTree(funcStr);
    return;
}

double Node::foundSearch(double x)
{
    if(isValueX) return x;
    if(value != nullptr) return *value;

    switch (*op)
    {
        case Operation::Add         : return left->foundSearch(x) + right->foundSearch(x);
        case Operation::Subtraction : return left->foundSearch(x) - right->foundSearch(x);
        case Operation::Divide      : return left->foundSearch(x) / right->foundSearch(x);
        case Operation::Multiple    : return left->foundSearch(x) * right->foundSearch(x);
        default                     : return 0;
    }
}