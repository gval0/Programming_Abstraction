/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include <fstream>
#include "strlib.h"
#include "simpio.h"
#include "map.h"
#include "vector.h"
#include "random.h"
using namespace std;

/* Function prototype */
void readFile(ifstream& f);
int getMarkovOrder();
void analyzeText(ifstream& f, int n, Map<string,Vector<char>  >& m);
void randomWrite(Map<string, Vector<char>  >& m, int n);
string getMostCommonSequence(Map<string,Vector<char>  >& m);
char randomChar (string s, Map<string,Vector<char>  >& m);

/* constants */
const int maxRandomChars = 2000;

/*
main function
interact with user
displays random text generated
*/
int main() {
	ifstream textFile;
	readFile(textFile);
	int order = getMarkovOrder();
	cout << "Processing file..." << endl;

	Map<string,Vector<char>  > charMap;
	analyzeText(textFile, order, charMap);
	textFile.close();
	randomWrite(charMap, order);
	
    return 0;
}

/* reads file */
void readFile(ifstream& textFile){
	string fileName;
	while(true){
		fileName = getLine("Enter the source text: ");
		textFile.open(fileName.c_str());
		if(!textFile.fail())break; 
		textFile.clear();
		cout << "Unable to open the file. Try again." << endl;
	}
}

/* reads markov order from user */
int getMarkovOrder(){
	int num;
	while(true){
		num = getInteger("Enter the Markov order [1-10]: ");
		if(num > 0 && num < 11) return num;
		cout << "That value is out of range" << endl;
	}
}

/*
reads text char by char
writes in map markov order and what follows it
*/
void analyzeText(ifstream& textFile, int order, Map<string,Vector<char>  >& charMap){
	string curSequence;
	char ch;
	while(textFile.get(ch)){
		if(curSequence.length() != order)curSequence += string() + ch; 
		else {
			charMap[curSequence].add(ch);
			curSequence = curSequence.substr(1, order - 1) + ch;
		}
	}
}

/* displays randomly generated text */
void randomWrite(Map<string,Vector<char>  >& charMap, int order){
	string curSequence = getMostCommonSequence(charMap);
	cout << curSequence;
	for(int i = order; i < maxRandomChars; i++){
		if(!charMap.containsKey(curSequence)) break;
		char nextChar = randomChar(curSequence, charMap);
		cout << nextChar;
		curSequence += nextChar;
		curSequence = curSequence.substr(1, order);
	}
	cout << endl;
}

/* returns most common markov order */
string getMostCommonSequence(Map<string,Vector<char>  >& charMap){
	string mostCommonSequence = "";
	int sequenceN = INT_MIN;
	foreach(string curStr in charMap){
		if(charMap[curStr].size() > sequenceN){
			mostCommonSequence = curStr;
			sequenceN = charMap[curStr].size();
		}
	}
	return mostCommonSequence;
}

/* returns random char from vector with equal probablity */
char randomChar(string str, Map<string,Vector<char>  >& charMap){
	Vector<char> v = charMap[str];
	int index = randomInteger(0, v.size() - 1);
	return v.get(index);
}
	
