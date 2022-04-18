#pragma once
#include "ChessFigure.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Board.h"

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
};

bool Pawn::move(int vert, int hor, char col)
{
    if (Check(vert, hor) && )
    {
        vertical = vert;
        didMove = true;
        if (vert == 7 || vert == 0)
        {

        }
    }
    return 0;
}
bool Pawn::cut_down(Piece& f)
{
    //������ �� �������, ����� �� ���������...
}
