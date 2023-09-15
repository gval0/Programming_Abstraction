/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

// function prototypes
int combinations(int n, int k);

int main() {
	
	int n,k;
	while(true){
		n = getInteger("enter n: ");
		if(n >= 0) break;
		cout << "Invalid input." << endl;
	}
	
	while(true){
		k = getInteger("enter k: ");
		if(n >= 0 && k <= n) break;
		cout << "Invalid input." << endl;
	}

    cout << combinations(n,k)<< endl;
    return 0;
}

// returns C(k, from n)
int combinations(int n, int k){
	if(k == 0 || k == n ) return 1;
	return combinations(n-1,k) + combinations(n-1,k-1);
}
