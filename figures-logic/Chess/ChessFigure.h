#pragma once
#include <iostream>

class Piece
{
protected:
    char colour; // цвет фигуры: 1 - black, 0 - white
    int vertical; // буквы
    int horizontal; // цифры
public:
    Piece(char colour, int vert, int hor) : colour(colour), vertical(vert), horizontal(hor) {};
    Piece(Piece& f)
    {
        colour = f.colour;
        vertical = f.vertical;
        horizontal = f.horizontal;
    };
    virtual int move(int vert, int hor) = 0;
    virtual int cut_down(Piece& f) = 0;
};

bool Check(int vert, int hor)
{
    if (vert != -1 && vert != 8 && hor != -1 && hor != 8)
        return false;
    return true;
}