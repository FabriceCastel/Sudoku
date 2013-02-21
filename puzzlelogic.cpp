#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include "puzzlelogic.h"
#include "interface.h"


using std::cout;

// Puzzle constructor, initializes the grid to 0 in all tiles
Puzzle::Puzzle(){
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			grid[i][j] = 0;
		} // for
	} // for
}



// checks if the given puzzle has any conflicting tiles
bool Puzzle::checkValid(){
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){

			// if there's a tile conflict
			if(getTile(i, j) != 0 &&
				(!checkRow(i, j, getTile(i, j)) ||
				!checkColumn(i, j, getTile(i, j)) ||
				!checkSquare(i, j, getTile(i, j)))){
				return false;
			}
		}
	}
	return true;
}


// Basic getter.
int Puzzle::getTile(int i, int j){
	return grid[i][j];
}



// Tests for valid tile input, stores given value in given tile address
void Puzzle::setTile(int i, int j, int val){
	assert(val < 10 && val >= 0);
	grid[i][j] = val;
}



// Checks if the given number occurs somewhere else in the same row. If it does, the function outputs false
// and if the number is unique, the output is true.
bool Puzzle::checkRow(int i, int j, int val){
	for(int a = 0; a < 9; a++){
		if((grid[a][j] == val && a != i) || (grid[a][j] == (val * -1) && a != i)) return false;
	}
	return true;
}



// Does the same as checkRow but with columns.
bool Puzzle::checkColumn(int i, int j, int val){
	for(int a = 0; a < 9; a++){
		if((grid[i][a] == val && a != j) || (grid[i][a] == (val * -1) && a != j)) return false;
	}
	return true;
}



// Checks to see if the same value is contained somewhere within the 3x3 suqare in which the tile is located
// returns false iff the number is already present in the 3x3 square.
bool Puzzle::checkSquare(int i, int j, int val){
	for(int a = 0; a < 3; a++){
		for(int b = 0; b < 3; b++){

			// starts checking at the top left corner of the 3x3 square, incementing 'a' moves down one tile
			// and incrementing 'b' moves one tile right until all tiles have been checked
			if(((grid[i - i%3 + a][j - j%3 + b] == val) ||
				(grid[i - i%3 + a][j - j%3 + b] == val * -1)) &&
				i - i%3 + a != i &&
				j - j%3 + b != j){
				return false;
			}
		}
	}
	return true;
}



// resets the tile to its original value
void Puzzle::resetTile(int i, int j){
	if(grid[i][j] < 0){
		grid[i][j] = 0;
	}
}



// If the tile value is legal, output true & store the value in the wanted tile (with a '-' sign).
// If the tile is fixed (given by user), output true and leave tile untouched.
bool Puzzle::tryTile(int i, int j, int val){

	// check that the tile isn't a fixed value
	if(grid[i][j] <= 0){
		if(checkRow(i, j, val) && checkColumn(i, j, val) && checkSquare(i, j, val)){
			int tempval = -1 * val;
			grid[i][j] = tempval;
			return true;
		} else{ 
			grid[i][j] = 0;
			return false;
		}
	}
	return true;
}



// Brute force solves the sudoku, outputs true iff a solution is found
bool Puzzle::solvePuzzle(void){
	int rowTracker = 0; // keeps track of position in row
	int columnTracker = 0; // keeps track of position in column
	int firsti = 0;
	int firstj = 0; // firsti and firstj keep track of the first empty tile
	bool forward = true; // true iff we moved forward one step in the grid


	// look for the first blank tile
	while(grid[firsti][firstj] != 0){
		if(firsti < 8) firsti++;
		else{
			firsti = 0;
			firstj++;
			if(firstj > 8){
				cout << "\n\nERROR:The grid is already full, there is nothing to solve.\n\n";
				exit(1);
			}
		}
	}

	rowTracker = firsti;
	columnTracker = firstj;

	// while loop ends when all possibilities have been exhausted
	// because of the short-circuiting behaviour of the '||' operator, the row position will only be checked
	// when the rows are equal for firstj & columnTracker
	while(columnTracker > firstj || (columnTracker == firstj && rowTracker >= firsti)){
		// debug code
		// cout << " Solving tile: (" << rowTracker + 1 << ", " << columnTracker + 1 << ") " << grid[rowTracker][columnTracker] << " -> ";
		// printPuzzle(*this);
		/*for(int w = 0; w != 9; w++){
			for(int v = 0; v != 9; v++){
				cout << abs(grid[v][w]) << " ";
			}
		}
		cout << "\n";
		*/


		// denotes the tile holding a non-mutable value
		bool fixedtile = false;
		if(grid[rowTracker][columnTracker] > 0) fixedtile = true;

		int tempval;

		//// If we took a step forward, start tempval at 1 and if we went back, pick up where we left off
		// if(forward) tempval = 1;
		/* else */ tempval = abs(grid[rowTracker][columnTracker]) + 1;
		
		// will be changed to true iff we find a valid candidate for the tile
		bool success = false;

		// Increment and try to insert tempval in the tile until a value fits or all have failed
		while(!fixedtile && !success && tempval < 10){
			success = tryTile(rowTracker, columnTracker, tempval);
			tempval++;
		}

		// if a candidate was found, move forward. If the tile was fixed, keep going in the
		// same direction you were previously moving (ie. skip over the fixed tiles)
		if(!fixedtile) forward = success;

		// debug code
		// cout << grid[rowTracker][columnTracker] << "\n";

		// increment/decrement trackers accordingly
		if(forward){
			if(rowTracker >= 8){

				// if at the last tile and moving forward, the puzzle is solved
				if(columnTracker >= 8) return true;
				
				// Increment trackers
				rowTracker = 0;
				columnTracker++;
			} else rowTracker++;
		} else{
			
			// as you backtrack, set the attempted tile to 0 (unless it was fixed, in which case
			// the resetTile method leaves the tile untouched)
			resetTile(rowTracker, columnTracker);

			// backtrack
			if(rowTracker <= 0){
				rowTracker = 8;
				columnTracker--;
			} else{
				rowTracker--;
			}
		}

	}
	// In the event that the trackers get decrememted past the first blank tile, it means that
	// every combination has been attempted and failed, thus the 
	return false;
}