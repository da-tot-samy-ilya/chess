#pragma once
#include "ChessFigure.h"
#include "Board.h"

class Rook : public Piece
{
private:
   TypePiece type_piece = ROOK;
   bool didMove = false;
public:
   Rook(char col, int vert, int hor) : Piece(col, vert, hor) {};
   Rook(Rook& f) : Piece(f.colour, f.vertical, f.horizontal) {};
   bool move(int vert, int hor, char col) override;
   bool cut_down(Piece& f) override;
   bool getFirstMove() { return didMove; };
};

bool Rook::move(int vert, int hor, char col)
{
   if (col == 'n' && Check(vert, hor) && MovingRook(vert, hor, vertical, horizontal) && PiecesAlongTheWayForRook(vert, hor, vertical, horizontal))
   {
       PieceMoving(vert, hor, vertical, horizontal);
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
       PieceMoving(f.GetVert(), f.GetHor(), vertical, horizontal);
       horizontal = newHor;
       vertical = newVert;
       return true;
   }
   return false;
}
