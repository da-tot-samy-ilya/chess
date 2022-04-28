#pragma once
#include "ChessFigure.h"

class Knight : public Piece
{
private:
    TypePiece type_piece = KNIGHT;
public:
    Knight(bool col, int vert, int hor) : Piece(col, vert, hor) {};
    Knight(Knight& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    bool move(int vert, int hor, char col) override;
    bool cut_down(Piece& f) override;
    bool getFirstMove() override { return false; };
};

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