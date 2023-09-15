/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "strlib.h"
#include "simpio.h"
#include "queue.h"
#include "lexicon.h"
#include "vector.h"
using namespace std;

/* Function prototype */
Vector<string> buildLadder(string& a, string& b, Lexicon& l);
void sameNumberOfLetters(Lexicon& l, int n, Lexicon& lex);
Lexicon wordsDiffByOneLetter(string s, Lexicon& l);
void printResult(Vector<string>& vec);

/* constants */
const string sentinel = "";
const string lexiconName = "EnglishWords.dat";

/*
main function
interact with user
displays path
*/
int main() {
	Lexicon englishWords(lexiconName);
    while(true){
		string startWord = getLine("Enter the staring word (or nothong to quit): ");
		if(startWord == sentinel) break;
		string endWord = getLine("Enter the ending word: ");
		cout << "Searching ..." << endl;
		
		
		printResult(buildLadder(startWord,endWord,englishWords));
		cout << endl;
	}
	cout << "Goodbye!" << endl;

    return 0;
}

/*
returns vector with possible path
in case of no path returns empty vector
*/
Vector<string> buildLadder(string& startWord, string& endWord, Lexicon& englishWords){

	if(startWord.length() != endWord.length()){
		Vector<string> v;
		return v;
	}
	
	Queue<Vector<string> > ladderQueue;
	Vector<string> vec;
	vec.add(startWord);
	ladderQueue.enqueue(vec); 

	Lexicon usedWords;
	usedWords.add(startWord);

	while(!ladderQueue.isEmpty()){
		Vector<string> curVector = ladderQueue.dequeue();
		if(curVector.get(curVector.size() - 1) == endWord) return curVector;
		foreach(string curWord in wordsDiffByOneLetter(curVector.get(curVector.size() - 1), englishWords)){
			if(!usedWords.contains(curWord)){ 
				Vector<string> tempVector =  curVector;
				tempVector.add(curWord);
				usedWords.add(curWord);
				ladderQueue.enqueue(tempVector);
			}
		}
	}

	Vector<string> v;
	return v;
}

/*
returns words in english that differs by one letters
*/
Lexicon wordsDiffByOneLetter(string lastWord, Lexicon& englishWords){
	Lexicon oneLetterDiff; 
	for (int i = 0; i < lastWord.length(); i++){
		for(int j = 0; j < 'z' - 'a' + 1; j++){
			string tempstr = lastWord;
			tempstr[i] = 'a' + j;
			if(englishWords.contains(tempstr)&& lastWord != tempstr) oneLetterDiff.add(tempstr);
		}
	}
	return oneLetterDiff;
}

/*
displays word ladder
*/
void printResult(Vector<string>& wordLadder){
	if(wordLadder.isEmpty()) 
		cout << "No word ladder found" <<  endl;
	else{
		cout << "Ladder found: ";
	for(int i = 0; i < wordLadder.size()-1; i++){
		cout<< wordLadder.get(i);
		cout << " -> ";
	}
	cout << wordLadder.get(wordLadder.size()-1) << endl;
	}
	 
}