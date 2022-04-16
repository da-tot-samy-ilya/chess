#pragma once
#include <iostream>

class Piece
{
protected:
    bool colour; // цвет фигуры: 1 - black, 0 - white
    int vertical; // буквы
    int horizontal; // цифры
public:
    Piece(bool colour, int vert, int hor) : colour(colour), vertical(vert), horizontal(hor) {};
    Piece(Piece& f)
    {
        colour = f.colour;
        vertical = f.vertical;
        horizontal = f.horizontal;
    };
    virtual int move(int vert, int hor) = 0;
    virtual int cut_down(Piece& f) = 0;
};
