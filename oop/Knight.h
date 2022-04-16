#pragma once
#include "ChessPiece.h"

class Knight : public Piece
{
public:
    Knight(bool col, int vert, int hor) : Piece(col, vert, hor) {};
    Knight(Knight& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    int move(int vert, int hor) override;
    int cut_down(Piece& f) override;
};

int Knight::move(int vert, int hor)
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
int Knight::cut_down(Piece& f)
{
    
}