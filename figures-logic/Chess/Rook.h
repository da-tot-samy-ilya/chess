#pragma once
#include "ChessFigure.h"

class Rook : public Piece
{
private:
    TypePiece type_piece = ROOK;
public:
    Rook(Colour col, int vert, int hor, TypePiece type) : Piece(col, vert, hor, type) {};
    Rook(Rook& f) : Piece(f.colour, f.vertical, f.horizontal, f.type_piece) {};
    /*bool move(int vert, int hor, char col) override;
    bool cut_down(Piece& f) override;*/
};
