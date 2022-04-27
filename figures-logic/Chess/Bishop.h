//#pragma once
//#include "ChessFigure.h"
//
//class Bishop : public Piece
//{
//private:
//    TypePiece type_piece = BISHOP;
//public:
//    Bishop(char col, int vert, int hor) : Piece(col, vert, hor) {};
//    Bishop(Bishop& f) : Piece(f.colour, f.vertical, f.horizontal) {};
//    bool move(int vert, int hor, char col) override;
//    bool cut_down(Piece& f) override;
//};
//
//bool Bishop::move(int vert, int hor, char col)
//{
//    if (col == 'n' && Check(vert, hor) && MovingBishop(vert, hor, vertical, horizontal) && PiecesAlongTheWayForBishop(vert, hor, vertical, horizontal))
//    {
//        board->PieceMoving(vert, hor, vertical, horizontal);
//        horizontal = hor;
//        vertical = vert;
//        return true;
//    }
//    return false;
//}
//bool Bishop::cut_down(Piece& f)
//{
//    int vsign = 1;
//    int hsign = 1;
//    if (f.GetVert() < vertical) vsign = -1;
//    if (f.GetHor() < horizontal) hsign = -1;
//    if (colour != f.GetColour() && MovingBishop(f.GetVert(), f.GetHor(), vertical, horizontal) && PiecesAlongTheWayForBishop(f.GetVert() - vsign, f.GetHor() - hsign, vertical, horizontal))
//    {
//        int newHor = f.GetHor();
//        int newVert = f.GetVert();
//        board->PieceMoving(f.GetVert(), f.GetHor(), vertical, horizontal);
//        horizontal = newHor;
//        vertical = newVert;
//        return true;
//    }
//    return false;
//}