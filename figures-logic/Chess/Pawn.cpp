#include "CheckingForMove.h"
bool Pawn::move(int vert, int hor, char col)
{
    PossibleMoves.clear();
    FindPossibleMovesForPawn(PossibleMoves, vertical, horizontal, colour, didMove);
    if (col == 'n' && Check(vert, hor) && CanMakeMove(PossibleMoves, canMove, make_pair(hor, vert)))
    {
        board->PieceMoving(vert, hor, vertical, horizontal);
        vertical = vert;
        didMove = true;
        return true;
        //переопределение пешки
        if (horizontal == 7 || horizontal == 0)
        {
            TypePiece type;
            board->SetPiece(colour, horizontal, vertical, type);
        }
    }
    return 0;
}
bool Pawn::cut_down(Piece& f)
{
    if (f.GetHor() < horizontal) return false;
    if (colour != f.GetColour() && CanMakeMove(PossibleMoves, canMove, make_pair(f.GetHor(), f.GetVert())))
    {
        int newHor = f.GetHor();
        int newVert = f.GetVert();
        board->PieceMoving(f.GetVert(), f.GetHor(), vertical, horizontal);
        horizontal = newHor;
        vertical = newVert;
        return true;
        //взятие на проходе
    }
    return false;

}