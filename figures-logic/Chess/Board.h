#pragma once
#include "Square.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"

//enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };

class Board
{
public:
	Square square[8][8];
	void SetBoard();
};

void Board::SetBoard()
{
	square[0][0].setPieceAndColor(Rook r1('w', 0, 0), 'w');
	square[1][0].setPieceAndColor(Knight kn1('w', 1, 0), 'w');
	square[2][0].setPieceAndColor(Bishop b1('w', 2, 0), 'w');
	square[3][0].setPieceAndColor(Queen q1('w', 3, 0), 'w');
	square[4][0].setPieceAndColor(King k1('w', 4, 0), 'w');
	square[5][0].setPieceAndColor(Bishop b2('w', 5, 0), 'w');
	square[6][0].setPieceAndColor(Knight kn2('w', 6, 0), 'w');
	square[7][0].setPieceAndColor(Rook r2('w', 7, 0), 'w');

	square[0][7].setPieceAndColor(Rook r3('b', 0, 7), 'b');
	square[1][7].setPieceAndColor(Knight kn3('b', 1, 7), 'b');
	square[2][7].setPieceAndColor(Bishop b3('b', 2, 7), 'b');
	square[3][7].setPieceAndColor(Queen q2('b', 3, 7), 'b');
	square[4][7].setPieceAndColor(King k2('b', 4, 7), 'b');
	square[5][7].setPieceAndColor(Bishop b4('b', 5, 7), 'b');
	square[6][7].setPieceAndColor(Knight kn4('b', 6, 7), 'b');
	square[7][7].setPieceAndColor(Rook r4('b', 7, 7), 'b');

	square[0][1].setPieceAndColor(Pawn p11('w', 0, 1), 'w');
	square[1][1].setPieceAndColor(Pawn p12('w', 1, 1), 'w');
	square[2][1].setPieceAndColor(Pawn p13('w', 2, 1), 'w');
	square[3][1].setPieceAndColor(Pawn p14('w', 3, 1), 'w');
	square[4][1].setPieceAndColor(Pawn p15('w', 4, 1), 'w');
	square[5][1].setPieceAndColor(Pawn p16('w', 5, 1), 'w');
	square[6][1].setPieceAndColor(Pawn p17('w', 6, 1), 'w');
	square[7][1].setPieceAndColor(Pawn p18('w', 7, 1), 'w');

	square[0][6].setPieceAndColor(Pawn p21('b', 0, 6), 'b');
	square[1][6].setPieceAndColor(Pawn p22('b', 1, 6), 'b');
	square[2][6].setPieceAndColor(Pawn p23('b', 2, 6), 'b');
	square[3][6].setPieceAndColor(Pawn p24('b', 3, 6), 'b');
	square[4][6].setPieceAndColor(Pawn p25('b', 4, 6), 'b');
	square[5][6].setPieceAndColor(Pawn p26('b', 5, 6), 'b');
	square[6][6].setPieceAndColor(Pawn p27('b', 6, 6), 'b');
	square[7][6].setPieceAndColor(Pawn p28('b', 7, 6), 'b');

	for (int i = 2; i < 6; i++)
		for (int j = 0; j < 8; j++)
			square[j][i].setPieceAndColor(EMPTY, 'n');

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