#include "CheckingForMove.h"
bool Knight::move(int vert, int hor, char col)
{
    if (col == 'n' && Check(vert, hor) && MovingKnight(vert, hor, vertical, horizontal))
    {
        board->PieceMoving(vert, hor, vertical, horizontal);
        horizontal = hor;
        vertical = vert;
        return true;
    }
    return false;
}
bool Knight::cut_down(Piece& f)
{
    if (colour != f.GetColour() && MovingKnight(f.GetVert(), f.GetHor(), vertical, horizontal))
    {
        int newHor = f.GetHor();
        int newVert = f.GetVert();
        board->PieceMoving(f.GetVert(), f.GetHor(), vertical, horizontal);
        horizontal = newHor;
        vertical = newVert;
        return true;
    }
    return false;
}