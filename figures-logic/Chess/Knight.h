#pragma once
#include "ChessFigure.h"

class Knight : public Piece
{
private:
    TypePiece type_piece = KNIGHT;
public:
    Knight(Colour col, int vert, int hor) : Piece(col, vert, hor) {};
    Knight(Knight& f) : Piece(f.colour, f.vertical, f.horizontal) {};
   /* bool move(int vert, int hor, char col) override;
    bool cut_down(Piece& f) override;*/
    bool getFirstMove() override { return false; };
};