#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <iostream>
#include <unordered_map>
#define TYPE double
#include "Stack.h"

using namespace std;

unordered_map<string,double> MAP;

int isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int variableExists(string var){
    unordered_map<string,double>::iterator it = MAP.find(var);
    if(it != MAP.end())
        return 1;
    return 0;
}

int validateExpression(string exp){
    int N = exp.size();
    int i = 0;
    int bracketDepth = 0;
    /** First term (right hand side) **/
    while(exp[i] == ' ')    i++;
    if(i == N)  return -1; // empty expression, make newline
    if(!isalpha(exp[i]))    return 0; // x = 1 + 3*A
    while(isalpha(exp[i]))  i++;
    while(exp[i] == ' ')    i++;
    if(exp[i] != '=')   return 0; /// '=' missing

    /** Remaining terms **/
    char last = '='; /// 'o' = operator, 't' = term, '(', ')', '='
    i++;
    while(i < N && exp[i] == ' ')    i++;
    if(i == N)  return 0; /// empty expression
    for(; i < N; i++){
        //cout<<exp[i];
        if(exp[i] == ' ')   continue;
        else if(exp[i] == '('){
            if(last == 't') return 0; // invalid 5(...
            last = '(';
            bracketDepth++;
        }
        else if(exp[i] == ')'){
            if(last != ')' && last != 't')  return 0; // invalid ...+) or ...()...
            last = ')';
            bracketDepth--;
            if(bracketDepth < 0)    return 0; // invalid 3+4)
        }
        else if(isOperator(exp[i])){
            if(last != 't' && last != ')')  return 0; // invalid + + 5 or (+3
            last = 'o';
        }
        else if(isdigit(exp[i]) || exp[i] =='.'){
            if(last == 't' || last == ')')  return 0; // invalid (...)3 or A3
            while(isdigit(exp[i]))  i++;
            if(exp[i] == '.'){
                i++;
                if(!isdigit(exp[i]))    return 0; // invalid 12. + 5
                while(isdigit(exp[i]))  i++;
            }
            i--;
            last = 't';
        }
        else if(isalpha(exp[i])){
            if(last == 't' || last == ')')  return 0; // invalid (...)A or 3 A
            int j = i;
            while(isalpha(exp[j]))  j++;
            string sub = exp.substr(i, j - i);
            //cout<<sub;
            if(!variableExists(sub))    return 0; // invalid symbol (undefined variable)
            i = j - 1;
            last = 't';
        }
        else return 0;
    }
    //cout<<"TADA -- Almost!  ";
    if(bracketDepth != 0 || last == 'o')
        return 0;
        //cout<<"TADAA!  ";
    return 1;
}

int main()
{
    return 0;
}
