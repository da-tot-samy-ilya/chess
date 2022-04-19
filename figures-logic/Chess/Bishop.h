#pragma once
#include "ChessFigure.h"

class Bishop : public Piece
{
private:
    TypePiece type_piece = BISHOP;
public:
    Bishop(char col, int vert, int hor) : Piece(col, vert, hor) {};
    Bishop(Bishop& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    bool move(int vert, int hor, char col) override;
    bool cut_down(Piece& f) override;
};

bool Bishop::move(int vert, int hor, char col)
{
    if (col == 'n' && Check(vert, hor) && MovingBishop(vert, hor, vertical, horizontal) && PiecesAlongTheWayForBishop(vert, hor, vertical, horizontal))
    {
        PieceMoving(vert, hor, vertical, horizontal);
        horizontal = hor; // 1, 2
        vertical = vert;
        return true;
    }
    return false;
}
bool Bishop::cut_down(Piece& f)
{
    if ( colour != f.GetColour() && MovingBishop(f.GetVert(), f.GetHor(), vertical, horizontal) && PiecesAlongTheWayForBishop(f.GetVert(), f.GetHor(), vertical, horizontal))// 0 1
    {
        PieceMoving(f.GetVert(), f.GetHor(), vertical, horizontal);
        horizontal = f.GetHor();
        vertical = f.GetVert();
        return true;
    }
    return false;
}