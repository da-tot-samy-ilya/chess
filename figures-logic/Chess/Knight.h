#pragma once
#include "ChessFigure.h"

class Knight : public Piece
{
private:
    TypePiece type_piece = KNIGHT;
public:
    Knight(Colour col, int vert, int hor, TypePiece type) : Piece(col, vert, hor, type) {};
    Knight(Knight& f) : Piece(f.colour, f.vertical, f.horizontal, f.type_piece) {};
};