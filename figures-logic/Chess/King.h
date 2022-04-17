#pragma once
#include "ChessFigure.h"
#include "Square.h"
#include "Board.h"

class King : public Piece
{
private:
    bool didMove = false;
    bool haveCheck = false;
public:
    King(char col, int vert, int hor) : Piece(col, vert, hor) {};
    King(King& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    int move(int vert, int hor) override;
    int cut_down(Piece& f) override;
    bool getFirstMove() {return didMove};
};

int King::move(int vert, int hor)
{
    if (vertical + 1 == vert && horizontal == hor || vertical == vert && horizontal + 1 == hor ||
        vertical - 1 == vert && horizontal == hor || vertical == vert && horizontal - 1 == hor ||
        vertical + 1 == vert && horizontal + 1 == hor || vertical + 1 == vert && horizontal - 1 == hor ||
        vertical - 1 == vert && horizontal + 1 == hor || vertical - 1 == vert && horizontal - 1 == hor)
    {
        horizontal = hor;
        vertical = vert;
        didMove = true;
        return 1;
    }
    else if (this.getFirstMove == false) //ракировка
    {
        if (square[hor][0].getPiece() == r1 && square[hor][0].getPieceColor == this.colour)
        {
            
        }

    }
    return 0;
}
int King::cut_down(Piece& f)
{
    
}