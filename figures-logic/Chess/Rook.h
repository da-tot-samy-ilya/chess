#pragma once
#include "ChessFigure.h"

class Rook : public Piece
{
public: 
    Rook(bool col, int vert, int hor) : Piece(col, vert, hor) {};
    Rook(Rook& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    int move(int vert, int hor) override;
    int cut_down(Piece& f) override;
    bool getFirstMove() { return didMove };
};

int Rook::move(int vert, int hor)
{
    if (((vert = vertical) && (hor != horizontal)) || ((vert != vertical) && (hor == horizontal)))
    {
        horizontal = hor;
        vertical = vert;
        return 1;
    }
    return 0;
}
int Rook::cut_down(Piece& f)
{

}