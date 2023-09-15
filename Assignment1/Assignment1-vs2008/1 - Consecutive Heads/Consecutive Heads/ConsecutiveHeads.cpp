/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

void coinflip();

int main() {
    coinflip();
    return 0;
}

const int numOfHeads = 3;
string h = "heads"; // coresponds TRUE
string t = "tails"; // corespods FALSE

void coinflip(){
	int headsInRow = 0, flipsN=0;
	while (headsInRow != numOfHeads){
		bool flip = randomChance(0.5); 
		if(flip){
			cout << h << endl;
			headsInRow++;
		}else {
			cout << t << endl;
			headsInRow = 0;
		}
		flipsN++;
	}
	cout << "It took " << flipsN << " flips to get " 
		<< numOfHeads << " consecutive " << h << "."<< endl;
}