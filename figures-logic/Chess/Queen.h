#pragma once
#include "ChessFigure.h"
#include "Board.h"

class Queen : public Piece
{
private:
	TypePiece type_piece = QUEEN;
public:
	Queen(char col, int vert, int hor) : Piece(col, vert, hor) {};
	Queen(Queen& f) : Piece(f.colour, f.vertical, f.horizontal) {};
	bool move(int vert, int hor, char col) override;
	bool cut_down(Piece& f) override;
};


bool Queen::move(int vert, int hor, char col)
{
	if (Check(vert, hor) && ())
	{
		horizontal = hor;
		vertical = vert;
		return 1;
	}
	return 0;
}
bool Queen::cut_down(Piece& f)
{
	return 1;
}