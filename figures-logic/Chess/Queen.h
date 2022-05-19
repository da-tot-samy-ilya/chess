#pragma once
#include "ChessFigure.h"

class Queen : public Piece
{
private:
	TypePiece type_piece = QUEEN;
public:
	Queen(Colour col, int vert, int hor, TypePiece type, int move) : Piece(col, vert, hor, type, move) {};
	Queen(Queen& f) : Piece(f.colour, f.vertical, f.horizontal, f.type_piece, f.moveCount) {};
};
