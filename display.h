#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include "display.h"
#include "setup.h"
#include "data.h"
#include "checks.h"

using namespace std;

void move(string[8][8], int, int, int, int); // moves one piece to another, doubles as the capture function.
void whosturn(string); // prints out who's turn it is on the board (white/black).
void showboard(string[8][8]); // this function outputs the board onto the screen with all the pieces in their current location.
void play(string[8][8], string&, string&); // this function calls all the other functions necessary to a signle player turn. it is like the mother of all functions (excluding main of course).

void showboard(string board[8][8])
{
	int x = 8;
	for (int i = 0; i < 8; i++)
	{
		showrow(x);
		row();
		for (int j = 0; j < 8; j++)
			cout << "   |" << setw(4) << board[i][j];
		cout << "   |" << endl;
		for (int k = 0; k < 9; k++)
			cout << "   |    ";
		cout << endl;
	}
	cout << "  ";
	row();
	showletters();
}


void play(string board[8][8], string& stat, string& turn)
{
	int prerow, precolumn, postrow, postcolumn;
	string premove, postmove;
	showboard(board);
	whosturn(turn);
	getpremove(premove);
	getpostmove(postmove);
	getcoordnates(premove, prerow, precolumn);
	getcoordnates(postmove, postrow, postcolumn);
	if (premovecheck(premove, turn, board) && postmovecheck(postmove, turn, board) && check(board, prerow, postrow, precolumn, postcolumn, turn))
	{
		move(board, prerow, precolumn, postrow, postcolumn);
		cout << " Enter 'checkmate' if you've won or anything else to end your turn." << endl;
		cin >> stat;
		changeturn(turn, board);
	}
	else
	{
		cout << " THAT IS AN ILLEGAL MOVE, PLEASE TRY AGAIN." << endl;
		play(board, stat, turn);
	}

}

void move(string board[8][8], int prerow, int precolumn, int postrow, int postcolumn)
{
	board[postrow][postcolumn] = board[prerow][precolumn];
	board[prerow][precolumn] = " ";
}

void whosturn(string turn)
{
	if (turn == "W")
		cout << " It is White's turn." << endl;
	else
		cout << " It is Black's turn." << endl;
}