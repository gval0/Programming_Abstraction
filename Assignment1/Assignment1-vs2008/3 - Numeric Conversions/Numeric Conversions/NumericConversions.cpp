/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
    return 0;
}

//string to int
int stringToInt(string str){
	if(str.length() <= 1) return (str[0] - '0');

	if(str[0] == '-'){
		str = str.substr(1,str.length()-1);
		return (stringToInt(str) * (-1));
	}

	else {
		int num = str[str.length()-1] - '0';
		str = str.substr(0,str.length()-1);
		return num + 10 * stringToInt(str);
	}
}

// int to string
string intToString(int n){
	// special case of input beeing minimum integer
	if(n == INT_MIN){
		string str = intToString(INT_MAX);
		char ch = ((INT_MIN % 10)* (-1)) + '0' ;
		str[str.length()-1] = ch;
		return "-" + str ;
	}

	if (n < 0){
		return "-" + intToString(n * (-1));
	}

	if(n < 10 && n >= 0){ 
		char ch = n + '0';
		return (string() + ch);
	} 

	char ch = (n%10 + '0');
	return intToString(n/10) + (string() + ch);
}
