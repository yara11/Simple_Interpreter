#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>
#define TYPE double
#include "Stack.h"
#include "InfixPostfix.h"
#include "EvaluatePostfix.h"
using namespace std;

unordered_map<string,double> MAP;

int isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int variableExists(string var)
{
    unordered_map<string,double>::iterator it = MAP.find(var);
    if(it != MAP.end())
        return 1;
    return 0;
}

int validateExpression(string exp)
{
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
    for(; i < N; i++)
    {
        //cout<<exp[i];
        if(exp[i] == ' ')   continue;
        else if(exp[i] == '(')
        {
            if(last == 't') return 0; // invalid 5(...
            last = '(';
            bracketDepth++;
        }
        else if(exp[i] == ')')
        {
            if(last != ')' && last != 't')  return 0; // invalid ...+) or ...()...
            last = ')';
            bracketDepth--;
            if(bracketDepth < 0)    return 0; // invalid 3+4)
        }
        else if(isOperator(exp[i]))
        {
            if(last != 't' && last != ')')  return 0; // invalid + + 5 or (+3
            last = 'o';
        }
        else if(isdigit(exp[i]) || exp[i] =='.')
        {
            if(last == 't' || last == ')')  return 0; // invalid (...)3 or A3
            while(isdigit(exp[i]))  i++;
            if(exp[i] == '.')
            {
                i++;
                if(!isdigit(exp[i]))    return 0; // invalid 12. + 5
                while(isdigit(exp[i]))  i++;
            }
            i--;
            last = 't';
        }
        else if(isalpha(exp[i]))
        {
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

double doEvaluation(string exp)
{
    /** Step 0 : get name of variable to store expression in**/
    int n = exp.size(), j = 0, i = 0;
    string variableToStore;

    while(exp[i] == ' ')    i++;
    j = i;
    while(isalpha(exp[j]))  j++;
    variableToStore = exp.substr(i, j - i);
    i = j;
    while(exp[i] == ' ' || exp[i] == '=')    i++;

    /** Step 1 : convert infix to postfix and add expression in a vector (rather than a string) **/
    vector<string> postfix = infixToPostfix(exp.substr(i));

    /** Step 2 : evaluate postfix **/
    double ans = evaluatePostfix(postfix, MAP);
    //cout<<"Value of expression:  "<<ans<<"\n";

    /** Step 3 : save <key,value> in map **/
    MAP[variableToStore] = ans;
    string l = " = ";
    stringstream ss;
    ss>>variableToStore;
    ss>>l;
    ss>>ans;
    return ans;
}

int main()
{
    doEvaluation("X = .532 + .5");
    doEvaluation("XYz = 2*(3+2)");
    doEvaluation("X = (12.5*X)/2.0"); // okay good...
    doEvaluation("Y = (X * (4/5))");
    doEvaluation("Z = X*Y/5");
    doEvaluation("Z=");
    doEvaluation("");
    doEvaluation("X = 1.05");
    doEvaluation("X = 32 + 64");
    doEvaluation("x = 6*7+Y");
    doEvaluation("y = 2.5 +3.5");

    for(int i=0; i<44; i++)
        cout<<' ';
    cout<<"Welcome to Simple Interpreter"<<endl<<endl;
    cout<<">> For entering the equation through the console press (c)"<<endl;
    cout<<">> For entering the equation through the file press (f)"<<endl;
    cout<<">> To exit press (e)"<<endl;
    cout<<">> Enter your command"<<endl;

    string input="";
    cin>>input;
    if(input == "c")
    {
        while(1)
        {
            cout<<">> Enter your expression or type e to exit: ";
            getline(cin, input);
            if(input == "e")
            {
                break;
            }
            int v = validateExpression(input);
            //cout<<"[ "<<v<<" ] ";
            if(v == 1)
            {
                cout<<">> The value of your expression is : "<<doEvaluation(input)<<"\n";
                //doEvaluation(input);
            }
            else if(v == 0)
            {
                cout<<">> Invalid expression. Try again.\n";
            }
            else if(v == -1)
            {
                //cout<<"\n";

            }
        }
    }


    else if(input == "f")
    {
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        while(getline(cin, input))
        {
            //cout<<">> Enter your expression or type e to exit: ";

            if(input == "e")
            {
                break;
            }
            int v = validateExpression(input);
            //cout<<"[ "<<v<<" ] ";
            if(v == 1)
            {
                cout<<">> The value of your expression is : "<<doEvaluation(input)<<"\n";
                //doEvaluation(input);
            }
            else if(v == 0)
            {
                cout<<">> Invalid expression. Try again.\n";
            }
            else if(v == -1)
            {
                //cout<<"\n";

            }
        }
    }
    else
        cout<<"Enter valid command"<<endl;

    return 0;
}
