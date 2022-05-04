#pragma once
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
//  a b c d e f g h - vertical
//0 - hor
//1
//2
//3
//4
//5
//6
//7
using namespace std;

class Board
{ // Piece
public:
	int figures_count = 0;
	Piece* square[8][8];
	Board();
	void SetBoard(); // изначальное положение доски
	void SetPiece(Colour colour, int hor, int vert, TypePiece type); // поставить фигуру, либо удалить её, если Empty
	void PieceMoving(int vEnd, int hEnd, int vStart, int hStart); 
	bool move(int vert, int hor, Colour col, Piece* piece);
	bool cut_down(int vert, int hor, Colour col, Piece* piece);
	void SetSquare(int hor, int vert);
};

Board* CreateBoard()
{
	Board* board = new Board();
	return board;
}

Board::Board() { SetBoard(); }

void Board::SetBoard()
{
	for (int i = 0; i < 8; i++)
	{
		Colour colour = NONE;
		if (i < 2) colour = WHITE;
		if (i > 5) colour = BLACK;
		if (i == 0 || i == 7)
		{

			square[i][0] = new Rook(colour, 0, i, ROOK);
			square[i][1] = new Knight(colour, 1, i, KNIGHT);
			square[i][2] = new Bishop(colour, 2, i, BISHOP);
			square[i][3] = new Queen(colour, 3, i, QUEEN);
			square[i][4] = new King(colour, 4, i, KING);
			square[i][5] = new Bishop(colour, 5, i, BISHOP);
			square[i][6] = new Knight(colour, 6, i, KNIGHT);
			square[i][7] = new Rook(colour, 7, i, ROOK);
		}
		else
		{
			for (int j = 0; j < 8; j++)
				if (i == 1 || i == 6)
					square[i][j] = new Pawn(colour, j, i, PAWN);
				else
					square[i][j] = new Piece(colour, j, i, EMPTY);
		}
	}
}

void Board::SetPiece(Colour colour, int hor, int vert, TypePiece type)
{
	switch (type)
	{
	case (KING):
		square[hor][vert] = new King(colour, vert, hor, KING);
	case (QUEEN):
		square[hor][vert] = new Queen(colour, vert, hor, QUEEN);
	case(BISHOP):
		square[hor][vert] = new Bishop(colour, vert, hor, BISHOP);
	case(KNIGHT):
		square[hor][vert] = new Knight(colour, vert, hor, KNIGHT);
	case(ROOK):
		square[hor][vert] = new Rook(colour, vert, hor, ROOK);
	case(PAWN):
		square[hor][vert] = new Pawn(colour, vert, hor, PAWN);
	case (EMPTY):
		square[hor][vert] = new Piece(NONE, vert, hor, EMPTY);
	}
}

void Board::PieceMoving(int vEnd, int hEnd, int vStart, int hStart)
{
	square[hEnd][vEnd] = square[hStart][vStart];
	SetPiece(NONE, hStart, vStart, EMPTY);
}

Board* board = CreateBoard();

bool CanCut(pair<int, int> coords, Piece* CheckingPiece)
{
	if (coords.first != -1)
	{
		//ЗАМЕНИ
		//return board->square[coords.first][coords.second]->cut_down(*CheckingPiece); 
	}
	return false;
}

void funkBishop(vector<pair<int, int>>& PossibleMoves, int vEnd, int hEnd, int vStart, int hStart, char colour)
{
	int vsign = 1;
	int hsign = 1;
	if (vEnd < vStart) vsign = -1;
	if (hEnd < hStart) hsign = -1;
	vStart += vsign;
	hStart += hsign;
	std::pair<int, int> coords;
	for (; abs(vStart - vEnd) > 0; vStart += vsign, hStart += hsign)
	{
		if (board->square[hStart][vStart]->GetName() == EMPTY)
			PossibleMoves.push_back(make_pair(hStart, vStart));
		else
		{
			if (board->square[hStart][vStart]->GetColour() != colour && board->square[hStart][vStart]->GetName() != KING)
				PossibleMoves.push_back(make_pair(hStart, vStart));
		}
	}
}

void funkRook(vector<pair<int, int>>& PossibleMoves, int vEnd, int hEnd, int vStart, int hStart, char colour)
{
	int sign = 1;
	int End = vEnd;
	int Start = vStart;
	if (vEnd == vStart)
	{
		int End = hEnd;
		int Start = hStart;
	}
	if (End < Start) sign = -1;
	Start += sign;
	for (; abs(Start - End) > 0; Start += sign)
	{
		if (board->square[hStart][vStart]->GetName() == EMPTY)
			PossibleMoves.push_back(make_pair(hStart, vStart));
		else
		{
			if (board->square[hStart][vStart]->GetColour() != colour && board->square[hStart][vStart]->GetName() != KING)
				PossibleMoves.push_back(make_pair(hStart, vStart));
		}
	}
}

void FindPossibleMovesForRook(vector<pair<int, int>>& PossibleMoves, int vStart, int hStart, char colour)
{
	funkRook(PossibleMoves, vStart, 7, vStart, hStart, colour);
	funkRook(PossibleMoves, vStart, 0, vStart, hStart, colour);
	funkRook(PossibleMoves, 0, hStart, vStart, hStart, colour);
	funkRook(PossibleMoves, 7, hStart, vStart, hStart, colour);
}

pair<int, int> GetEdge(int vStart, int hStart, int hor)
{
	int vStartLeft = vStart;
	int vStartRight = vStart;
	int sign = 1;
	if (hor == 0)
		sign = -1;
	for (; hStart != hor; hStart += sign, vStartRight += 1, vStartLeft -= 1)
		return std::make_pair(vStartRight, vStartLeft);
}

void FindPossibleMovesForBishop(vector<pair<int, int>>& PossibleMoves, int vStart, int hStart, char colour)
{
	std::pair<int, int> Up = GetEdge(vStart, hStart, 7);
	std::pair<int, int> Down = GetEdge(vStart, hStart, 0);

	funkBishop(PossibleMoves, Down.first, 0, vStart, hStart, colour);
	funkBishop(PossibleMoves, Down.second, 0, vStart, hStart, colour);
	funkBishop(PossibleMoves, Up.first, 7, vStart, hStart, colour);
	funkBishop(PossibleMoves, Up.second, 7, vStart, hStart, colour);
}

void FindPossibleMovesForQueen(vector<pair<int, int>>& PossibleMoves, int vStart, int hStart, char colour)
{
	FindPossibleMovesForRook(PossibleMoves, vStart, hStart, colour);
	FindPossibleMovesForBishop(PossibleMoves, vStart, hStart, colour);
}

bool CanMakeMove(vector<pair<int, int>>& PossibleMoves, bool& CanMove, pair<int, int> coords)
{
	if (PossibleMoves.empty())
	{
		return false;
		CanMove = false;
	}
	CanMove = true;
	if (std::find(PossibleMoves.begin(), PossibleMoves.end(), coords) != PossibleMoves.end())
		return true;
	return false;

}

pair<int, int> KingLikeBishop(pair<int, int> coords, int vEnd, int hEnd, int vStart, int hStart, char kingColour)
{
	int vsign = 1;
	int hsign = 1;
	if (vEnd < vStart) vsign = -1;
	if (hEnd < hStart) hsign = -1;
	vStart += vsign;
	hStart += hsign;
	for (; abs(vStart - vEnd) > 0; vStart += vsign, hStart += hsign)
	{
		if (board->square[hStart][vStart]->GetColour() != kingColour && board->square[hStart][vStart]->GetName() != EMPTY)
		{
			coords.first = hStart;
			coords.second = vStart;
			return coords;
		}
	}
	return coords;
}

pair<int, int> KingLikeRook(pair<int, int> coords, int vEnd, int hEnd, int vStart, int hStart, char kingColour)
{
	int sign = 1;
	int End = vEnd;
	int Start = vStart;
	if (vEnd == vStart)
	{
		int End = hEnd;
		int Start = hStart;
	}
	if (End < Start) sign = -1;
	Start += sign;
	for (; abs(Start - End) > 0; Start += sign)
	{
		if (board->square[Start][Start]->GetColour() != kingColour && board->square[hStart][vStart]->GetName() != EMPTY)
		{
			coords.first = hStart;
			coords.second = vStart;
			return coords;
		}
	}
	return coords;
}

bool KingLikeKnight(int vStart, int hStart, char kingColour)
{
	if (board->square[hStart + 2][vStart + 1]->GetName() == KNIGHT && board->square[hStart + 2][vStart + 1]->GetColour() != kingColour && Check(vStart + 2, hStart + 1))
		return true;
	if (board->square[hStart + 1][vStart + 2]->GetName() == KNIGHT && board->square[hStart + 1][vStart + 2]->GetColour() != kingColour && Check(vStart + 1, hStart + 2))
		return true;
	if (board->square[hStart - 1][vStart + 2]->GetName() == KNIGHT && board->square[hStart - 1][vStart + 2]->GetColour() != kingColour && Check(vStart - 1, hStart + 2))
		return true;
	if (board->square[hStart - 2][vStart + 1]->GetName() == KNIGHT && board->square[hStart - 1][vStart + 2]->GetColour() != kingColour && Check(vStart - 1, hStart + 2))
		return true;
	if (board->square[hStart - 2][vStart - 1]->GetName() == KNIGHT && board->square[hStart - 2][vStart - 1]->GetColour() != kingColour && Check(vStart - 2, hStart - 1))
		return true;
	if (board->square[hStart - 1][vStart - 2]->GetName() == KNIGHT && board->square[hStart - 1][vStart - 2]->GetColour() != kingColour && Check(vStart - 1, hStart - 2))
		return true;
	if (board->square[hStart + 1][vStart - 2]->GetName() == KNIGHT && board->square[hStart + 1][vStart - 2]->GetColour() != kingColour && Check(vStart + 1, hStart - 2))
		return true;
	if (board->square[hStart + 2][vStart - 1]->GetName() == KNIGHT && board->square[hStart + 2][vStart - 1]->GetColour() != kingColour && Check(vStart + 2, hStart - 1))
		return true;

	return false;
}

bool HasCheck(int vStart, int hStart, char kingColour) //шах
{
	std::pair<int, int> coords(-1, -1);
	Piece* CheckingPiece = board->square[hStart][vStart];

	pair<int, int> coord1 = KingLikeRook(coords, vStart, 7, vStart, hStart, kingColour);
	pair<int, int> coord2 = KingLikeRook(coords, vStart, 0, vStart, hStart, kingColour);
	pair<int, int> coord3 = KingLikeRook(coords, 0, hStart, vStart, hStart, kingColour);
	pair<int, int> coord4 = KingLikeRook(coords, 7, hStart, vStart, hStart, kingColour);

	std::pair<int, int> Up = GetEdge(vStart, hStart, 7);
	std::pair<int, int> Down = GetEdge(vStart, hStart, 0);

	pair<int, int> coord5 = KingLikeBishop(coords, Down.first, 0, vStart, hStart, kingColour);
	pair<int, int> coord6 = KingLikeBishop(coords, Down.second, 0, vStart, hStart, kingColour);
	pair<int, int> coord7 = KingLikeBishop(coords, Up.first, 7, vStart, hStart, kingColour);
	pair<int, int> coord8 = KingLikeBishop(coords, Up.second, 7, vStart, hStart, kingColour);

	if (CanCut(coord1, CheckingPiece) || CanCut(coord2, CheckingPiece) || CanCut(coord3, CheckingPiece)
		|| CanCut(coord4, CheckingPiece) || CanCut(coord5, CheckingPiece) || CanCut(coord6, CheckingPiece)
		|| CanCut(coord7, CheckingPiece) || CanCut(coord8, CheckingPiece) || KingLikeKnight(vStart, hStart, kingColour)) return true;

	return false;
}

void MakeCastling(vector<pair<int, int>>& PossibleMoves, int vEnd, int vStart, int hStart)
{
	int sign = -2;
	if (vEnd > vStart)
		sign = 2;
	if (board->square[hStart][vEnd]->GetName() == ROOK)
	{
		if (board->square[hStart][vEnd]->getFirstMove() == false)
		{
			bool allClear = true;
			for (int i = min(vEnd, vStart) + 1; i < max(vEnd, vStart) && allClear; ++i)
			{
				if (board->square[hStart][i]->GetName() != EMPTY)
					allClear = false;
			}
			if (allClear)
				PossibleMoves.push_back(make_pair(hStart, vStart + sign));
		}
	}
}

void FindPossibleMovesForKing(vector<pair<int, int>>& PossibleMoves, int vStart, int hStart, char colour)
{
	if (!HasCheck(vStart, hStart + 1, colour))
		funkRook(PossibleMoves, vStart, hStart + 1, vStart, hStart, colour);
	if (!HasCheck(vStart, hStart - 1, colour))
		funkRook(PossibleMoves, vStart, hStart - 1, vStart, hStart, colour);
	if (!HasCheck(vStart - 1, hStart, colour))
		funkRook(PossibleMoves, vStart - 1, hStart, vStart, hStart, colour);
	if (!HasCheck(vStart + 1, hStart, colour))
		funkRook(PossibleMoves, vStart + 1, hStart, vStart, hStart, colour);
	if (!HasCheck(vStart + 1, hStart + 1, colour))
		funkBishop(PossibleMoves, vStart + 1, hStart + 1, vStart, hStart, colour);
	if (!HasCheck(vStart - 1, hStart + 1, colour))
		funkBishop(PossibleMoves, vStart - 1, hStart + 1, vStart, hStart, colour);
	if (!HasCheck(vStart + 1, hStart - 1, colour))
		funkBishop(PossibleMoves, vStart + 1, hStart - 1, vStart, hStart, colour);
	if (!HasCheck(vStart - 1, hStart - 1, colour))
		funkBishop(PossibleMoves, vStart - 1, hStart - 1, vStart, hStart, colour);
	//рокировка
	if (board->square[hStart][vStart]->getFirstMove() == false && !HasCheck(vStart, hStart, colour))
	{
		if (!HasCheck(2, hStart, colour))
			MakeCastling(PossibleMoves, 0, vStart, hStart);
		if (!HasCheck(6, hStart, colour))
			MakeCastling(PossibleMoves, 7, vStart, hStart);
	}
}

void funkKnight(vector<pair<int, int>>& PossibleMoves, int vEnd, int hEnd, char colour)
{
	if (Check(vEnd, hEnd) && board->square[hEnd][vEnd]->GetColour() != colour && board->square[hEnd][vEnd]->GetName() != KING)
		PossibleMoves.push_back(make_pair(hEnd, vEnd));
}

void FindPossibleMovesForKnight(vector<pair<int, int>>& PossibleMoves, int vStart, int hStart, char colour)
{
	funkKnight(PossibleMoves, vStart - 1, hStart - 2, colour);
	funkKnight(PossibleMoves, vStart - 1, hStart + 2, colour);
	funkKnight(PossibleMoves, vStart + 1, hStart - 2, colour);
	funkKnight(PossibleMoves, vStart + 1, hStart + 2, colour);
	funkKnight(PossibleMoves, vStart - 2, hStart - 1, colour);
	funkKnight(PossibleMoves, vStart - 2, hStart + 1, colour);
	funkKnight(PossibleMoves, vStart + 2, hStart - 1, colour);
	funkKnight(PossibleMoves, vStart + 2, hStart + 1, colour);
}


void FindPossibleMovesForPawn(vector<pair<int, int>>& PossibleMoves, int vStart, int hStart, char colour, bool didMove)
{
	int tmp = 1;
	if (didMove == false)
		tmp = 2;
	funkRook(PossibleMoves, vStart, vStart + tmp, vStart, hStart, colour);
	funkBishop(PossibleMoves, vStart + 1, hStart + 1, vStart, hStart, colour);
	funkBishop(PossibleMoves, vStart - 1, hStart + 1, vStart, hStart, colour);
}


void Board::SetSquare(int hor, int vert)
{

}

bool Board::move(int vert, int hor, Colour col, Piece* piece)
{
	Colour colour = piece->GetColour();
	TypePiece type = piece->GetName();
	auto PossibleMoves = *(piece->GetVector());
	bool canMove = piece->GetCanMove();
	int vertical = piece->GetVert();
	int horizontal = piece->GetHor();
	bool* didMove = piece->GetDidMove();
	switch (type)
	{
	case (KING):
		PossibleMoves.clear();
		FindPossibleMovesForKing(PossibleMoves, vertical, horizontal, colour);
		if (col == NONE && Check(vert, hor) && CanMakeMove(PossibleMoves, canMove, make_pair(hor, vert)))
		{
			//добавить перемещение ладьи при рокировке
			board->PieceMoving(vert, hor, vertical, horizontal);
			horizontal = hor;
			vertical = vert;
			*didMove = true;
			return true;
		}
		return false;
	case (QUEEN):
		PossibleMoves.clear();
		FindPossibleMovesForQueen(PossibleMoves, vertical, horizontal, colour);
		if (col == NONE && Check(vert, hor) && CanMakeMove(PossibleMoves, canMove, make_pair(hor, vert)))
		{
			board->PieceMoving(vert, hor, vertical, horizontal);
			horizontal = hor;
			vertical = vert;
			return true;
		}
		return false;
	case(BISHOP):
		PossibleMoves.clear();
		FindPossibleMovesForBishop(PossibleMoves, vertical, horizontal, colour);
		if (col == NONE && Check(vert, hor) && CanMakeMove(PossibleMoves, canMove, make_pair(hor, vert)))
		{
			board->PieceMoving(vert, hor, vertical, horizontal);
			horizontal = hor;
			vertical = vert;
			return true;
		}
		return false;
	case(KNIGHT):
		PossibleMoves.clear();
		FindPossibleMovesForKnight(PossibleMoves, vertical, horizontal, colour);
		if (col == NONE && Check(vert, hor) && CanMakeMove(PossibleMoves, canMove, make_pair(hor, vert)))
		{
			board->PieceMoving(vert, hor, vertical, horizontal);
			horizontal = hor;
			vertical = vert;
			return true;
		}
		return false;
	case(ROOK):
		PossibleMoves.clear();
		FindPossibleMovesForRook(PossibleMoves, piece->GetVert(), piece->GetHor(), colour);
		if (canMove && col == NONE && Check(vert, hor) && CanMakeMove(PossibleMoves, canMove, make_pair(hor, vert)))
		{
			board->PieceMoving(vert, hor, vertical, horizontal);
			horizontal = hor;
			vertical = vert;
			*didMove = true;
			return true;
		}
		return false;
	case(PAWN):
		PossibleMoves.clear();
		FindPossibleMovesForPawn(PossibleMoves, vertical, horizontal, colour, didMove);
		if (col == NONE && Check(vert, hor) && CanMakeMove(PossibleMoves, canMove, make_pair(hor, vert)))
		{
			board->PieceMoving(vert, hor, vertical, horizontal);
			vertical = vert;
			*didMove = true;
			return true;
			//переопределение пешки
			if (horizontal == 7 || horizontal == 0)
			{
				TypePiece type;
				board->SetPiece(colour, horizontal, vertical, type);
			}
		}
		return 0;
	case (EMPTY):
		return false;
	}
}

bool Board::cut_down(int vert, int hor, Colour col, Piece* piece)
{
	Colour colour = piece->GetColour();
	TypePiece type = piece->GetName();
	auto PossibleMoves = *(piece->GetVector());
	bool canMove = piece->GetCanMove();
	int vertical = piece->GetVert();
	int horizontal = piece->GetHor();
	bool* didMove = piece->GetDidMove();
	int vsign = 1;
	int hsign = 1;
	switch (type)
	{
	case (KING):
		if (colour != col && CanMakeMove(PossibleMoves, canMove, make_pair(hor, vert)))
		{
			int newHor = hor;
			int newVert = vert;
			board->PieceMoving(vert, hor, vertical, horizontal);
			horizontal = newHor;
			vertical = newVert;
			return true;
		}
		return false;
	case (QUEEN):
		if (vert < vertical) vsign = -1;
		if (vert == vertical) vsign = 0;
		if (hor < horizontal) hsign = -1;
		if (hor == horizontal) hsign = 0;
		//FindPossibleMovesForQueen(PossibleMoves, vertical, horizontal, colour);
		if (colour != col && CanMakeMove(PossibleMoves, canMove, make_pair(hor, vert)))
		{
			int newHor = hor;
			int newVert = vert;
			board->PieceMoving(vert, hor, vertical, horizontal);
			horizontal = newHor;
			vertical = newVert;
			return true;
		}
		return false;
	case(BISHOP):
		if (vert < vertical) vsign = -1;
		if (hor < horizontal) hsign = -1;
		//PossibleMoves.clear();
		//FindPossibleMovesForBishop(PossibleMoves, vertical, horizontal, colour);
		if (colour != col && CanMakeMove(PossibleMoves, canMove, make_pair(hor, vert)))
		{
			int newHor = hor;
			int newVert = vert;
			board->PieceMoving(vert, hor, vertical, horizontal);
			horizontal = newHor;
			vertical = newVert;
			return true;
		}
		return false;
	case(KNIGHT):
		if (colour != col && CanMakeMove(PossibleMoves, canMove, make_pair(hor, vert)))
		{
			int newHor = hor;
			int newVert = vert;
			board->PieceMoving(vert, hor, vertical, horizontal);
			horizontal = newHor;
			vertical = newVert;
			return true;
		}
		return false;
	case(ROOK):
		if (vert < vertical) vsign = -1;
		if (vert == vertical) vsign = 0;
		if (hor < horizontal) hsign = -1;
		if (hor == horizontal) hsign = 0;
		//PossibleMoves.clear();
		//FindPossibleMovesForRook(PossibleMoves, vertical, horizontal, colour);
		if (colour != col && CanMakeMove(PossibleMoves, canMove, make_pair(hor, vert)))
		{
			int newHor = hor;
			int newVert = vert;
			board->PieceMoving(vert, hor, vertical, horizontal);
			horizontal = newHor;
			vertical = newVert;
			return true;
		}
		return false;
	case(PAWN):
		if (hor < horizontal) return false;
		if (colour != col && CanMakeMove(PossibleMoves, canMove, make_pair(hor, vert)))
		{
			int newHor = hor;
			int newVert = vert;
			board->PieceMoving(vert, hor, vertical, horizontal);
			horizontal = newHor;
			vertical = newVert;
			return true;
			//взятие на проходе
		}
		return false;
	case (EMPTY):
		return false;
	}
}




