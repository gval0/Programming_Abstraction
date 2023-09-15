/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "foreach.h"
#include "random.h"
#include "set.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
void makeBoard(Grid<char>& letterGrid);
string shuffleCubes(Vector<string>& cubesVector);
void displayLetters(Grid<char>& letterGrid, string& letters);
void humanPlays(Grid<char>& letterGrid, Set<string>& foundWords, Lexicon& lex);
bool possibleToGet(Grid<char>& letterGrid, string word);
bool helper(Grid<char>& letterGrid, Grid<bool>& boolGrid, string word, int x, int y);
void computerPlays(Grid<char>& letterGrid, Set<string>& foundWords, Lexicon& lex);
void computerHelper(Grid<char>& letterGrid, Set<string>& foundWords, Lexicon& lex, Grid<bool>& boolGrid, string word, int x, int y);




/* Main program */

int main() {

	GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
	initGBoggle(gw);
	welcome();
	giveInstructions();

	while(true){
		Grid<char> letterGrid(4,4);
		makeBoard(letterGrid);

		Set<string> foundWords;
		Lexicon lex("EnglishWords.dat");
		humanPlays(letterGrid,foundWords, lex);
		computerPlays(letterGrid, foundWords, lex);

		if(getLine("If you dont want to continue press Enter: ") == "") break;
	}
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

/* choose letters, display them */
void makeBoard(Grid<char>& letterGrid){
	drawBoard(4,4);

	cout << "Do you want to force the board configuration? ";
	cout << "If so type yes... ";
	string boardLetters = "";
	if(toLowerCase(getLine()) == "yes"){
		cout << endl;
		cout << "Enter a 16-character string to identify which letters you want on the cubes. ";
		cout << "The first 4 letters are the cubes on the top row from left to right, ";
		cout << "the next 4 letters are the second row, and so on." << endl;
		while(true){
			boardLetters = getLine("Enter the string: ");
			if(boardLetters.size() >= 16) break;
			cout << "String must include 16 characters!" << endl;
		}
		boardLetters = boardLetters.substr(0,16);
	} else {
		Vector<string> cubesVector;
		foreach (string s in STANDARD_CUBES) cubesVector.add(s);
		boardLetters = shuffleCubes(cubesVector);
	}
	boardLetters = toUpperCase(boardLetters);
	displayLetters(letterGrid, boardLetters);
}

/* randomize letters */
string shuffleCubes(Vector<string>& cubesVector){
	int curIndex;
	for (int i = 0; i < cubesVector.size(); i++){
		curIndex = randomInteger(i, cubesVector.size() - 1);
		string tempStr = cubesVector[curIndex];
		cubesVector[curIndex] = cubesVector[i];
		cubesVector[i] = tempStr;
	}

	string result = "";
	for (int i = 0; i < cubesVector.size(); i++){
		curIndex = randomInteger(0, 5);
		result += cubesVector[i][curIndex];

	}
	return result;
}

/* display letter */
void displayLetters(Grid<char>& letterGrid, string& letters){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
		labelCube(i, j, letters[i*4+j]);
		letterGrid[i][j] = letters[i*4+j];
		}
	}
}

/* human is playing */
void humanPlays(Grid<char>& letterGrid, Set<string>& foundWords, Lexicon& lex){
	cout << "Ok, take all the time you want and find all the words you can! ";
	cout << "Signal that you're finished by entering an empty line." << endl;

	
	string curWord = "";
	while (true){
		curWord = getLine("Enter a word: ");
		curWord = toUpperCase(curWord);
		if(curWord == "") break;
		if(curWord.size() < 4) 
			cout << "That word doesn't meet the minimum word length." << endl;
		else if(!lex.contains(curWord)) 
			cout << "That's not a word!" << endl;
		else if(foundWords.contains(curWord)) 
			cout << "You've already guessed that!" << endl;
		else if(possibleToGet(letterGrid, curWord)){
				foundWords.add(curWord);
				recordWordForPlayer(curWord, HUMAN);
		} else cout << "You can't make that word!" << endl;
	}
}

/* checks if possible to get the word, highlight letters */
bool possibleToGet(Grid<char>& letterGrid, string word){
	Grid<bool> boolGrid(4,4);
	for(int i = 0; i < letterGrid.nRows; i++){
		for(int j = 0; j < letterGrid.nCols; j++){
			if(letterGrid[i][j] == word[0]){
				boolGrid[i][j] = true;
				if(helper(letterGrid, boolGrid, word.substr(1), i, j)){
					highlightCube(i, j, true);
					pause(150);
					highlightCube(i, j, false);
					return true;
				}
				boolGrid[i][j] = false;
			}
		}
	}
}

/* helper function */
bool helper(Grid<char>& letterGrid, Grid<bool>& boolGrid, string word, int x, int y){
	if(word.size() == 0) return true;
	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			if(letterGrid.inBounds(x + i, y + j) && !boolGrid[x + i][y + j] && letterGrid[x+i][y+j] == word[0]) {
				boolGrid[x + i][y + j] = true;
				if(helper(letterGrid, boolGrid, word.substr(1), x+i, y+j)){
					highlightCube(x+i, y+j, true);
					pause(150);
					highlightCube(x+i, y+j, false);
					return true;
				}
			}
		}
	}
}

/* finds all remaining words */
void computerPlays(Grid<char>& letterGrid, Set<string>& foundWords, Lexicon& lex){
	for(int i = 0; i < letterGrid.nRows; i++){
		for(int j = 0; j < letterGrid.nCols; j++){
			string curWord = string() + letterGrid[i][j];
			Grid<bool> boolGrid(4,4);
			boolGrid[i][j] = true;
			computerHelper(letterGrid, foundWords, lex, boolGrid, curWord, i, j);
			boolGrid[i][j] = false;
		}
	}
}

/* helper function */
void computerHelper(Grid<char>& letterGrid, Set<string>& foundWords, Lexicon& lex, Grid<bool>& boolGrid, string word, int x, int y){
	if(!lex.containsPrefix(word)) {
	} else {
		if(word.size() >= 4) {
			if(lex.contains(word) && !foundWords.contains(word)){
				recordWordForPlayer(word, COMPUTER);
				foundWords.add(word);
			}
		}
		for(int i = -1; i < 2; i++){
			for(int j = -1; j < 2; j++){
				if(letterGrid.inBounds(x + i, y + j) && !boolGrid[x + i][y + j]){
					word += letterGrid[x + i][y + j];
					boolGrid[x + i][y + j] = true;
					computerHelper(letterGrid, foundWords, lex, boolGrid, word, x+i, y+j);
					word = word.substr(0, word.size() - 1);
					boolGrid[x + i][y + j] = false;
				}
			}
		}
	}
}