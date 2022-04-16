#include <iostream>

class Figure
{
protected:
    bool colour; // цвет фигуры
    char vertical; // буквы
    int horizontal; // цифры
public:
    Figure(bool colour, char vert, int hor) : colour(colour), vertical(vert), horizontal(hor) {};
    Figure(Figure &f)
    {
        colour = f.colour;
        vertical = f.vertical;
        horizontal = f.horizontal;
    };
    virtual int move(char vert, int hor) = 0;
    virtual int cut_down(Figure &f) = 0;
};

