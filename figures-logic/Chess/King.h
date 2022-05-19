#pragma once
#include "ChessFigure.h"

class King : public Piece
{
private:
    TypePiece type_piece = KING;
    bool haveCheck = false;
public:
    King(Colour col, int vert, int hor, TypePiece type, int move) : Piece(col, vert, hor, type, move) {};
    King(King& f) : Piece(f.colour, f.vertical, f.horizontal, f.type_piece, f.moveCount) {};
};