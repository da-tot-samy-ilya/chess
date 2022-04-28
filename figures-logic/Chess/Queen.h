#pragma once
#include "ChessFigure.h"

class Queen : public Piece
{
private:
	TypePiece type_piece = QUEEN;
public:
	Queen(char col, int vert, int hor) : Piece(col, vert, hor) {};
	Queen(Queen& f) : Piece(f.colour, f.vertical, f.horizontal) {};
	bool move(int vert, int hor, char col) override;
	bool cut_down(Piece& f) override;
	bool getFirstMove() override { return false; };
};
