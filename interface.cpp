#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include "interface.h"
#include "puzzlelogic.h"

using std::cout;
using std::cin;

// Prints the program title
void printTitle(void){
	cout << "\n\n *****************************************************************\n"
		 << " *                  BRUTE FORCE SUDOKU SOLVER                    *\n"
		 << " *                      by Fabrice Castel                        *\n"
		 << " *                         V 1.0 - 2013                          *\n"
		 << " *****************************************************************\n\n"
		 << " NOTE: This is an early build which will not terminate given an unsolvable grid.\n\n";
}


// Prompts the user for a yes/no response, returns true iff user inputs 'y'
// regardless of the rest of the input
bool again(void){
	printf(" Solve another puzzle? (y/n) ");
	char ans;
	cin >> ans;
	cin.clear();

	if(ans == 'y' || ans == 'Y'){
		cout << "\n\n";
		return true;
	} else{
		cout << "\n";
		return false;
	}
}


// Prompts user & reads sudoku state from stdin
void getPuzzle(Puzzle& sudoku){

	cout << " Please enter the incomplete sudoku one row after the other, separating digits with a space and marking blank tiles as 0.\n\n";
	
	for(int j = 0; j < 9; j++){
		cout << " Row #" << j + 1 << " - ";
		for(int i = 0; i < 9; i++){
			int val = 0;
			cin >> val;

			// check for input validity
			if(0 > val || val > 9){
				cout << "\n\nERROR: Invalid argument. All tiles must have a value ranging from 0 to 9.\n\n";
				exit(1);
			}

			sudoku.setTile(i, j, val);
		}
	}
}



// Prints the given puzzle
void printPuzzle(Puzzle sudoku){
	for(int i = 0; i < 9; i++){
		if(i%3 == 0){
			cout << "\n";
		}
		for(int j = 0; j < 9; j++){
			// debug code
			// cout << " " << sudoku.getTile(j, i);
			cout << " " << abs(sudoku.getTile(j, i));
			if(j%3 == 2) cout << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}
