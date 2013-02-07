#ifndef _PUZZLELOGIC_H_
#define _PUZZLELOGIC_H_

// The imput given by the user is stored in the grid as positive integers of
// the given value. As the program tries different combinations, the attempted
// "solutions" will be stored as negative integers.
// Eg. 2 = the ogirinal puzzle tile contains 2
//    -2 = the original puzzle tile is blank and the program is trying to find
//         a solution with '2' placed in the specific tile
class Puzzle{
private:
	int grid[9][9];
public:
	Puzzle();
	int getTile(int i, int j);
	void setTile(int i, int j, int val);
	bool tryTile(int i, int j, int val);
	bool checkRow(int i, int j, int val);
	bool checkColumn(int i, int j, int val);
	bool checkSquare(int i, int j, int val);
	bool solvePuzzle(void);
	void resetTile(int i, int j);
};

#endif