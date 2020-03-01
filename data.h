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

void getpremove(string&); // prompts a player to select the piece they wish to move.
void getpostmove(string&); // prompts a player to select the place they wish to move their piece.
int rowtransform(int);// , string[8][8], string, string); // takes the first coordnate point for a square and translates it from the chess board row number to the 2D array row coordnate.
int columntransform(char);//, string[8][8], string, string); // takes the second coordnate point for a square and translates it from the chess board column letter to the 2D array column coordnate.
void getcoordnates(string, int&, int&);// , string[8][8], string, string); // uses the row and column transform fuctions to collect the coordnates required for a move.
void changeturn(string&, string[8][8]); // changes who's turn it is, either white to black or black to white.
char filter(string[8][8], int, int); // turns piece string identy to a char value.
int numbermag(int); // takes in a number and returns its magnitude or absolute value of that number
void promote(string[8][8], int, int, int, int, string); //if checkpromote passes true bool value, promotes pawn
void clearwhitespassant(string[8][8]); // deletes whites ability for en passant
void clearblackspassant(string[8][8]); // deltes blacks ability for en passant#pragma once

void getpremove(string& premove)
{
	cout << " Enter piece to move: ";
	cin >> premove;
	if (inputcheck(premove))
	{
		cout << " THAT IS NOT A VALID PIECE TO MOVE." << endl;
		getpremove(premove);
	}
}

int rowtransform(int x)
{
	switch (x)
	{
	case 1:
		return 7;
	case 2:
		return 6;
	case 3:
		return 5;
	case 4:
		return 4;
	case 5:
		return 3;
	case 6:
		return 2;
	case 7:
		return 1;
	case 8:
		return 0;
	default:
		cout << " CONGRATS, NOT SURE HOW YOU DID IT BUT YOU MANAGED TO CRASH THE GAME." << endl;
		exit(1);
	}
}

int columntransform(char x)
{
	int a = 9;
	switch (x)
	{
	case 'A':
	case 'a':
		a = 0;
		break;
	case 'B':
	case 'b':
		a = 1;
		break;
	case'C':
	case 'c':
		a = 2;
		break;
	case 'D':
	case 'd':
		a = 3;
		break;
	case 'E':
	case 'e':
		a = 4;
		break;
	case'F':
	case 'f':
		return 5;
		break;
	case 'G':
	case 'g':
		a = 6;
		break;
	case 'H':
	case 'h':
		a = 7;
		break;
	default:
		cout << " CONGRATS, NOT SURE HOW YOU DID IT BUT YOU MANAGED TO CRASH THE GAME." << endl;
		exit(1);
	}
	return a;
}

void getcoordnates(string move, int& row, int& column)
{
	string srow = move.substr(1, 1), test;
	row = rowtransform(stoi(srow));
	column = columntransform(move[0]);
}

void getpostmove(string& postmove)
{
	cout << " Enter where you want to move your piece: ";
	cin >> postmove;
	if (inputcheck(postmove))
	{
		cout << " THAT IS NOT A VALID PLACE TO MOVE." << endl;
		getpostmove(postmove);
	}
}

void changeturn(string& turn, string board[8][8])
{
	if (turn == "W")
	{
		turn = "B";
		clearwhitespassant(board);
	}
	else
	{
		turn = "W";
		clearblackspassant(board);
	}
}

char filter(string board[8][8], int prerow, int precolumn)
{
	string check = board[prerow][precolumn].substr(1, 1);
	if (check == "P")
		return 'P';
	else if (check == "R")
		return 'R';
	else if (check == "N")
		return 'N';
	else if (check == "B")
		return 'B';
	else if (check == "Q")
		return 'Q';
	else if (check == "K")
		return 'K';
	else
		return 'a';
}

int numbermag(int num)
{
	if (num > 0)
		return num;
	else
		return -1 * num;
}

void promote(string board[8][8], int prerow, int postrow, int precolumn, int postcolumn, string turn) // not working
{
	string upgrade;
	if (turn == "W")
	{
		if (postrow == 0)
		{
			cout << " Congrats on the promotion! Enter 'WQ' for queen, 'WR' for rook, 'WN' for knight, or 'WB' for bishop: ";
			cin >> upgrade;
			if (checkpromote(upgrade, turn))
			{
				board[prerow][precolumn] = upgrade;
			}
			else
			{
				cout << " NOT VALID INPUT, TRY AGAIN." << endl;
				promote(board, prerow, postrow, precolumn, postcolumn, turn);
			}

		}
	}
	else
	{
		if (postrow == 7)
		{
			cout << " Congrats on the promotion! Enter 'BQ' for queen, 'BR' for rook, 'BN' for knight, or 'BB' for bishop: ";
			cin >> upgrade;
			if (checkpromote(upgrade, turn))
			{
				board[prerow][precolumn] = upgrade;
			}
			else
			{
				cout << " NOT VALID INPUT, TRY AGAIN." << endl;
				promote(board, prerow, postrow, precolumn, postcolumn, turn);
			}
			checkpromote(upgrade, turn);
			board[prerow][precolumn] = upgrade;
		}
	}
}

void clearblackspassant(string board[8][8])
{
	for (int i = 0; i < 8; i++)
		if (board[5][i] == "  ")
			board[5][i] = " ";
}

void clearwhitespassant(string board[8][8])
{
	for (int i = 0; i < 8; i++)
		if (board[2][i] == "  ")
			board[2][i] = " ";
}