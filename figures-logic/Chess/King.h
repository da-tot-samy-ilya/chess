#pragma once
#include "ChessFigure.h"

class King : public Piece
{
private:
    TypePiece type_piece = KING;
    bool haveCheck = false;
public:
    King(Colour col, int vert, int hor, TypePiece type) : Piece(col, vert, hor, type) {};
    King(King& f) : Piece(f.colour, f.vertical, f.horizontal, f.type_piece) {};
};