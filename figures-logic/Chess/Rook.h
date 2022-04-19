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
    if ( Check(vert, hor) && )
    {
        horizontal = hor;
        vertical = vert;
        didMove = true;
        return 1;
    }
    return 0;
}
bool Rook::cut_down(Piece& f)
{
    return false;
}
