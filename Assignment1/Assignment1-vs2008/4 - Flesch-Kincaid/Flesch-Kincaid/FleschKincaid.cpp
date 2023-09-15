/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include <fstream>
#include "simpio.h"
#include "tokenscanner.h"
#include "strlib.h"
using namespace std;


struct stats{
	int words;
	int sentences;
	int syllables;
	double difficulty;
};

// function prototypes 
stats processText(TokenScanner scanner);
bool isWord(string s);
int countSyllables(string s);
bool isVowel(char ch);
bool isEndOfSentence(string s);
void printResult(stats s);
double calculateDifficulty(stats s);


int main() {
	
	//open file
	ifstream file;
	while(true){
		string filename = getLine("Enter file name: ");
		file.open(filename.c_str());
		if(!file.fail()) break;
		file.clear();
		cout << "Invalid file name, try again!" << endl;
	}
	
	// read file w tokenscanner
	TokenScanner scanner(file);

	// analyze tokens
	stats ans = processText(scanner);
	file.close();

	//print results
	printResult(ans);
    return 0;
}

// counts words, sentences, syllables, difficulty
stats processText(TokenScanner scanner){

	scanner.ignoreWhitespace();
	scanner.addWordCharacters("'");

	stats result;
	result.words = 0;
	result.sentences = 0;
	result.syllables = 0;
	result.difficulty = 0;

	while(scanner.hasMoreTokens()){
		string token = scanner.nextToken();
		token = toLowerCase(token);

		if(isWord(token)) {
			result.words += 1;
			result.syllables += countSyllables(token);//coutns syllabels
		}

		else if (isEndOfSentence(token)) 
			result.sentences += 1;

	}

	//to prevent devision by 0
	if(result.words == 0) result.words =1;
	if(result.sentences == 0) result.sentences =1;
	result.difficulty = calculateDifficulty(result);
	return result;
}

// returns true if token starts with word letter
bool isWord(string s){
	if(s[0] >= 'a' && s[0] <= 'z'){
		return true;
	} 
	return false;	
}

//counts syllables in a word
int countSyllables(string s){
	int result = 0;
	if(s.length() <= 1) return 1;
	for(int i=1; i< s.length()-1; i++){
		if(isVowel(s[i]) && !isVowel(s[i-1])) result ++;
	}
	if(isVowel(s[s.length()-1]) && !isVowel(s[s.length()-2]) && s[s.length()-1] != 'e')
		result++;
	if (isVowel(s[0])) result++;
	if(result == 0) result = 1;
	return result;
}

// returns true if character is vowel (a,e,i,o,u,y)
bool isVowel(char ch){
	if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y')
		return true;
	else return false;
}

// returns true if token is (. ? !)
bool isEndOfSentence(string s){
	if(s[0] == '.' || s[0] == '?' || s[0] == '!') return true;
	else return false;
}

// constants for the formula
const double c0 = -15.59, c1 =0.39 , c2 =11.8 ;
//returns difficalty double
double calculateDifficulty(stats ans){
	double result = c0 + c1 * ((double) ans.words / ans.sentences) +c2 * ((double) ans.syllables / ans.words);
	return result;
}
 
//prints result
void printResult(stats ans){
	cout<< "Words: " << ans.words << endl;
	cout<< "Syllables: " << ans.syllables << endl;
	cout<< "Sentences: " << ans.sentences << endl;
	cout<< "Grade level: " << ans.difficulty << endl;
}