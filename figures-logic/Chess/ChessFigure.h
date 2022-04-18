#pragma once
#include <iostream>
#include "CheckingForMove.h"
#include "Board.h"

class Piece
{
private:
    TypePiece type_piece = EMPTY;
protected:
    char colour; // цвет фигуры
    int vertical; // буквы
    int horizontal;// цифры
public:
    Piece() : colour('n'), vertical(-1), horizontal(-1) {};
    Piece(char colour, int vert, int hor) : colour(colour), vertical(vert), horizontal(hor) {};
    Piece(Piece& f)
    {
        colour = f.colour;
        vertical = f.vertical;
        horizontal = f.horizontal;
    };
    virtual bool move(int vert, int hor) { return false; };
    virtual bool cut_down(Piece& f) { return false; };

    char GetColour() { return this->colour; };
    int GetVert() { return this->vertical; };
    int GetHor() { return this->horizontal; };
    TypePiece GetName() { return this->type_piece; };
};

bool Check(int vert, int hor)
{
    if (vert != -1 && vert != 8 && hor != -1 && hor != 8)
        return false;
    return true;
}