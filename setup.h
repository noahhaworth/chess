#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "display.h"
#include "setup.h"
#include "data.h"
#include "checks.h"

using namespace std;

void makeboard(string[8][8]); //this function creates a 8 X 8 string array and sets every value to " ".
void setup(string[8][8]); // this function sets up the chess pieces in their starting position.
void makeandsetupboard(string[8][8]); // combines the setupboard and setupboard into one function.

									  //functions in this group are all used in the all important "showboard" function.

void row(); // this function creates the horizontal boarders of the board you view on the screen with a bunch of "_" symbols.
void showrow(int&); // this function outputs the numbers on the right side of board.
void showletters(); // this function outputs the letter below the board.

void makeandsetupboard(string board[8][8])
{
	makeboard(board);
	setup(board);
}

void makeboard(string board[8][8])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board[i][j] = " ";
}

void setup(string board[8][8])
{
	for (int i = 0; i < 8; i++)
		board[6][i] = "WP";
	for (int i = 0; i < 8; i++)
		board[1][i] = "BP";
	board[0][0] = "BR";
	board[0][1] = "BN";
	board[0][2] = "BB";
	board[0][3] = "BQ";
	board[0][4] = "BK";
	board[0][5] = "BB";
	board[0][6] = "BN";
	board[0][7] = "BR";
	board[7][0] = "WR";
	board[7][1] = "WN";
	board[7][2] = "WB";
	board[7][3] = "WQ";
	board[7][4] = "WK";
	board[7][5] = "WB";
	board[7][6] = "WN";
	board[7][7] = "WR";
}

void row()
{
	for (int i = 0; i < 67; i++)
		cout << "_";
	cout << endl;
}

void showrow(int& x)
{
	cout << x << " ";
	x--;
}

void showletters()
{
	cout << "	A	B	C	D	E	F	G	H" << endl;
}