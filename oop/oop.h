#pragma once
#include <vector>

enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
//enum PieceColor { WHITE, BLACK, NONE };
enum SquareColor { white, black };

class Square {
private:
	Piece piece;
	//PieceColor piece_color;
	bool piece_color;
	SquareColor square_color;
public:
	void setPlace(Square*);
	void setEmpty();
	void setPieceAndColor(Piece, bool);
	void setPieceColor(bool);
	void setSquareColor(SquareColor);
	Piece getPiece();
	bool getPieceColor();
	Square();
};

class Board
{
public:
	std::vector <std::vector <Square>> square[8][8];
	void SetBoard();
};

class Chess
{
protected:
	Board board;
public:
	virtual void gameStart(void) = 0;
};

class Chess_1 : public Chess
{
public:
	void gameStart() {
		//начало таймера
	}
};

class Chess_2 : public Chess_1
{
private:
	unsigned PassTime; //время хода
public:
	Chess_2(unsigned pass_time = 1200) : PassTime(pass_time) {}
	void setTime(unsigned sec) {
		PassTime = sec;
	}
	//время хода вышло
	int timeEnd(void) {
		//...
	}
	void gameStart(void) {
		//...
	}
};

/*
class Player
{
private:
	bool color;
	bool isMoving;
public:
	bool getMove() {
		//...
	};
	bool getColor() { return color; }

};
*/
