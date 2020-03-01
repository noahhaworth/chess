#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "display.h" //includes all functions for putting display out onto the board
#include "setup.h" //includes all functions for seting up the board, happens before game play
#include "data.h" // includes all functions that collect and interpret information
#include "checks.h" // includes all functions that represent rules and checks to make sure inputted moves are legal

using namespace std;

int main()
{
	string board[8][8], stat("ok"), turn("W");
	makeandsetupboard(board);
	do { play(board, stat, turn); } while (stat != "checkmate");
	return 0;
}