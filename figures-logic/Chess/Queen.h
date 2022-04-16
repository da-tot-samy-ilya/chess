#pragma once
#include "Bishop.h"
#include "Rook.h"

class Queen : public Piece
{
public:
	Queen(bool col, int vert, int hor) : Piece(col, vert, hor) {};
	Queen(Queen& f) : Piece(f.colour, f.vertical, f.horizontal) {};
	int move(int vert, int hor) override;
	int cut_down(Piece& f) override;	
    friend int Rook::move(int vert, int hor);
    friend int Bishop::move(int vert, int hor);
};


int Queen::move(int vert, int hor)
{
	return Rook::move(vert, hor) || Bishop::move(vert, hor);
}
int Queen::cut_down(Piece& f)
{

}