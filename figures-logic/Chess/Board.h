#pragma once
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include <algorithm>
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
vector<pair<int, int>>* MakePossibleMoves(Piece* piece);

pair<int, int> hasMadeMove; //изменение

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



Board::Board() { SetBoard(); }

void Board::SetBoard()
{
	//for (int i = 0; i < 8; i++)
	//{
	//	Colour colour = NONE;
	//	if (i < 2) colour = WHITE;//AHAHAHAHHA
	//	if (i > 5) colour = BLACK;
	//	if (i == 0 || i == 7)
	//	{
	//		square[i][0] = new Rook(colour, 0, i, ROOK);
	//		square[i][1] = new Knight(colour, 1, i, KNIGHT);
	//		square[i][2] = new Bishop(colour, 2, i, BISHOP);
	//		square[i][3] = new Queen(colour, 3, i, QUEEN);
	//		square[i][4] = new King(colour, 4, i, KING);
	//		square[i][5] = new Bishop(colour, 5, i, BISHOP);
	//		square[i][6] = new Knight(colour, 6, i, KNIGHT);
	//		square[i][7] = new Rook(colour, 7, i, ROOK);
	//	}
	//	else
	//	{
	//		for (int j = 0; j < 8; j++)
	//			if (i == 1 || i == 6)
	//				square[i][j] = new Pawn(colour, j, i, PAWN);
	//			else
	//				square[i][j] = new Piece(colour, j, i, EMPTY);
	//	}
	//}

	for (int i = 0; i<8; i++)
		for (int j = 0; j < 8; j++)
			square[i][j] = new Piece(NONE, j, i, EMPTY);
	square[4][4] = new King(WHITE, 4, 4, KING);
	square[2][7] = new Queen(BLACK, 7, 2, QUEEN);

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
Board board;
pair<int, int> WhiteKingCoords = make_pair(0, 4);
pair<int, int> BlackKingCoords = make_pair(7, 4);
Piece* CopySquare[8][8];

Board* CreateBoard()
{
	return &board;
}

void Board::PieceMoving(int vEnd, int hEnd, int vStart, int hStart)
{
	square[hEnd][vEnd] = square[hStart][vStart];
	SetPiece(NONE, hStart, vStart, EMPTY);
}

bool CanMakeMove(vector<pair<int, int>>& PossibleMoves, bool& CanMove, pair<int, int> coords)
{
	if (PossibleMoves.empty())
	{
		CanMove = false;
		return false;
	}
	CanMove = true;
	if (find(PossibleMoves.begin(), PossibleMoves.end(), coords) != PossibleMoves.end())
		return true;
	return false;
}

pair<int, int> KingLikeBishop(pair<int, int> coords, int vEnd, int hEnd, int vStart, int hStart, Colour kingColour)
{
	int vert = vStart;
	int hor = hStart;
	int vsign = 1;
	int hsign = 1;
	if (vEnd < vStart) vsign = -1;
	if (hEnd < hStart) hsign = -1;
	vStart += vsign;
	hStart += hsign;
	if (Check(hStart, vStart) && *(board.square[hStart][vStart]->GetName()) == PAWN && *(board.square[hStart][vStart]->GetColour()) != kingColour)
	{
		coords.first = hStart;
		coords.second = vStart;
		return coords;
	}
	for (; abs(vStart - hStart) > 0 && vStart < 8 && vStart > -1 && hStart < 8 && hStart > -1; vStart += vsign, hStart += hsign)
	{
		if (*(board.square[hStart][vStart]->GetName()) == BISHOP || *(board.square[hStart][vStart]->GetName()) == QUEEN)
		{
			if (*(board.square[hStart][vStart]->GetColour()) != kingColour)
			{
				coords.first = hStart;
				coords.second = vStart;
				return coords;
			}
			if (*(board.square[hStart][vStart]->GetColour()) == kingColour /*&& *(board.square[hStart][vStart])->GetName() != KING*/)
			{
				//cout << 'a' << endl;
				return coords;
			}
		}
	}
	return coords;
}

pair<int, int> KingLikeRook(pair<int, int> coords, int vEnd, int hEnd, int vStart, int hStart, Colour kingColour) //
{
	int hS, vS, hE, vE;
	bool p = false;
	int sign = 1;
	bool StartisV = true;
	int End = vEnd;
	int Start = vStart;
	if (vEnd == vStart)
	{
		End = hEnd;
		Start = hStart;
		StartisV = false;
	}
	if (End < Start) sign = -1;
	Start += sign;
	//if (StartisV)
	//{
	//	if (*(board.square[hStart][Start]->GetName()) == KING)
	//	{
	//		//board.PieceMoving(vStart, hStart, Start, hStart);
	//		hS = hStart;
	//		vS = vStart;
	//		hE = hStart;
	//		vE = Start;
	//		p = true;
	//	}
	//}
	//else
	//{
	//	if (*(board.square[Start][vStart]->GetName()) == KING)
	//	{
	//		//board.PieceMoving(vStart, hStart, vStart, Start);
	//		hS = hStart;
	//		vS = vStart;
	//		hE = Start;
	//		vE = vStart;
	//		p = true;
	//	}
	//}
	for (; abs(Start - End) > 0 && Start < 8 && Start > -1; Start += sign)
	{
		if (StartisV)
		{
			if (*(board.square[hStart][Start]->GetName()) == ROOK || *(board.square[hStart][Start]->GetName()) == QUEEN)
			{
				if (*(board.square[hStart][Start]->GetColour()) != kingColour)
				{
					//vector<pair<int, int>>* PossibleMoves = MakePossibleMoves(board.square[hStart][Start]);
					//*(board.square[hStart][Start]->GetPossibleMoves())
					coords.first = hStart;
					coords.second = Start;
					/*if (p)
						board.PieceMoving(vE, hE, vS, hS);*/
					//if (p)
					//{
					//	if (find(PossibleMoves->begin(), PossibleMoves->end(), make_pair(hE, vE)) != PossibleMoves->end())
					//	{
					//		PossibleMoves->push_back(make_pair(hS, vS));
					//	}
					//}
					return coords;
				}
			}
		}
		else
		{
			if (*(board.square[Start][vStart]->GetName()) == ROOK || *(board.square[Start][vStart]->GetName()) == QUEEN)
			{
				if (*(board.square[Start][vStart]->GetColour()) != kingColour)
				{
					//vector<pair<int, int>>* PossibleMoves = MakePossibleMoves(board.square[Start][vStart]);
					//MakePossibleMoves(board.square[Start][vStart]);
					coords.first = Start;
					coords.second = vStart;
					/*if (p)
						board.PieceMoving(vE, hE, vS, hS);*/
					/*if (p)
					{
						if (find(PossibleMoves->begin(), PossibleMoves->end(), make_pair(hE, vE)) != PossibleMoves->end())
						{
							PossibleMoves->push_back(make_pair(hS, vS));
						}
					}*/
					return coords;
				}
			}
		}
	}
	return coords;
}

bool KingLikeKnight(int vStart, int hStart, Colour kingColour)
{
	if (Check(vStart + 1, hStart + 2) && *(board.square[hStart + 2][vStart + 1]->GetName()) == KNIGHT && *(board.square[hStart + 2][vStart + 1]->GetColour()) != kingColour)
		return true;
	if (Check(vStart + 2, hStart + 1) && *(board.square[hStart + 1][vStart + 2]->GetName()) == KNIGHT && *(board.square[hStart + 1][vStart + 2]->GetColour()) != kingColour)
		return true;
	if (Check(vStart + 2, hStart - 1) && *(board.square[hStart - 1][vStart + 2]->GetName()) == KNIGHT && *(board.square[hStart - 1][vStart + 2]->GetColour()) != kingColour)
		return true;
	if (Check(vStart + 1, hStart - 2) && *(board.square[hStart - 2][vStart + 1]->GetName()) == KNIGHT && *(board.square[hStart - 2][vStart + 1]->GetColour()) != kingColour)
		return true;
	if (Check(vStart - 1, hStart - 2) && *(board.square[hStart - 2][vStart - 1]->GetName()) == KNIGHT && *(board.square[hStart - 2][vStart - 1]->GetColour()) != kingColour)
		return true;
	if (Check(vStart - 2, hStart - 1) && *(board.square[hStart - 1][vStart - 2]->GetName()) == KNIGHT && *(board.square[hStart - 1][vStart - 2]->GetColour()) != kingColour)
		return true;
	if (Check(vStart - 2, hStart + 1) && *(board.square[hStart + 1][vStart - 2]->GetName()) == KNIGHT && *(board.square[hStart + 1][vStart - 2]->GetColour()) != kingColour)
		return true;
	if (Check(vStart - 1, hStart + 2) && *(board.square[hStart + 2][vStart - 1]->GetName()) == KNIGHT && *(board.square[hStart + 2][vStart - 1]->GetColour()) != kingColour)
		return true;

	return false;
}

bool CanCut(pair<int, int> coords, int hStart, int vStart, Colour colour)
{
	if (Check(coords.first, coords.second))
	{
		//cout << hStart << ' ' << vStart << endl;
		if (*(board.square[coords.first][coords.second])->GetName() != PAWN)
		{
			vector<pair<int, int>>* PossibleMovis = MakePossibleMoves(board.square[coords.first][coords.second]);
			//cout << (find(PossibleMovis->begin(), PossibleMovis->end(), make_pair(hStart, vStart)) != PossibleMovis->end()) << endl << endl;
			bool check = find(PossibleMovis->begin(), PossibleMovis->end(), make_pair(hStart, vStart)) != PossibleMovis->end();
			//PossibleMovis->clear();
			return (check);
		}
		int tmp = 1;
		if (colour == BLACK)
			tmp *= -1;
		if (hStart + tmp == coords.first && vStart + tmp == coords.second)
			return true;
		if (hStart + tmp == coords.first && vStart - tmp == coords.second)
			return true;
	}
	return false;
}

pair<int, int>* GetEdge(int vStart, int hStart) // axis = 'h' - horizontal == 0, 'v' - vertical == 0
{
	pair<int, int>* A = new pair<int, int>[4];
	for (int i = vStart, j = hStart; i < 8 && i > -1 && j < 8 && j > -1; i++, j++)
		A[0] = make_pair(j, i);
	for (int i = vStart, j = hStart; i < 8 && i > -1 && j < 8 && j > -1; i++, j--)
		A[1] = make_pair(j, i);
	for (int i = vStart, j = hStart; i < 8 && i > -1 && j < 8 && j > -1; i--, j++)
		A[2] = make_pair(j, i);
	for (int i = vStart, j = hStart; i < 8 && i > -1 && j < 8 && j > -1; i--, j--)
		A[3] = make_pair(j, i);
	for (int i = 0; i < 4; i++)
		if (A[i].second == vStart && A[i].first == hStart)
			A[i] = make_pair(-1, -1);
	return A;
}

bool HasCheck(int vStart, int hStart, Colour kingColour) //шах
{
	std::pair<int, int> coords(-1, -1);

	pair<int, int> coord1 = KingLikeRook(coords, vStart, 7, vStart, hStart, kingColour);
	pair<int, int> coord2 = KingLikeRook(coords, vStart, 0, vStart, hStart, kingColour);
	pair<int, int> coord3 = KingLikeRook(coords, 0, hStart, vStart, hStart, kingColour);
	pair<int, int> coord4 = KingLikeRook(coords, 7, hStart, vStart, hStart, kingColour);

	pair<int, int>* A = GetEdge(vStart, hStart);
	/*for (int i = 0; i < 4; ++i)
		cout << A[i].first << " " << A[i].second << endl;
	cout << endl;*/

	pair<int, int> coord5 = KingLikeBishop(coords, A[0].first, A[0].second, vStart, hStart, kingColour);
	pair<int, int> coord6 = KingLikeBishop(coords, A[1].first, A[1].second, vStart, hStart, kingColour);
	pair<int, int> coord7 = KingLikeBishop(coords, A[2].first, A[2].second, vStart, hStart, kingColour);
	pair<int, int> coord8 = KingLikeBishop(coords, A[3].first, A[3].second, vStart, hStart, kingColour);

	if (!CanCut(coord1, hStart, vStart, kingColour) && !CanCut(coord2, hStart, vStart, kingColour) && !CanCut(coord3, hStart, vStart, kingColour)
		&& !CanCut(coord4, hStart, vStart, kingColour) && !CanCut(coord5, hStart, vStart, kingColour) && !CanCut(coord6, hStart, vStart, kingColour)
		&& !CanCut(coord7, hStart, vStart, kingColour) && !CanCut(coord8, hStart, vStart, kingColour) && !KingLikeKnight(vStart, hStart, kingColour))
		return false;

	return true;
}
//рокировка
void MakeCastling(vector<pair<int, int>>& PossibleMoves, int vEnd, int vStart, int hStart)
{
	int sign = -2;
	pair<int, int>& castle = *(board.square[hStart][vStart])->isMackingCastling();
	if (vEnd > vStart)
		sign = 2;
	if (*(board.square[hStart][vEnd]->GetName()) == ROOK)
	{
		if (*(board.square[hStart][vEnd])->getMoveCount() == 0)
		{
			bool allClear = true;
			for (int i = min(vEnd, vStart) + 1; i < max(vEnd, vStart) && allClear; ++i)
			{
				if (*(board.square[hStart][i]->GetName()) != EMPTY)
					allClear = false;
			}
			if (allClear)
			{
				if (sign == -2)
					castle.first = 7;
				else 
					castle.second = 0;
				PossibleMoves.push_back(make_pair(hStart, vStart + sign));
			}
		}
	}
}

void FindPossibleMovesForKing(vector<pair<int, int>>* PossibleMoves, int vStart, int hStart, Colour colour)
{
	if (Check(vStart, hStart + 1) && !HasCheck(vStart, hStart + 1, colour) && *(board.square[hStart + 1][vStart]->GetColour()) != colour)
		PossibleMoves->push_back(make_pair(hStart + 1, vStart));
	if (Check(vStart, hStart - 1) && !HasCheck(vStart, hStart - 1, colour) && *(board.square[hStart - 1][vStart]->GetColour()) != colour)
		PossibleMoves->push_back(make_pair(hStart - 1, vStart));
	if (Check(vStart - 1, hStart) && !HasCheck(vStart - 1, hStart, colour) && *(board.square[hStart][vStart - 1]->GetColour()) != colour)
		PossibleMoves->push_back(make_pair(hStart, vStart - 1));
	if (Check(vStart + 1, hStart) && !HasCheck(vStart + 1, hStart, colour) && *(board.square[hStart][vStart + 1]->GetColour()) != colour)
		PossibleMoves->push_back(make_pair(hStart, vStart + 1));
	if (Check(vStart + 1, hStart + 1) && !HasCheck(vStart + 1, hStart + 1, colour) && *(board.square[hStart + 1][vStart + 1]->GetColour()) != colour)
		PossibleMoves->push_back(make_pair(hStart + 1, vStart + 1));
	if (Check(vStart - 1, hStart + 1) && !HasCheck(vStart - 1, hStart + 1, colour) && *(board.square[hStart + 1][vStart - 1]->GetColour()) != colour)
		PossibleMoves->push_back(make_pair(hStart + 1, vStart - 1));
	if (Check(vStart + 1, hStart - 1) && !HasCheck(vStart + 1, hStart - 1, colour) && *(board.square[hStart - 1][vStart + 1]->GetColour()) != colour)
		PossibleMoves->push_back(make_pair(hStart - 1, vStart + 1));
	if (Check(vStart - 1, hStart - 1) && !HasCheck(vStart - 1, hStart - 1, colour) && *(board.square[hStart - 1][vStart - 1]->GetColour()) != colour)
		PossibleMoves->push_back(make_pair(hStart - 1, vStart - 1));
	//рокировка
		if (*(board.square[hStart][vStart])->getMoveCount() == 0 && !HasCheck(vStart, hStart, colour))
		{
			if (!HasCheck(2, hStart, colour))
				MakeCastling(*PossibleMoves, 0, vStart, hStart);
			if (!HasCheck(6, hStart, colour))
				MakeCastling(*PossibleMoves, 7, vStart, hStart);
		}
}

void funkKnight(vector<pair<int, int>>& PossibleMoves, int vEnd, int hEnd, Colour colour)
{
	if (Check(vEnd, hEnd) && *(board.square[hEnd][vEnd]->GetColour()) != colour /*&& *(board.square[hEnd][vEnd]->GetName()) != KING*/)
		PossibleMoves.push_back(make_pair(hEnd, vEnd));
}

void FindPossibleMovesForKnight(vector<pair<int, int>>& PossibleMoves, int vStart, int hStart, Colour colour)
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

bool KingProtected(pair<int, int> coords, int vStart, int hStart)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			CopySquare[i][j] = board.square[i][j];
	/*for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			cout << *(board.square[i][j]->GetName()) << " ";
		cout << endl;
	}*/
	/*cout << endl;*/
	board.PieceMoving(coords.second, coords.first, vStart, hStart);
	auto colour = *(board.square[coords.first][coords.second]->GetColour());
	pair<int, int> kingCoords;
	if (colour == WHITE)
		kingCoords = WhiteKingCoords;
	else
		kingCoords = BlackKingCoords;
	bool hasCheck = HasCheck(kingCoords.second, kingCoords.first, colour);
	/*for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			cout << *(board.square[i][j]->GetName()) << " ";
		cout << endl;
	}
	cout << endl;*/
	/*cout << hasCheck << endl;
	cout << endl;*/
	//board.PieceMoving(vStart, hStart, coords.second, coords.first);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board.square[i][j] = CopySquare[i][j];
	/*for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			cout << *(board.square[i][j]->GetName()) << " ";
		cout << endl;
	}
	cout << endl;*/
	if (hasCheck)
		return true;
	return false;
}

void funkBishop(vector<pair<int, int>>& PossibleMoves, int vEnd, int hEnd, int vStart, int hStart, Colour colour)
{
	int vsign = 1;
	int hsign = 1;
	if (vEnd < vStart) vsign = -1;
	if (hEnd < hStart) hsign = -1;
	vStart += vsign;
	hStart += hsign;
	std::pair<int, int> coords;
	for (; abs(vStart - vEnd) >= 0 && vStart < 8 && vStart > -1 && hStart < 8 && hStart > -1; vStart += vsign, hStart += hsign)
	{
		if (*(board.square[hStart][vStart]->GetName()) != EMPTY)
		{
			if (*(board.square[hStart][vStart]->GetColour()) != colour /*&& *(board.square[hStart][vStart]->GetName()) != KING*/)
				PossibleMoves.push_back(make_pair(hStart, vStart));
			break;
		}
		PossibleMoves.push_back(make_pair(hStart, vStart));
	}
}

void funkRook(vector<pair<int, int>>& PossibleMoves, int vEnd, int hEnd, int vStart, int hStart, Colour colour)
{
	int sign = 1;
	bool StartisV = true;
	int End = vEnd;
	int Start = vStart;
	if (vEnd == vStart)
	{
		End = hEnd;
		Start = hStart;
		StartisV = false;
	}
	if (End < Start) sign = -1;
	Start += sign;
	for (; abs(Start - End) >= 0 && Start < 8 && Start > -1; Start += sign)
	{

		if (StartisV)
		{
			if (*(board.square[hStart][Start]->GetName()) != EMPTY)
			{
				if (*(board.square[hStart][Start]->GetColour()) != colour /*&& *(board.square[hStart][Start]->GetName()) != KING*/)
					PossibleMoves.push_back(make_pair(hStart, Start));
				break;
			}
			PossibleMoves.push_back(make_pair(hStart, Start));
		}
		else
		{
			if (*(board.square[Start][vStart]->GetName()) != EMPTY)
			{
				if (*(board.square[Start][vStart]->GetColour()) != colour/* && *(board.square[Start][vStart]->GetName()) != KING*/)
					PossibleMoves.push_back(make_pair(Start, vStart));
				break;
			}
			PossibleMoves.push_back(make_pair(Start, vStart));
		}
	}
}

void FindPossibleMovesForRook(vector<pair<int, int>>& PossibleMoves, int vStart, int hStart, Colour colour)
{
	funkRook(PossibleMoves, vStart, 7, vStart, hStart, colour);
	funkRook(PossibleMoves, vStart, 0, vStart, hStart, colour);
	funkRook(PossibleMoves, 0, hStart, vStart, hStart, colour);
	funkRook(PossibleMoves, 7, hStart, vStart, hStart, colour);
}

void FindPossibleMovesForBishop(vector<pair<int, int>>& PossibleMoves, int vStart, int hStart, Colour colour)
{
	pair<int, int>* A = GetEdge(vStart, hStart);
	for (int i = 0; i < 4; i++)
		funkBishop(PossibleMoves, A[i].second, A[i].first, vStart, hStart, colour);
}

void FindPossibleMovesForQueen(vector<pair<int, int>>& PossibleMoves, int vStart, int hStart, Colour colour)
{
	FindPossibleMovesForRook(PossibleMoves, vStart, hStart, colour);
	FindPossibleMovesForBishop(PossibleMoves, vStart, hStart, colour);
}

void FindPossibleMovesForPawn(vector<pair<int, int>>* PossibleMoves, int vStart, int hStart, Colour colour, int MoveCount)
{
	bool canMove = true;
	int tmp = 1;
	int side = 4;
	if (colour == BLACK)
	{
		tmp *= -1;
		side = 3;
	}
	bool clear = false; //изменение
	if (canMove && Check(vStart, hStart + tmp) && *(board.square[hStart + tmp][vStart]->GetColour()) == NONE /*&& *(board.square[hStart + tmp][vStart]->GetName()) != KING*/)
	{
		PossibleMoves->push_back(make_pair(hStart + tmp, vStart));
		clear = true;
		if (KingProtected(make_pair(hStart + tmp, vStart), vStart, hStart))
		{
			canMove = false;
			PossibleMoves->clear();
		}
	}
	if (canMove && Check(vStart + tmp, hStart + tmp) && *(board.square[hStart + tmp][vStart + tmp]->GetColour()) != NONE && (*(board.square[hStart + tmp][vStart + tmp]->GetColour())) != colour /*&& *(board.square[hStart + tmp][vStart + tmp]->GetName()) != KING*/)
	{
		PossibleMoves->push_back(make_pair(hStart + tmp, vStart + tmp));
		if (KingProtected(make_pair(hStart + tmp, vStart + tmp), vStart, hStart))
		{
			canMove = false;
			PossibleMoves->clear();
		}
	}
	if (canMove && Check(vStart - tmp, hStart + tmp) && *(board.square[hStart + tmp][vStart - tmp]->GetColour()) != NONE && (*(board.square[hStart + tmp][vStart - tmp]->GetColour())) != colour /*&& *(board.square[hStart + tmp][vStart - tmp]->GetName()) != KING*/)
	{
		PossibleMoves->push_back(make_pair(hStart + tmp, vStart - tmp));
		if (KingProtected(make_pair(hStart + tmp, vStart - tmp), vStart, hStart))
		{
			canMove = false;
			PossibleMoves->clear();
		}
	}
	if (canMove && MoveCount == 0 && clear)
	{
		tmp *= 2;
		if (*(board.square[hStart + tmp][vStart]->GetColour()) == NONE /*&& *(board.square[hStart + tmp][vStart]->GetName()) != KING*/)
		{
			PossibleMoves->push_back(make_pair(hStart + tmp, vStart));
			if (KingProtected(make_pair(hStart + tmp, vStart), vStart, hStart))
			{
				canMove = false;
				PossibleMoves->clear();
			}
		}
	}
	//взятие на проходе
	if (canMove && side == hStart && Check(vStart + 1, hStart) && *(board.square[hStart][vStart + 1]->GetName()) == PAWN && hasMadeMove.first == hStart && hasMadeMove.second == vStart + 1)
	{
		
		if (*(board.square[hStart][vStart + 1])->getMoveCount() == 1)
		{
			PossibleMoves->push_back(make_pair(hStart + tmp, vStart + 1));
			*(board.square[hStart][vStart])->isCaptureEnPassant() = make_pair(hStart, vStart + 1);
		}
	}
	else if (canMove && side == hStart && Check(vStart - 1, hStart) && *(board.square[hStart][vStart - 1]->GetName()) == PAWN && hasMadeMove.first == hStart && hasMadeMove.second == vStart-1)
	{
		if (*(board.square[hStart][vStart - 1])->getMoveCount() == 1)
		{
			PossibleMoves->push_back(make_pair(hStart + tmp, vStart - 1));
			*(board.square[hStart][vStart])->isCaptureEnPassant() = make_pair(hStart, vStart - 1);
		}
	}
	else *(board.square[hStart][vStart])->isCaptureEnPassant() = make_pair(-1, -1);
}

vector<pair<int, int>>* MakePossibleMoves(Piece* piece)
{
	vector<pair<int, int>>* vector1 = piece->GetPossibleMoves();
	Colour* colour = piece->GetColour();
	int* hor = piece->GetHor();
	int* vert = piece->GetVert();
	TypePiece* type = piece->GetName();
	vector1->clear();
	switch (*type)
	{
	case (KING):
		FindPossibleMovesForKing(vector1, *vert, *hor, *colour);
		return piece->GetPossibleMoves();
	case (QUEEN):
		FindPossibleMovesForQueen(*vector1, *vert, *hor, *colour);
		return piece->GetPossibleMoves();
	case(BISHOP):
		FindPossibleMovesForBishop(*vector1, *vert, *hor, *colour);
		return piece->GetPossibleMoves();
	case(KNIGHT):
		FindPossibleMovesForKnight(*vector1, *vert, *hor, *colour);
		return piece->GetPossibleMoves();
	case(ROOK):
		FindPossibleMovesForRook(*vector1, *vert, *hor, *colour);
		return piece->GetPossibleMoves();
	case(PAWN):
		FindPossibleMovesForPawn(vector1, *vert, *hor, *colour, *(piece->getMoveCount()));
		return piece->GetPossibleMoves();
	case (EMPTY):
		return vector1;
	}
}

void Board::SetSquare(int hor, int vert)
{

}

void TurningAPawn()
{

}

bool Board::move(int vert, int hor, Colour col, Piece* piece)
{
	Colour* colour = piece->GetColour();
	TypePiece* type = piece->GetName();
	auto PossibleMoves = piece->GetPossibleMoves();
	bool* canMove = piece->GetCanMove();
	int* vertical = piece->GetVert();
	int* horizontal = piece->GetHor();
	int* MoveCount = piece->getMoveCount();
	switch (*type)
	{
	case (KING):
		FindPossibleMovesForKing(PossibleMoves, *vertical, *horizontal, *colour);
		if (col == NONE && Check(vert, hor) && CanMakeMove(*PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			board.PieceMoving(vert, hor, *vertical, *horizontal);
			//перемещение ладьи при рокировке
			if (abs(*vertical - vert) > 1)
			{
				pair<int, int>* castle = piece->isMackingCastling();
				if ((*castle).first == 7 && *vertical - vert == 2)
					board.PieceMoving(3, *horizontal, 0, *horizontal);
				else if ((*castle).second == 0 && *vertical - vert == -2)
					board.PieceMoving(5, *horizontal, 7, *horizontal);
			}
			*horizontal = hor;
			*vertical = vert;
			*MoveCount += 1;
			//изменение в каждом
			hasMadeMove = make_pair(*horizontal, *vertical);
			if (*colour == WHITE)
				WhiteKingCoords = make_pair(hor, vert);
			else
				BlackKingCoords = make_pair(hor, vert);
			return true;
		}
		return false;
	case (QUEEN):
		FindPossibleMovesForQueen(*PossibleMoves, *vertical, *horizontal, *colour);
		if (col == NONE && Check(vert, hor) && CanMakeMove(*PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			board.PieceMoving(vert, hor, *vertical, *horizontal);
			*horizontal = hor;
			*vertical = vert;
			*MoveCount += 1;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
	case(BISHOP):
		FindPossibleMovesForBishop(*PossibleMoves, *vertical, *horizontal, *colour);
		if (col == NONE && Check(vert, hor) && CanMakeMove(*PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			board.PieceMoving(vert, hor, *vertical, *horizontal);
			*horizontal = hor;
			*vertical = vert;
			*MoveCount += 1;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
	case(KNIGHT):
		FindPossibleMovesForKnight(*PossibleMoves, *vertical, *horizontal, *colour);
		if (col == NONE && Check(vert, hor) && CanMakeMove(*PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			board.PieceMoving(vert, hor, *vertical, *horizontal);
			*horizontal = hor;
			*vertical = vert;
			*MoveCount += 1;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
	case(ROOK):
		FindPossibleMovesForRook(*PossibleMoves, *(piece->GetVert()), *(piece->GetHor()), *colour);
		if (canMove && col == NONE && Check(vert, hor) && CanMakeMove(*PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			board.PieceMoving(vert, hor, *vertical, *horizontal);
			*horizontal = hor;
			*vertical = vert;
			*MoveCount += 1;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
	case(PAWN):
		FindPossibleMovesForPawn(PossibleMoves, *vertical, *horizontal, *colour, *MoveCount);
		if (col == NONE && Check(vert, hor) && CanMakeMove(*PossibleMoves, *canMove, make_pair(hor, vert)))//-Check -col
		{
			//взятие на проходе
			pair<int, int> captureEnPassant = *(board.square[*horizontal][*vertical])->isCaptureEnPassant();
			if (captureEnPassant.first == *horizontal && captureEnPassant.second == vert)
			{
				int sign = 1;
				if (*colour == BLACK)
					sign = -1;
				SetPiece(NONE, *horizontal, vert, EMPTY);
			}
			board.PieceMoving(vert, hor, *vertical, *horizontal);
			*vertical = vert;
			*horizontal = hor;
			*MoveCount += 1;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
	case (EMPTY):
		return false;
	}
}

bool Board::cut_down(int vert, int hor, Colour col, Piece* piece)
{
	Colour* colour = piece->GetColour();
	TypePiece* type = piece->GetName();
	auto PossibleMoves = *(piece->GetPossibleMoves());
	bool* canMove = piece->GetCanMove();
	int* vertical = piece->GetVert();
	int* horizontal = piece->GetHor();
	int* MoveCount = piece->getMoveCount();
	int vsign = 1;
	int hsign = 1;
	switch (*type)
	{
	case (KING):
		FindPossibleMovesForKing(&PossibleMoves, *vertical, *horizontal, *colour);
		if (*colour != col && CanMakeMove(PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			int newHor = hor;
			int newVert = vert;
			board.PieceMoving(vert, hor, *vertical, *horizontal);
			*horizontal = newHor;
			*vertical = newVert;
			*MoveCount += 1;
			hasMadeMove = make_pair(*horizontal, *vertical);
			if (*colour == WHITE)
				WhiteKingCoords = make_pair(newHor, newVert);
			else
				BlackKingCoords = make_pair(newHor, newVert);
			return true;
		}
		return false;
	case (QUEEN):
		if (vert < *vertical) vsign = -1;
		if (vert == *vertical) vsign = 0;
		if (hor < *horizontal) hsign = -1;
		if (hor == *horizontal) hsign = 0;
		FindPossibleMovesForQueen(PossibleMoves, *vertical, *horizontal, *colour);
		if (*colour != col && CanMakeMove(PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			int newHor = hor;
			int newVert = vert;
			board.PieceMoving(vert, hor, *vertical, *horizontal);
			*horizontal = newHor;
			*vertical = newVert;
			*MoveCount += 1;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
	case(BISHOP):
		if (vert < *vertical) vsign = -1;
		if (hor < *horizontal) hsign = -1;
		//PossibleMoves.clear();
		FindPossibleMovesForBishop(PossibleMoves, *vertical, *horizontal, *colour);
		if (*colour != col && CanMakeMove(PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			int newHor = hor;
			int newVert = vert;
			board.PieceMoving(vert, hor, *vertical, *horizontal);
			*horizontal = newHor;
			*vertical = newVert;
			*MoveCount += 1;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
	case(KNIGHT):
		FindPossibleMovesForKnight(PossibleMoves, *vertical, *horizontal, *colour);
		if (*colour != col && CanMakeMove(PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			int newHor = hor;
			int newVert = vert;
			board.PieceMoving(vert, hor, *vertical, *horizontal);
			*horizontal = newHor;
			*vertical = newVert;
			*MoveCount += 1;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
	case(ROOK):
		if (vert < *vertical) vsign = -1;
		if (vert == *vertical) vsign = 0;
		if (hor < *horizontal) hsign = -1;
		if (hor == *horizontal) hsign = 0;
		//PossibleMoves.clear();
		FindPossibleMovesForRook(PossibleMoves, *vertical, *horizontal, *colour);
		if (*colour != col && CanMakeMove(PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			int newHor = hor;
			int newVert = vert;
			board.PieceMoving(vert, hor, *vertical, *horizontal);
			*horizontal = newHor;
			*vertical = newVert;
			*MoveCount += 1;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
	case(PAWN):
		FindPossibleMovesForPawn(&PossibleMoves, *vertical, *horizontal, *colour, *MoveCount);
		if (*colour != col && CanMakeMove(PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			int newHor = hor;
			int newVert = vert;
			board.PieceMoving(vert, hor, *vertical, *horizontal);
			*horizontal = newHor;
			*vertical = newVert;
			*MoveCount += 1;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
	case (EMPTY):
		return false;
	}
}