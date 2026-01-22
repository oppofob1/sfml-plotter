#ifndef MATHFUNC_H
#define MATHFUNC_H

#include <string>

enum class Operation { Multiple, Divide, Add, Subtraction, None };

class Node
{
private:
    Node* left = nullptr;
    Node* right = nullptr;

    double *value = nullptr;
    Operation *op = nullptr;

    bool isValueX = false;

public:
    Node() = default;

    Node(std::string str) { buildTree(str); }
    ~Node()
    {
        delete left;
        delete right;
        delete op;
        delete value;
    }

    void buildTree(std::string str);
    
    double foundSearch(double x);
}; // Class Node

class MathFunction
{
private:
    std::string funcStr;
    Node node;

public:
    MathFunction(std::string str)
        : funcStr(str)
    {
        translateMath();
    }

    // string to math helpers:
    void translateMath(); 

    // cpp function
    double func(double x) { return node.foundSearch(x); }
};

#endif