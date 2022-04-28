#include "CheckingForMove.h"
bool Pawn::move(int vert, int hor, char col)
{
    if (col == 'n' && Check(vert, hor) && MovingPawn(vert, hor, vertical, horizontal, didMove) && PiecesAlongTheWayForPawn(vert, hor, vertical, horizontal))
    {
        board->PieceMoving(vert, hor, vertical, horizontal);
        vertical = vert;
        didMove = true;
        return true;
        if (horizontal == 7 || horizontal == 0)
        {
            TypePiece type;
            board->SetPiece(colour, horizontal, vertical, type);/*->square[horizontal][vertical]*/
            //переопределение пешки
        }
    }
    return 0;
}
bool Pawn::cut_down(Piece& f)
{
    if (f.GetHor() < horizontal) return false;
    if (colour != f.GetColour() && MovingPawn(f.GetVert(), f.GetHor(), vertical, horizontal, didMove))
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