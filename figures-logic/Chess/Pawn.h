#pragma once
#include "ChessFigure.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"

class Pawn : public Piece
{
private:
    bool didMove = false;
public:
    Pawn(char col, int vert, int hor) : Piece(col, vert, hor) {};
    Pawn(Pawn& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    int move(int vert, int hor) override;
    int cut_down(Piece& f) override;
};

int Pawn::move(int vert, int hor)
{
    if (Check(vert, hor) && ((!didMove && vertical == vert - 2) || (vertical == vert - 1)))
    {
        vertical = vert;
        didMove = true;
        if (vert == 7 || vert == 0)
        {
            char a;
            switch (a)
            {
            case('r'):
                Rook(colour, vertical, horizontal); // будет похоже на срубание фигуры
            case('b'):
                Bishop(colour, vertical, horizontal);
            case('q'):
                Queen(colour, vertical, horizontal);
            case('k'):
                Knight(colour, vertical, horizontal);
            }
        }
            return 1;
    }
    return 0;
}
int Pawn::cut_down(Piece& f)
{
    //взятие на проходе, рубят по диагонали...
}
