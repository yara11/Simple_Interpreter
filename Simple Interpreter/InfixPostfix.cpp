#include "InfixPostfix.h"
#include <vector>
#include <iostream>
#include "Stack.h"
using namespace std;
//#include "mapFile.h"


// converts a pair of integers to a double x = a.b
/*double makeDouble(int whole,int frac, int k){
    double a = (double)whole;
    double b = (double)frac;
    // divide b by 10^(no. of digits in frac)
    while(k > 0){
        k--;
        b /= 10;
    }
    return b + a;
}*/

// TO DO : ADD MOD
int precedence(char c){
    switch(c){
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    default: return 0;
    }
}


string charToString(char c){
    string s = "";
    s += c;
    return s;
}

vector<string> infixToPostfix(string infix){
    Stack<char> myStack; /// new linked-list-based stack;
    myStack.initialize();

    vector<string>postfix;
    int N = infix.size();
    for(int i = 0; i <N; i++){
        if(infix[i] == ' ')
            continue;
        if(isdigit(infix[i]) || infix[i] == '.'){
            int stt = i, endd = i;
            while(i < N && isdigit(infix[i]))   i++;
            if(infix[i] == '.'){
                i++;
                while(i < N && isdigit(infix[i]))   i++;
            }
            endd = i;
            postfix.push_back(infix.substr(stt, endd - stt));
            i--;
        }
        else if(isalpha(infix[i])){
            int stt = i, endd = i;
            while(i < N && isalpha(infix[i])) i++;
            endd = i;
            postfix.push_back(infix.substr(stt, endd - stt));
            i--;
        }
        else if(infix[i] == '('){
            myStack.push('(');
        }
        else if(infix[i] == ')'){
            while(myStack.peek() != '('){
                postfix.push_back(charToString(myStack.pop()));
                //myStack.pop();
                //postfix.push_back("x");
            }
            myStack.pop();
        }
        else if(isOperator(infix[i])){
            while(!myStack.isEmpty() && precedence(myStack.peek()) >= precedence(infix[i])){
                postfix.push_back(charToString(myStack.pop()));
                //postfix.push_back("x");
                //myStack.pop();
            }
            myStack.push(infix[i]);
        }
    }

    while(!myStack.isEmpty()){
        postfix.push_back(charToString(myStack.pop()));
        //postfix.push_back("x");
        //myStack.pop();
    }

    return postfix;
}
