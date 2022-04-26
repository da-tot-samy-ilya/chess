//#pragma once
//#include "ChessFigure.h"
//#include "Board.h"
//
//class King : public Piece
//{
//private:
//    TypePiece type_piece = KING;
//private:
//    bool didMove = false;
//    bool haveCheck = false;
//public:
//    King(char col, int vert, int hor) : Piece(col, vert, hor) {};
//    King(King& f) : Piece(f.colour, f.vertical, f.horizontal) {};
//    bool move(int vert, int hor, char col) override;
//    bool cut_down(Piece& f) override;
//    bool getFirstMove() { return didMove; };
//};
//
//bool King::move(int vert, int hor, char col)
//{
//    if (col == 'n'  && Check(vert, hor) && MovingKing(vert, hor, vertical, horizontal) && PiecesAlongTheWayForKing(vert, hor, vertical, horizontal) && HasCheck(vertical, horizontal, colour))
//    {
//        PieceMoving(vert, hor, vertical, horizontal);
//        horizontal = hor;
//        vertical = vert;
//        didMove = true;
//        return true;
//    }
//}
//bool King::cut_down(Piece& f)
//{
//    if (colour != f.GetColour() && MovingKing(f.GetVert(), f.GetHor(), vertical, horizontal) && PiecesAlongTheWayForKing(f.GetVert(), f.GetHor(), vertical, horizontal))
//    {
//        int newHor = f.GetHor();
//        int newVert = f.GetVert();
//        PieceMoving(f.GetVert(), f.GetHor(), vertical, horizontal);
//        horizontal = newHor;
//        vertical = newVert;
//        return true;
//    }
//}