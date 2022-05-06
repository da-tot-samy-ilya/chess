#pragma once
#include "ChessFigure.h"

class Bishop : public Piece
{
private:
    TypePiece type_piece = BISHOP;
public:
    Bishop(Colour col, int vert, int hor, TypePiece type) : Piece(col, vert, hor, type) {};
    Bishop(Bishop& f) : Piece(f.colour, f.vertical, f.horizontal, f.type_piece) {};
    /*bool move(int vert, int hor, char col) override;
    bool cut_down(Piece& f) override;*/
    bool* getFirstMove() override { return false; };
};