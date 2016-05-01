#ifndef INFIXPOSTFIX_H_
#define INFIXPOSTFIX_H_
#include <vector>
#include <iostream>
using namespace std;

vector<string> infixToPostfix(string infix);
int isOperator(char c);
int precedence(char c);
string charToString(char c);
//double makeDouble(int whole,int frac);

#endif
