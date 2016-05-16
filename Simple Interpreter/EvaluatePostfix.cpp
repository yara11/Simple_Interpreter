#include "EvaluatePostfix.h"
#include "Stack.h"
using namespace std;
// converts a pair of integers to a double x = a.b
double makeDouble(int whole,int frac, int k)
{
    double a = (double)whole;
    double b = (double)frac;
    // divide b by 10^(no. of digits in frac)
    while(k > 0)
    {
        k--;
        b /= 10;
    }
    return b + a;
}
bool isDigit(char s)
{
    return s >= '0' && s <= '9';
}

bool isOperator(string s)
{
    return s == "+" || s == "-" || s == "/" || s == "*";
}

double evaluate(double A, double B, char o)
{
    switch(o)
    {
    case '+':
        return A + B;
    case '-':
        return A - B;
    case '*':
        return A * B;
    case '/':
        return A / B;
        //default: break;
    }
}
double evaluatePostfix(vector<string>&postfix, unordered_map<string,double>&MAP)
{
    int sz = postfix.size(),k,j;
    double temp,tempdicemel;
    Stack<double>stck;
    stck.initialize();
    for(int i = 0; i < sz; i++)
    {
        if(postfix[i][0]=='.')
        {
            int string_size = postfix[i].size();
            temp = 0.0;
            for(int j=1; j<string_size; j++)
            {
                temp*=10;
                temp+=postfix[i][j]-'0';
            }
            for(int j=1; j<string_size; j++)
                temp/=10;
            stck.push(temp);
        }
        else if(isdigit(postfix[i][0]))
        {
            int string_size = postfix[i].size();
            temp = 0.0;
            for(j=0; j<string_size; j++)
            {
                if(postfix[i][j] == '.')
                {
                    k=j+1;
                    break;
                }
                temp*=10;
                temp+=postfix[i][j]-'0';
            }
            tempdicemel = 0.0;
            for(k; k<string_size; k++)
            {
                tempdicemel*=10;
                tempdicemel+=postfix[i][k]-'0';
            }
            k=j+1;
            for(k; k<string_size; k++)
                tempdicemel/=10;
            stck.push(temp+tempdicemel);
        }
        else if(isalpha(postfix[i][0])){
            stck.push(MAP[postfix[i]]);
        }
        else if(isOperator(postfix[i]))
        {
            double a = stck.pop();
            double b = stck.pop();
            stck.push(evaluate(b, a,postfix[i][0]));
        }
    }
    return stck.pop();

}


