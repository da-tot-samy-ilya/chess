#include "CheckingForMove.h"
bool Bishop::move(int vert, int hor, char col)
{
    PossibleMoves.clear();
    MakeVectorForRook(PossibleMoves, vertical, horizontal, colour);
    if (col == 'n' && Check(vert, hor) && CanMakeMove(PossibleMoves, canMove, make_pair(hor, vert)))
    {
        board->PieceMoving(vert, hor, vertical, horizontal);
        horizontal = hor;
        vertical = vert;
        return true;
    }
    return false;
}
bool Bishop::cut_down(Piece& f)
{
    int vsign = 1;
    int hsign = 1;
    if (f.GetVert() < vertical) vsign = -1;
    if (f.GetHor() < horizontal) hsign = -1;
    //PossibleMoves.clear();
    MakeVectorForRook(PossibleMoves, vertical, horizontal, colour);
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