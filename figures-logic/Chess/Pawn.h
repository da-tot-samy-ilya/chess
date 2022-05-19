#pragma once
#include "ChessFigure.h"

class Pawn : public Piece
{
private:
    TypePiece type_piece = PAWN;
public:
    Pawn(Colour col, int vert, int hor, TypePiece type, int move) : Piece(col, vert, hor, type, move) {};
    Pawn(Pawn& f) : Piece(f.colour, f.vertical, f.horizontal, f.type_piece, f.moveCount) {};
};
