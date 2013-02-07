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
		bool solved = sudoku.solvePuzzle(); // brute force search algorithm
		if(solved){
			std::cout << "\n\n Solution:\n";
			printPuzzle(sudoku);
		} else std::cout << "\n\n The given puzzle has no solution.\n";
	}
	while(again()); // again prompts the user
	
	return 0;
}