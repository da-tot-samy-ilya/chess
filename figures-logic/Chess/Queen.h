#pragma once
#include "ChessFigure.h"

class Queen : public Piece
{
public:
	Queen(char col, int vert, int hor) : Piece(col, vert, hor) {};
	Queen(Queen& f) : Piece(f.colour, f.vertical, f.horizontal) {};
	bool move(int vert, int hor) override;
	bool cut_down(Piece& f) override;
};


bool Queen::move(int vert, int hor)
{
	if ((Check(vert, hor))&& ((((vert = vertical) && (hor != horizontal)) || ((vert != vertical) && (hor == horizontal))) ||
		(abs((vert - vertical) == abs(hor - horizontal)) && (vert != vertical))))
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