#pragma once
#include <ChessFigure.h>
enum SquareColor { white, black };

class Square {
private:
	Piece piece;
	char piece_color = 'n'; //n - none, w - white, b - black
	SquareColor square_color;
public:
	void setPlace(Square*);
	void setEmpty();
	void setPieceAndColor(Piece, char);
	void setPieceColor(char);
	void setSquareColor(SquareColor);
	Piece getPiece();
	char getPieceColor();
	Square();
};

Square::Square()
{
	piece = EMPTY;
	square_color = white;
}

void Square::setPlace(Square* place)
{
	piece_color = place->getPieceColor();
	piece = place->getPiece();
}

void Square::setSquareColor(SquareColor s)
{
	square_color = s;
}

void Square::setEmpty()
{
	piece_color = 'n';
	piece = EMPTY;
}

Piece Square::getPiece()
{
	return piece;
}

char Square::getPieceColor()
{
	return piece_color;
}

void Square::setPieceAndColor(Piece p, char c)
{
	piece = p;
	piece_color = c;
}

void Square::setPieceColor(char c)
{
	piece_color = c;
}