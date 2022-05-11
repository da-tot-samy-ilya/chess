#pragma once
#include "ChessFigure.h"

class King : public Piece
{
private:
    TypePiece type_piece = KING;
    bool didMove = false;
    bool haveCheck = false;
public:
    King(Colour col, int vert, int hor, TypePiece type) : Piece(col, vert, hor, type) {};
    King(King& f) : Piece(f.colour, f.vertical, f.horizontal, f.type_piece) {};
    /*bool move(int vert, int hor, char col) override;
    bool cut_down(Piece& f) override;*/
    bool* getFirstMove() override { return  &(this->didMove); };
};