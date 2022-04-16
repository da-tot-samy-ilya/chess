#pragma once
#pragma once
#include "ChessFigure.h"

class King : public Piece
{
public:
    King(bool col, int vert, int hor) : Piece(col, vert, hor) {};
    King(King& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    int move(int vert, int hor) override;
    int cut_down(Piece& f) override;
};

int King::move(int vert, int hor)
{
    if (vertical + 1 == vert && horizontal == hor || vertical == vert && horizontal + 1 == hor ||
        vertical - 1 == vert && horizontal == hor || vertical == vert && horizontal - 1 == hor ||
        vertical + 1 == vert && horizontal + 1 == hor || vertical + 1 == vert && horizontal - 1 == hor ||
        vertical - 1 == vert && horizontal + 1 == hor || vertical - 1 == vert && horizontal - 1 == hor)
    {
        horizontal = hor;
        vertical = vert;
        return 1;
    }
    return 0;
}
int King::cut_down(Piece& f)
{
    
}