#pragma once
#include "ChessFigure.h"
#include "Board.h"

class King : public Piece
{
private:
    bool didMove = false;
    bool haveCheck = false;
public:
    King(char col, int vert, int hor) : Piece(col, vert, hor) {};
    King(King& f) : Piece(f.colour, f.vertical, f.horizontal) {};
    bool move(int vert, int hor) override;
    bool cut_down(Piece& f) override;
    bool getFirstMove() { return didMove; };
};

bool King::move(int vert, int hor)
{
    if ((Check(vert, hor)) && (vertical + 1 == vert && horizontal == hor || vertical == vert && horizontal + 1 == hor ||
        vertical - 1 == vert && horizontal == hor || vertical == vert && horizontal - 1 == hor ||
        vertical + 1 == vert && horizontal + 1 == hor || vertical + 1 == vert && horizontal - 1 == hor ||
        vertical - 1 == vert && horizontal + 1 == hor || vertical - 1 == vert && horizontal - 1 == hor))
    {
        horizontal = hor;
        vertical = vert;
        didMove = true;
        return true;
    }
    else if (this.getFirstMove() == false) //рокировка
    {
        if (square[0][hor].getEmpty() == false && (square[0][hor].getPiece() == r1 || square[0][hor].getPiece() == r3) && square[0][hor].getPieceColor() == this.colour)
        {
            bool emptySquares = true;
            for (int i = 1; i < 3; ++i)
            {
                if (!square[i][hor].getEmpty())
                {
                    emptySquares = false;
                    break;
                }
            }
            if (emptySquares)
            {
                square[2][hor].setPieceAndColor(square[vert][hor].getPiece(), this.colour);
                square[vert][hor].setEmpty();
                square[3][hor].setPieceAndColor(square[0][hor].getPiece(), this.colour);
                square[0][hor].setEmpty();
            }
        }
        else if ((square[7][hor].getPiece() == r2 || square[7][hor].getPiece() == r4) && square[7][hor].getPieceColor() == c)
        {
            bool emptySquares = true;
            for (int i = 5; i < 7; ++i)
            {
                if (!square[i][hor].getEmpty())
                {
                    emptySquares = false;
                    break;
                }
            }
            if (emptySquares)
            {
                square[6][hor].setPieceAndColor(square[vert][hor].getPiece(), this.colour);
                square[vert][hor].setEmpty();
                square[5][hor].setPieceAndColor(square[0][hor].getPiece(), this.colour);
                square[0][hor].setEmpty();
            }
        }

    }
    return false;
}
bool King::cut_down(Piece& f)
{
    
}