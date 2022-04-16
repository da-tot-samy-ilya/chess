#pragma once
#include "Square.h"
#include "Rook.h"

//enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };

class Board
{
public:
	Square square[8][8];
	void SetBoard();
};

void Board::SetBoard()
{
	square[0][0].setPieceAndColor(ROOK, 0);
	square[1][0].setPieceAndColor(KNIGHT, 0);
	square[2][0].setPieceAndColor(BISHOP, 0);
	square[3][0].setPieceAndColor(QUEEN, 0);
	square[4][0].setPieceAndColor(KING, 0);
	square[5][0].setPieceAndColor(BISHOP, 0);
	square[6][0].setPieceAndColor(KNIGHT, 0);
	square[7][0].setPieceAndColor(ROOK, 0);

	square[0][7].setPieceAndColor(ROOK, 1);
	square[1][7].setPieceAndColor(KNIGHT, 1);
	square[2][7].setPieceAndColor(BISHOP, 1);
	square[3][7].setPieceAndColor(QUEEN, 1);
	square[4][7].setPieceAndColor(KING, 1);
	square[5][7].setPieceAndColor(BISHOP, 1);
	square[6][7].setPieceAndColor(KNIGHT, 1);
	square[7][7].setPieceAndColor(ROOK, 1);

	for (int i = 0; i < 8; i++)
	{
		square[i][1].setPieceAndColor(PAWN, 0);
		square[i][6].setPieceAndColor(PAWN, 1);

	}
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			square[j][i].setPieceAndColor(EMPTY, 'n');

	}
	int counter = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (counter == 0)
			{
				square[i][j].setSquareColor(black);
				counter = 1;
			}
			else
				counter = 0;
		}
}