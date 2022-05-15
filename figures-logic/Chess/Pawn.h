#pragma once
#include "ChessFigure.h"

class Pawn : public Piece
{
private:
    TypePiece type_piece = PAWN;
public:
    Pawn(Colour col, int vert, int hor, TypePiece type) : Piece(col, vert, hor, type) {};
    Pawn(Pawn& f) : Piece(f.colour, f.vertical, f.horizontal, f.type_piece) {};
};
