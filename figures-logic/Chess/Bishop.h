#pragma once
#include "ChessFigure.h"

class Bishop : public Piece
{
private:
    TypePiece type_piece = BISHOP;
public:
    Bishop(Colour col, int vert, int hor, TypePiece type, int move) : Piece(col, vert, hor, type, move) {};
    Bishop(Bishop& f) : Piece(f.colour, f.vertical, f.horizontal, f.type_piece, f.moveCount) {};
};