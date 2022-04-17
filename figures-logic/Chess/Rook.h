#pragma once
#include "ChessFigure.h"
#include "Pawn.h"

class Rook : public Piece
{
<<<<<<< HEAD
public: 
    Rook(bool col, int vert, int hor) : Piece(col, vert, hor) {};
||||||| a5ec6b7
public:
    Rook(bool col, int vert, int hor) : Piece(col, vert, hor) {};
=======
public:
    Rook(char col, int vert, int hor) : Piece(col, vert, hor) {};
>>>>>>> fd5c32c0c228a44f6c22ad2cbed549f412af9969
    Rook(Rook& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    int move(int vert, int hor) override;
    int cut_down(Piece& f) override;
    bool getFirstMove() { return didMove };
};

int Rook::move(int vert, int hor)
{
    if ((Check(vert, hor))&&(((vert = vertical) && (hor != horizontal)) || ((vert != vertical) && (hor == horizontal))))
    {
        horizontal = hor;
        vertical = vert;
        return 1;
    }
    return 0;
}
int Rook::cut_down(Piece& f)
{

}