#pragma once
#include "ChessFigure.h"

class Pawn : public Piece
{
private:
    TypePiece type_piece = PAWN;
private:
    bool didMove = false;
public:
    Pawn(char col, int vert, int hor) : Piece(col, vert, hor) {};
    Pawn(Pawn& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    bool move(int vert, int hor, char col) override;
    bool cut_down(Piece& f) override;
    bool getFirstMove() override { return didMove; };
};
