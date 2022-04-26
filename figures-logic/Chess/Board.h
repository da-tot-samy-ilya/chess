#pragma once
#include "ChessFigure.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"

enum TypePiece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
//  a b c d e f g h - vertical
//0 - hor
//1
//2
//3
//4
//5
//6
//7

class Board
{ // Piece
public:
	Piece* square[8][8];
	void SetBoard(); // èçíà÷àëüíîå ïîëîæåíèå äîñêè
	void SetPiece(char colour, int hor, int vert, TypePiece type); // ïîñòàâèòü ôèãóðó, ëèáî óäàëèòü å¸, åñëè Empty
	void PieceMoving(int vEnd, int hEnd, int vStart, int hStart);
	void SetSquare();
};

void SetSquare(int hor, int vert)
{

}

void Board::SetPiece(char colour, int hor, int vert, TypePiece type)
{
	switch (type)
	{
	case (KING):
		square[hor][vert] = new King(colour, vert, hor);
	case (QUEEN):
		square[hor][vert] = new Queen(colour, vert, hor);
	case(BISHOP):
		square[hor][vert] = new Bishop(colour, vert, hor);
	case(KNIGHT):
		square[hor][vert] = new Knight(colour, vert, hor);
	case(ROOK):
		square[hor][vert] = new Rook(colour, vert, hor);
	case(PAWN):
		square[hor][vert] = new Pawn(colour, vert, hor);
	case (EMPTY):
		square[hor][vert] = new Piece('n', vert, hor);
	}
}

void Board::PieceMoving(int vEnd, int hEnd, int vStart, int hStart)
{
	square[hEnd][vEnd] = square[hStart][vStart];
	SetPiece('n', hStart, vStart, EMPTY);
}

void Board::SetBoard()
{
	for (int i = 0; i < 8; i++)
	{
		char colour = 'n';
		if (i < 2) colour = 'w';
		if (i > 5) colour = 'b';
		if (i == 0 || i == 7)
		{

			square[i][0] = new Rook(colour, 0, i);
			square[i][1] = new Knight(colour, 1, i);
			square[i][2] = new Bishop(colour, 2, i);
			square[i][3] = new Queen(colour, 3, i);
			square[i][4] = new King(colour, 4, i);
			square[i][5] = new Bishop(colour, 5, i);
			square[i][6] = new Knight(colour, 6, i);
			square[i][7] = new Rook(colour, 7, i);
		}
		else
		{
			for (int j = 0; j < 8; j++)
				if (i > 1 || i < 6)
					square[i][j] = new Piece(colour, j, i);
				else
					square[i][j] = new Pawn(colour, j, i);
		}
	}
	/*int counter = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (counter == 0)
			{
				square[i][j]->setSquareColor(black);
				counter = 1;
			}
			else
				counter = 0;
		}*/
}
Board* CreateBoard()
{
	Board board;
	return &board;
}