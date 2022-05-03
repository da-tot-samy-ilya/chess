#pragma once
#include "ChessFigure.h"

class Rook : public Piece
{
private:
    TypePiece type_piece = ROOK;
    bool didMove = false;
public:
    Rook(Colour col, int vert, int hor) : Piece(col, vert, hor) {};
    Rook(Rook& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    /*bool move(int vert, int hor, char col) override;
    bool cut_down(Piece& f) override;*/
    bool getFirstMove() { return didMove; };
};
