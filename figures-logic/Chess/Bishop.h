#pragma once
#include "ChessFigure.h"

class Bishop : public Piece
{

public:
    Bishop(char col, int vert, int hor) : Piece(col, vert, hor) {};
    Bishop(Bishop& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    bool move(int vert, int hor) override;
    bool cut_down(Piece& f) override;
    /*Bishop operator=(Piece& p)
    {
        colour = p.colour;
        vertical = p.vertical;
        horizontal = 
    }*/
};

bool Bishop::move(int vert, int hor)
{
    if ( Check(vert, hor) && MovingBishop(vert, hor, vertical, horizontal))
    {
        horizontal = hor;
        vertical = vert;
        return 1;
    }
    return 0;
}
bool Bishop::cut_down(Piece& f)
{
    
}