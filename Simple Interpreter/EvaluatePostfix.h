#ifndef EVALUATEPOSTFIX_H_
#define EVALUATEPOSTFIX_H_
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
	double evaluatePostfix(vector<string>&postfix, unordered_map<string,double>&MAP);
	double makeDouble(int whole,int frac);

#endif
