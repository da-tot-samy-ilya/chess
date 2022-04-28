#include "CheckingForMove.h"
bool Rook::move(int vert, int hor, char col)
{
    if (canMove && col == 'n' && Check(vert, hor) && MovingRook(vert, hor, vertical, horizontal) && PiecesAlongTheWayForRook(vert, hor, vertical, horizontal))
    {
        board->PieceMoving(vert, hor, vertical, horizontal);
        horizontal = hor;
        vertical = vert;
        return true;
    }
    return false;
}
bool Rook::cut_down(Piece& f)
{
    int vsign = 1;
    int hsign = 1;
    if (f.GetVert() < vertical) vsign = -1;
    if (f.GetVert() == vertical) vsign = 0;
    if (f.GetHor() < horizontal) hsign = -1;
    if (f.GetHor() == horizontal) hsign = 0;
    if (colour != f.GetColour() && MovingRook(f.GetVert(), f.GetHor(), vertical, horizontal) && PiecesAlongTheWayForRook(f.GetVert() - vsign, f.GetHor() - hsign, vertical, horizontal))
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