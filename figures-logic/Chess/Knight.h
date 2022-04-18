#pragma once
#include "ChessFigure.h"
#include "Board.h"

class Knight : public Piece
{
private:
    TypePiece type_piece = KNIGHT;
public:
    Knight(bool col, int vert, int hor) : Piece(col, vert, hor) {};
    Knight(Knight& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    bool move(int vert, int hor, char col) override;
    bool cut_down(Piece& f) override;
};

bool Knight::move(int vert, int hor, char col)
{
    if ()
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