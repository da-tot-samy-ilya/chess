#pragma once
#include "ChessFigure.h"

class Knight : public Piece
{
private:
    TypePiece type_piece = KNIGHT;
public:
    Knight(Colour col, int vert, int hor, TypePiece type) : Piece(col, vert, hor, type) {};
    Knight(Knight& f) : Piece(f.colour, f.vertical, f.horizontal, f.type_piece) {};
   /* bool move(int vert, int hor, char col) override;
    bool cut_down(Piece& f) override;*/
    bool* getFirstMove() override { return false; };
};