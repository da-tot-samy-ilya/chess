#pragma once
#include "ChessFigure.h"

class Knight : public Piece
{
public:
    Knight(bool col, int vert, int hor) : Piece(col, vert, hor) {};
    Knight(Knight& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    bool move(int vert, int hor) override;
    bool cut_down(Piece& f) override;
};

bool Knight::move(int vert, int hor)
{
    if (vertical + 2 == vert && horizontal + 1 == hor || vertical + 1 == vert && horizontal + 2 == hor ||
        vertical - 1 == vert && horizontal + 2 == hor || vertical - 2 == vert && horizontal + 1 == hor ||
        vertical - 2 == vert && horizontal - 1 == hor || vertical - 1 == vert && horizontal - 2 == hor ||
        vertical + 1 == vert && horizontal - 2 == hor || vertical + 2 == vert && horizontal - 1 == hor)
    {
        horizontal = hor;
        vertical = vert;
        return 1;
    }
    return 0;
}
bool Knight::cut_down(Piece& f)
{
    
}