#pragma once
#include "ChessFigure.h"
#include "Board.h"

class King : public Piece
{
private:
    TypePiece type_piece = KING;
private:
    bool didMove = false;
    bool haveCheck = false;
public:
    King(char col, int vert, int hor) : Piece(col, vert, hor) {};
    King(King& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    bool move(int vert, int hor, char col) override;
    bool cut_down(Piece& f) override;
    bool getFirstMove() { return didMove; };
};

bool King::move(int vert, int hor, char col)
{
    if (Check(vert, hor))
    {
        horizontal = hor;
        vertical = vert;
        didMove = true;
        return true;
    }
}
bool King::cut_down(Piece& f)
{
    
}