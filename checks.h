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

bool premovecheck(string&, string, string[8][8]); // checks to make sure the player selected a legal piece to move.
bool postmovecheck(string&, string, string[8][8]);// check to make sure the player isn't telling their piece to occupy a square they already have a piece on.
bool check(string[8][8], int, int, int, int, string); // takes in which piece type it is and the inputed move, returns bool value of that move passed in the right rules check
bool rookcheck(string[8][8], int, int, int, int); //checks to see if proposed rook move is legal or not
bool bishopcheck(string[8][8], int, int, int, int); // checks to see if proposed bishop move is legal or not
bool knightcheck(string[8][8], int, int, int, int); // checks if knight move is legal or illegal
bool queencheck(string[8][8], int, int, int, int); // checks if proposed queen move is legal
bool kingcheck(string[8][8], int, int, int, int); // checks if proposed queen move is legal
bool pawncheck(string[8][8], int, int, int, int, string); // checks if proposed pawn move is legal
bool oppoent(string[8][8], int, int, string); // checks if post row and pre row contains oppoents piece
bool inputcheck(string); // checks if input is legal input
bool okletter(string); // checks in input letter is legal 
bool checkpromote(string, string); //checks if promotion is legal
bool passantcheck(string[8][8], int, int); // checks if passant is legal#pragma once.
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


bool premovecheck(string& move, string turn, string board[8][8])
{
	int row, column;
	string test;
	getcoordnates(move, row, column);
	test = board[row][column];
	if (turn[0] == test[0])
		return true;
	else
		return false;
}

bool postmovecheck(string& move, string turn, string board[8][8])
{
	int row, column;
	string test;
	getcoordnates(move, row, column);
	test = board[row][column];
	if (turn[0] == test[0])
		return false;
	else
		return true;
}

bool check(string board[8][8], int prerow, int postrow, int precolumn, int postcolumn, string turn)
{
	switch (filter(board, prerow, precolumn))
	{
	case'R':
		return rookcheck(board, prerow, postrow, precolumn, postcolumn);
	case 'B':
		return bishopcheck(board, prerow, postrow, precolumn, postcolumn);
	case 'N':
		return knightcheck(board, prerow, postrow, precolumn, postcolumn);
	case 'Q':
		return queencheck(board, prerow, postrow, precolumn, postcolumn);
	case 'K':
		return kingcheck(board, prerow, postrow, precolumn, postcolumn);
	case 'P':
		return pawncheck(board, prerow, postrow, precolumn, postcolumn, turn);
	default:
		return false;

	}
}
bool rookcheck(string board[8][8], int prerow, int postrow, int precolumn, int postcolumn)
{
	int count = 0;
	if (prerow == postrow)
	{
		if (precolumn < postcolumn)
		{
			for (int i = postcolumn - precolumn - 1; i > 0; i--)
			{
				count++;
				if (board[prerow][precolumn + i] == " ")
					count--;
			}
			if (count == 0)
				return true;
			else
				return false;
		}
		else//(precolumn > postcolumn)
		{
			for (int i = precolumn - postcolumn - 1; i > 0; i--)
			{
				count++;
				if (board[prerow][precolumn - i] == " ")
					count--;
			}
			if (count == 0)
				return true;
			else
				return false;
		}
	}
	else if (precolumn == postcolumn)
	{
		if (prerow < postrow)
		{
			for (int i = postrow - prerow - 1; i > 0; i--)
			{
				count++;
				if (board[prerow + i][precolumn] == " ")
					count--;
			}
			if (count == 0)
				return true;
			else
				return false;
		}
		else //(prerow > precolumn)
		{
			for (int i = prerow - postrow - 1; i > 0; i--)
			{
				count++;
				if (board[prerow - i][precolumn] == " ")
					count--;
			}
			if (count == 0)
				return true;
			else
				return false;
		}
	}
	else
	{
		return false;
	}
}

bool knightcheck(string board[8][8], int prerow, int postrow, int precolumn, int postcolumn)
{
	int changeinrow = postrow - prerow, changeincolumn = postcolumn - precolumn;
	if (changeinrow == 2 && changeincolumn == 1)
		return true;
	if (changeinrow == 1 && changeincolumn == 2)
		return true;
	if (changeinrow == -1 && changeincolumn == 2)
		return true;
	if (changeinrow == -2 && changeincolumn == 1)
		return true;
	if (changeinrow == -2 && changeincolumn == -1)
		return true;
	if (changeinrow == -2 && changeincolumn == -1)
		return true;
	if (changeinrow == 1 && changeincolumn == -2)
		return true;
	if (changeinrow == 2 && changeincolumn == -1)
		return true;
	else
		return false;
}

bool bishopcheck(string board[8][8], int prerow, int postrow, int precolumn, int postcolumn)
{
	int changeinrow = postrow - prerow, changeincolumn = postcolumn - precolumn, magrow = numbermag(changeinrow), magcolumn = numbermag(changeincolumn);
	if (magrow == magcolumn)
	{
		int count = 0;
		if (changeinrow > 0 && changeincolumn > 0)
			for (int i = magrow - 1; i > 0; i--)
			{
				count++;
				if (board[prerow + i][precolumn + i] == " ")
					count--;
			}
		if (changeinrow < 0 && changeincolumn > 0)
			for (int i = magrow - 1; i > 0; i--)
			{
				count++;
				if (board[prerow - i][precolumn + i] == " ")
					count--;
			}
		if (changeinrow > 0 && changeincolumn < 0)
			for (int i = magrow - 1; i > 0; i--)
			{
				count++;
				if (board[prerow + i][precolumn - i] == " ")
					count--;
			}
		if (changeinrow < 0 && changeincolumn < 0)
			for (int i = magrow - 1; i > 0; i--)
			{
				count++;
				if (board[prerow - i][precolumn - i] == " ")
					count--;
			}
		if (count == 0)
			return true;
		else
			return false;
	}
	return false;
}

bool queencheck(string board[8][8], int prerow, int postrow, int precolumn, int postcolumn)
{
	if (rookcheck(board, prerow, postrow, precolumn, postcolumn) || bishopcheck(board, prerow, postrow, precolumn, postcolumn))
		return true;
	else
		return false;
}

bool kingcheck(string board[8][8], int prerow, int postrow, int precolumn, int postcolumn)
{
	int changeinrow = postrow - prerow, changeincolumn = postcolumn - precolumn, magrow = numbermag(changeinrow), magcolumn = numbermag(changeincolumn);
	if (queencheck(board, prerow, postrow, precolumn, postcolumn) && magrow <= 1 && magcolumn <= 1)
		return true;
	else
		return false;
}

bool pawncheck(string board[8][8], int prerow, int postrow, int precolumn, int postcolumn, string turn)
{
	int changeinrow = postrow - prerow, changeincolumn = postcolumn - precolumn, magcolumn = numbermag(changeincolumn);
	if (turn == "W")
	{
		if (precolumn == postcolumn && postrow == prerow - 1 && board[postrow][postcolumn] == " ")
		{
			promote(board, prerow, postrow, precolumn, postcolumn, turn);
			return true;
		}
		if ((precolumn == postcolumn && prerow == 6 && board[postrow][postcolumn] == " " && board[prerow - 1][precolumn] == " ") && postrow == 4)
		{
			board[prerow - 1][precolumn] = "  ";
			return true;
		}
		if (postrow == prerow - 1 && magcolumn == 1 && oppoent(board, postrow, postcolumn, turn))
		{
			promote(board, prerow, postrow, precolumn, postcolumn, turn);
			return true;
		}
		if ((precolumn == postcolumn + 1 || precolumn == postcolumn - 1) && prerow == 3 && board[prerow][postcolumn] == "BP" && passantcheck(board, postrow, postcolumn))
		{
			board[prerow][postcolumn] = "  ";
			return true;
		}
		else
			return false;
	}
	else
	{
		if (precolumn == postcolumn && postrow == prerow + 1 && board[postrow][postcolumn] == " ")
		{
			promote(board, prerow, postrow, precolumn, postcolumn, turn);
			return true;
		}
		if ((precolumn == postcolumn && prerow == 1 && board[postrow][postcolumn] == " " && board[prerow + 1][precolumn] == " ") && postrow == 3)
		{
			board[prerow + 1][precolumn] = "  ";
			return true;
		}
		if (postrow == prerow + 1 && magcolumn == 1 && oppoent(board, postrow, postcolumn, turn))
		{
			promote(board, prerow, postrow, precolumn, postcolumn, turn);
			return true;
		}
		if ((precolumn == postcolumn + 1 || precolumn == postcolumn - 1) && prerow == 4 && board[prerow][postcolumn] == "WP" && passantcheck(board, postrow, postcolumn))
		{
			board[prerow][postcolumn] = "  ";
			return true;
		}
		else
			return false;
	}
}
bool oppoent(string board[8][8], int postrow, int postcolumn, string turn)
{
	if (turn == "W")
	{
		if (board[postrow][postcolumn][0] == 'B')
			return true;
		else
			return false;
	}
	else
	{
		if (board[postrow][postcolumn][0] == 'W')
			return true;
		else
			return false;
	}
}

bool inputcheck(string input)
{
	if (input.length() == 2 && isdigit(input[1]) && input[1] != '0' && input[1] != '9' && okletter(input))
		return false;
	else
		return true;
}

bool okletter(string input)
{
	char x = input[0];
	switch (x)
	{
	case 'A':
	case 'a':
		return true;
		break;
	case 'B':
	case 'b':
		return true;
		break;
	case'C':
	case 'c':
		return true;
		break;
	case 'D':
	case 'd':
		return true;
		break;
	case 'E':
	case 'e':
		return true;
		break;
	case'F':
	case 'f':
		return true;
		break;
	case 'G':
	case 'g':
		return true;
		break;
	case 'H':
	case 'h':
		return true;
		break;
	default:
		return false;
	}
}

bool checkpromote(string upgrade, string turn)
{
	if (turn == "W")
	{
		if (upgrade.length() == 2 && upgrade[0] == 'W' && (upgrade[1] == 'P' || upgrade[1] == 'R' || upgrade[1] == 'N' || upgrade[1] == 'B' || upgrade[1] == 'Q' || upgrade[1] == 'K'))
			return true;
		else
			return false;
	}
	else
	{
		if (upgrade.length() == 2 && upgrade[0] == 'B' && (upgrade[1] == 'P' || upgrade[1] == 'R' || upgrade[1] == 'N' || upgrade[1] == 'B' || upgrade[1] == 'Q' || upgrade[1] == 'K'))
			return true;
		else
			return false;
	}
}

bool passantcheck(string board[8][8], int postrow, int postcolumn)
{
	if (board[postrow][postcolumn] == "  ")
		return true;
	else
		return false;
}
