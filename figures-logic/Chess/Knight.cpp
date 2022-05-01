#include "CheckingForMove.h"
bool Knight::move(int vert, int hor, char col)
{
    PossibleMoves.clear();
    FindPossibleMovesForKnight(PossibleMoves, vertical, horizontal, colour);
    if (col == 'n' && Check(vert, hor) && CanMakeMove(PossibleMoves, canMove, make_pair(hor, vert)))
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
    if (colour != f.GetColour() && CanMakeMove(PossibleMoves, canMove, make_pair(f.GetHor(), f.GetVert())))
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