//#pragma once
//#include "ChessFigure.h"
//#include "Rook.h"
//#include "Bishop.h"
//#include "Queen.h"
//#include "Knight.h"
//#include "Board.h"
//
//class Pawn : public Piece
//{
//private:
//    TypePiece type_piece = PAWN;
//private:
//    bool didMove = false;
//public:
//    Pawn(char col, int vert, int hor) : Piece(col, vert, hor) {};
//    Pawn(Pawn& f) : Piece(f.colour, f.vertical, f.horizontal) {};
//    bool move(int vert, int hor, char col) override;
//    bool cut_down(Piece& f) override;
//};
//
//bool Pawn::move(int vert, int hor, char col)
//{
//    if (col == 'n' && Check(vert, hor) && MovingPawn(vert, hor, vertical, horizontal, didMove) && PiecesAlongTheWayForPawn(vert, hor, vertical, horizontal))
//    {
//        PieceMoving(vert, hor, vertical, horizontal);
//        vertical = vert;
//        didMove = true;
//        return true;
//        if (horizontal == 7 || horizontal == 0)
//        {
//            TypePiece type;
//            square[horizontal][vertical].SetPiece(colour, horizontal, vertical, type);
//            //переопределение пешки
//        }
//    }
//    return 0;
//}
//bool Pawn::cut_down(Piece& f)
//{
//    if (f.GetHor() < horizontal) return false;
//    if (colour != f.GetColour() && MovingPawn(f.GetVert(), f.GetHor(), vertical, horizontal, didMove))
//    {
//        int newHor = f.GetHor();
//        int newVert = f.GetVert();
//        PieceMoving(f.GetVert(), f.GetHor(), vertical, horizontal);
//        horizontal = newHor;
//        vertical = newVert;
//        return true;
//        //взятие на проходе
//    }
//    return false;
//   
//}
