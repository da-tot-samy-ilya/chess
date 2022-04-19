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
	if (col == 'n' && Check(vert, hor) && MovingQueen(vert, hor, vertical, horizontal) && PiecesAlongTheWayForQueen(vert, hor, vertical, horizontal))
	{
		PieceMoving(vert, hor, vertical, horizontal);
		horizontal = hor;
		vertical = vert;
		return true;
	}
	return false;
}
bool Queen::cut_down(Piece& f)
{
	int vsign = 1;
	int hsign = 1;
	if (f.GetVert() < vertical) vsign = -1;
	if (f.GetVert() == vertical) vsign = 0;
	if (f.GetHor() < horizontal) hsign = -1;
	if (f.GetHor() == horizontal) hsign = 0;
	if (colour != f.GetColour() && MovingBishop(f.GetVert(), f.GetHor(), vertical, horizontal) && PiecesAlongTheWayForBishop(f.GetVert() - vsign, f.GetHor() - hsign, vertical, horizontal))
	{
		int newHor = f.GetHor();
		int newVert = f.GetVert();
		PieceMoving(f.GetVert(), f.GetHor(), vertical, horizontal);
		horizontal = newHor;
		vertical = newVert;
		return true;
	}
	return false;
}