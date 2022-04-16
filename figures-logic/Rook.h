#include "ChessFigure.h"

class Rook: public Figure
{
public:
    Rook(bool col, char vert, int hor) : Figure(col, vert, hor) {};
    Rook(Rook &f) : Figure(f.colour, f.vertical, f.horizontal) {};
    int move(char vert, int hor) override;
    int cut_down(Figure &f) override;
};
