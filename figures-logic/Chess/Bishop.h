#pragma once
#include "ChessFigure.h"

class Bishop : public Piece
{

public:
    Bishop(char col, int vert, int hor) : Piece(col, vert, hor) {};
    Bishop(Bishop& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    int move(int vert, int hor) override;
    int cut_down(Piece& f) override;
};

int Bishop::move(int vert, int hor)
{
    if ((Check(vert, hor))&&(abs((vert - vertical) == abs(hor - horizontal)) && (vert != vertical)))
    {
        horizontal = hor;
        vertical = vert;
        return 1;
    }
    return 0;
}
int Bishop::cut_down(Piece& f)
{
    
}