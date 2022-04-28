#include "CheckingForMove.h"
bool King::move(int vert, int hor, char col)
{
    if (col == 'n' && Check(vert, hor) && MovingKing(vert, hor, vertical, horizontal) && PiecesAlongTheWayForKing(vert, hor, vertical, horizontal) && HasCheck(vertical, horizontal, colour))
    {
        board->PieceMoving(vert, hor, vertical, horizontal);
        horizontal = hor;
        vertical = vert;
        didMove = true;
        return true;
    }
}
bool King::cut_down(Piece& f)
{
    if (colour != f.GetColour() && MovingKing(f.GetVert(), f.GetHor(), vertical, horizontal) && PiecesAlongTheWayForKing(f.GetVert(), f.GetHor(), vertical, horizontal))
    {
        int newHor = f.GetHor();
        int newVert = f.GetVert();
        board->PieceMoving(f.GetVert(), f.GetHor(), vertical, horizontal);
        horizontal = newHor;
        vertical = newVert;
        return true;
    }
}