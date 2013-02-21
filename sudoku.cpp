#include <iostream>
#include "interface.h"
#include "puzzlelogic.h"

int main(void){
	
	printTitle(); // prints the title screen
	
	do
	{
		Puzzle sudoku = Puzzle(); // init new sudoku
		getPuzzle(sudoku); // get sudoku from user input
		std::cout << "\n\n Incomplete sudoku puzzle:\n";
		printPuzzle(sudoku);
		bool valid = sudoku.checkValid(); // check if the input is valid
		

		if(valid){
			bool solved = sudoku.solvePuzzle(); // brute force search algorithm
			if(solved){
				std::cout << "\n\n Solution:\n";
				printPuzzle(sudoku);
			} else std::cout << "\n The given puzzle has no solution.\n\n";
		} else {
			std::cout << "\n The given puzzle is invalid.\n\n";
		}
	}
	while(again()); // again prompts the user to continue
	
	return 0;
}