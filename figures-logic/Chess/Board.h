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
vector<pair<int, int>>* MakePossibleMoves(Piece* piece, bool Mode);

pair<int, int> hasMadeMove;
class Board
{ // Piece
public:
	int figures_count = 0;
	Piece* square[8][8];
	Board();
	void SetBoard(); // изначальное положение доски
	void SetPiece(Colour colour, int hor, int vert, TypePiece type, int moveCount); // поставить фигуру, либо удалить её, если Empty
	void PieceMoving(int vEnd, int hEnd, int vStart, int hStart, int moveCount);
	bool move(int vert, int hor, Colour col, Piece* piece);
	bool cut_down(int vert, int hor, Colour col, Piece* piece);
};

Board::Board() { SetBoard(); }

void Board::SetBoard()
{
	for (int i = 0; i < 8; i++)
	{
		Colour colour = NONE;
		if (i < 2) colour = WHITE;//AHAHAHAHHA
		if (i > 5) colour = BLACK;
		if (i == 0 || i == 7)
		{
			square[i][0] = new Rook(colour, 0, i, ROOK, 0);
			square[i][1] = new Knight(colour, 1, i, KNIGHT, 0);
			square[i][2] = new Bishop(colour, 2, i, BISHOP, 0);
			square[i][3] = new Queen(colour, 3, i, QUEEN, 0);
			square[i][4] = new King(colour, 4, i, KING, 0);
			square[i][5] = new Bishop(colour, 5, i, BISHOP, 0);
			square[i][6] = new Knight(colour, 6, i, KNIGHT, 0);
			square[i][7] = new Rook(colour, 7, i, ROOK, 0);
		}
		else
		{
			for (int j = 0; j < 8; j++)
				if (i == 1 || i == 6)
					square[i][j] = new Pawn(colour, j, i, PAWN, 0);
				else
					square[i][j] = new Piece(colour, j, i, EMPTY, 0);
		}
	}
	/*for (int i = 8; i< 12; i++)
		for (int j = 0; j < 8; j++)
			square[i][j] = new Piece(NONE, j, i, EMPTY);


	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			square[i][j] = new Piece(NONE, j, i, EMPTY);
	square[4][3] = new Rook(WHITE, 3, 4, ROOK);
	square[4][1] = new Queen(BLACK, 1, 4, QUEEN);
	square[4][4] = new King(WHITE, 4, 4, KING);*/
	/*square[5][1] = new King(BLACK, 4, 7, KING);*/

}
Board board;

void Board::SetPiece(Colour colour, int hor, int vert, TypePiece type, int moveCount)
{
	/*for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << *(board.square[i][j]->GetName()) << " ";
		}
		cout << endl;
	}
	cout << endl;*/
	switch (type)
	{
	case (KING):
		board.square[hor][vert] = new King(colour, vert, hor, KING, moveCount);
		break;
	case (QUEEN):
		board.square[hor][vert] = new Queen(colour, vert, hor, QUEEN, moveCount);
		break;
	case(BISHOP):
		board.square[hor][vert] = new Bishop(colour, vert, hor, BISHOP, moveCount);
		break;
	case(KNIGHT):
		board.square[hor][vert] = new Knight(colour, vert, hor, KNIGHT, moveCount);
		break;
	case(ROOK):
		board.square[hor][vert] = new Rook(colour, vert, hor, ROOK, moveCount);
		break;
	case(PAWN):
		board.square[hor][vert] = new Pawn(colour, vert, hor, PAWN, moveCount);
		break;
	case (EMPTY):
		board.square[hor][vert] = new Piece(NONE, vert, hor, EMPTY, moveCount);
		break;
	}
}

pair<int, int> WhiteKingCoords = make_pair(0, 4); // НЕ ЗАБУДЬ ВЕРНУТЬ НА (0, 4)
pair<int, int> BlackKingCoords = make_pair(7, 4);

Board* CreateBoard()
{
	return &board;
}

void Board::PieceMoving(int vEnd, int hEnd, int vStart, int hStart, int moveCount)
{
	SetPiece(*(square[hStart][vStart]->GetColour()), hEnd, vEnd, *(square[hStart][vStart]->GetName()), moveCount);
	SetPiece(NONE, hStart, vStart, EMPTY, -1);
}

bool CanMakeMove(vector<pair<int, int>>& PossibleMoves, bool& CanMove, pair<int, int> coords)
{
	if (PossibleMoves.empty())
	{
		CanMove = false;
		return false;
	}
	CanMove = true;
	return (find(PossibleMoves.begin(), PossibleMoves.end(), coords) != PossibleMoves.end());
}

pair<int, int> KingLikeBishop(pair<int, int> coords, int vEnd, int hEnd, int vStart, int hStart, Colour kingColour)
{
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
	for (; abs(vStart - vEnd) >= 0 && vStart < 8 && vStart > -1 && hStart < 8 && hStart > -1; vStart += vsign, hStart += hsign)
	{
		if (*(board.square[hStart][vStart]->GetName()) == BISHOP || *(board.square[hStart][vStart]->GetName()) == QUEEN)
		{
			if (*(board.square[hStart][vStart]->GetColour()) != kingColour)
			{
				coords.first = hStart;
				coords.second = vStart;
				return coords;
			}
			else if (*(board.square[hStart][vStart]->GetColour()) == kingColour)
				return coords;
		}
	}
	return coords;
}

pair<int, int> KingLikeRook(pair<int, int> coords, int vEnd, int hEnd, int vStart, int hStart, Colour kingColour)
{
	//cout << vEnd << hEnd << vStart << hStart << endl;
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
		//cout << "ABOBA" << endl;
		if (StartisV)
		{
			//cout << *(board.square[hStart][Start]->GetName()) << endl;
			if (*(board.square[hStart][Start]->GetName()) == ROOK || *(board.square[hStart][Start]->GetName()) == QUEEN)
			{
				
				if (*(board.square[hStart][Start]->GetColour()) != kingColour)
				{
					
					//cout << hStart << " " << vStart << endl;
					coords.first = hStart;
					coords.second = Start;
					//cout << coords.first << " " << coords.second << endl;
					return coords;
				}
			}
		}
		else
		{
			//cout << *(board.square[Start][vStart]->GetName()) << endl;
			if (*(board.square[Start][vStart]->GetName()) == ROOK || *(board.square[Start][vStart]->GetName()) == QUEEN)
			{
				
				if (*(board.square[Start][vStart]->GetColour()) != kingColour)
				{
					
					coords.first = Start;
					coords.second = vStart;
					return coords;
				}
			}
		}
	}
	//cout << endl;
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

void KingProtected(pair<int, int> coords, int vStart, int hStart, vector<pair<int, int>>* PossibleMoves);

void funkKnight(vector<pair<int, int>>* PossibleMoves, int vEnd, int hEnd, int vStart, int hStart, Colour colour, bool mode)
{
	if (Check(vEnd, hEnd) && *(board.square[hEnd][vEnd]->GetColour()) != colour)
	{
		PossibleMoves->push_back(make_pair(hEnd, vEnd));
		if (mode)
			KingProtected(make_pair(hEnd, vEnd), vStart, hStart, PossibleMoves);
	}
}

void funkBishop(vector<pair<int, int>>* PossibleMoves, int vEnd, int hEnd, int vStart, int hStart, Colour colour, bool mode) // mode = true, если просто проверка ходов, mode = false, если внутри cancut
{
	int startH = hStart; // не надо
	int startV = vStart; // не надо
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
			if (*(board.square[hStart][vStart]->GetColour()) != colour) //&& *(board.square[hStart][vStart]->GetName()) != KING)
			{
				PossibleMoves->push_back(make_pair(hStart, vStart));
				if (mode) // не надо
					KingProtected(make_pair(hStart, vStart), startV, startH, PossibleMoves);
			}
			
			break;
		}
		PossibleMoves->push_back(make_pair(hStart, vStart));
		if (mode) // не надо
			KingProtected(make_pair(hStart, vStart), startV, startH, PossibleMoves);
	}
}

void funkRook(vector<pair<int, int>>* PossibleMoves, int vEnd, int hEnd, int vStart, int hStart, Colour colour, bool mode)
{
	if (Check(vEnd, hEnd) && Check(vStart, hStart))
	{
		int startV = vStart, startH = hStart;
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
					if (*(board.square[hStart][Start]->GetColour()) != colour) //&& *(board.square[hStart][Start]->GetName()) != KING)
					{
						PossibleMoves->push_back(make_pair(hStart, Start));
						if (mode)
							KingProtected(make_pair(hStart, Start), startV, startH, PossibleMoves);
					}
					break;
				}
				PossibleMoves->push_back(make_pair(hStart, Start));
				if (mode)
					KingProtected(make_pair(hStart, Start), startV, startH, PossibleMoves);
			}
			else
			{
				if (*(board.square[Start][vStart]->GetName()) != EMPTY)
				{
					if (*(board.square[Start][vStart]->GetColour()) != colour) //&& *(board.square[Start][vStart]->GetName()) != KING)
					{
						PossibleMoves->push_back(make_pair(Start, vStart));
						if (mode)
							KingProtected(make_pair(Start, vStart), startV, startH, PossibleMoves);
					}
					break;
				}
				PossibleMoves->push_back(make_pair(Start, vStart));
				if (mode)
					KingProtected(make_pair(Start, vStart), startV, startH, PossibleMoves);
			}
		}
	}

}

bool HasCheck(int vStart, int hStart, Colour kingColour, bool mode);

bool CanCut(pair<int, int> coords, int hStart, int vStart, Colour colour, bool mode) // mode - работа с possible moves, false - с его копией
{
	if (Check(coords.first, coords.second))
	{
		auto type = *(board.square[coords.first][coords.second])->GetName();
		auto colour = *(board.square[coords.first][coords.second])->GetColour();
		if (type != PAWN)
		{
			//cout << *(board.square[coords.first][coords.second]->GetName()) << endl;
			vector<pair<int, int>> PossibleMovis = *(board.square[coords.first][coords.second]->GetPossibleMoves());
			if (type == KNIGHT)
				funkKnight(&PossibleMovis, vStart, hStart, coords.second, coords.first, colour, false);
			else
			{
				if (type == QUEEN || type == ROOK)
					funkRook(&PossibleMovis, vStart, hStart, coords.second, coords.first, colour, false);
				if (type == QUEEN || type == BISHOP)
					funkBishop(&PossibleMovis, vStart, hStart, coords.second, coords.first, colour, false);
			}
			return (find(PossibleMovis.begin(), PossibleMovis.end(), make_pair(hStart, vStart)) != PossibleMovis.end());
		}
		int tmp = 1;
		if (colour == BLACK)
			tmp *= -1;
		if (hStart == coords.first + tmp && vStart == coords.second + tmp)
			return true;
		if (hStart == coords.first + tmp && vStart == coords.second - tmp)
			return true;
		return false;
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
	return A; // координаты крайних точек диагоналей
}

bool HasCheck(int vStart, int hStart, Colour kingColour, bool mode) //шах
{
	std::pair<int, int> coords(-1, -1); // King = (4, 4): (0, 4), (7, 4), //(4, 0), //(4, 7)

	//cout << vStart << " " << hStart << endl;
	pair<int, int> coord1 = KingLikeRook(coords, vStart, 7, vStart, hStart, kingColour);
	pair<int, int> coord2 = KingLikeRook(coords, vStart, 0, vStart, hStart, kingColour);
	pair<int, int> coord3 = KingLikeRook(coords, 0, hStart, vStart, hStart, kingColour);
	pair<int, int> coord4 = KingLikeRook(coords, 7, hStart, vStart, hStart, kingColour);

	pair<int, int>* A = GetEdge(vStart, hStart);

	pair<int, int> coord5 = KingLikeBishop(coords, A[0].first, A[0].second, vStart, hStart, kingColour);
	pair<int, int> coord6 = KingLikeBishop(coords, A[1].first, A[1].second, vStart, hStart, kingColour);
	pair<int, int> coord7 = KingLikeBishop(coords, A[2].first, A[2].second, vStart, hStart, kingColour);
	pair<int, int> coord8 = KingLikeBishop(coords, A[3].first, A[3].second, vStart, hStart, kingColour);

	if (!CanCut(coord1, hStart, vStart, kingColour, mode) && !CanCut(coord2, hStart, vStart, kingColour, mode) && !CanCut(coord3, hStart, vStart, kingColour, mode)
		&& !CanCut(coord4, hStart, vStart, kingColour, mode) && !CanCut(coord5, hStart, vStart, kingColour, mode) && !CanCut(coord6, hStart, vStart, kingColour, mode)
		&& !CanCut(coord7, hStart, vStart, kingColour, mode) && !CanCut(coord8, hStart, vStart, kingColour, mode) && !KingLikeKnight(vStart, hStart, kingColour))
	{
		/*cout << CanCut(coord1, hStart, vStart, kingColour) << endl;
		cout << CanCut(coord2, hStart, vStart, kingColour) << endl;
		cout << CanCut(coord3, hStart, vStart, kingColour) << endl;
		cout << CanCut(coord4, hStart, vStart, kingColour) << endl;
		cout << CanCut(coord5, hStart, vStart, kingColour) << endl;
		cout << CanCut(coord6, hStart, vStart, kingColour) << endl;
		cout << CanCut(coord7, hStart, vStart, kingColour) << endl;
		cout << CanCut(coord8, hStart, vStart, kingColour) << endl;
		cout << KingLikeKnight(vStart, hStart, kingColour) << endl;*/

		/*for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
				cout << *(board.square[i][j]->GetName()) << " ";
			cout << endl;
		}
		cout << endl;*/
		
		return false;
	}
	return true;
}

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

void KingProtected(pair<int, int> coords, int vStart, int hStart, vector<pair<int, int>>* PossibleMoves)
{	
	if (coords.first != hStart || coords.second != vStart)
	{
		Piece*** Copy = new Piece **[8];
		for (int i = 0; i < 8; i++)
		{
			Copy[i] = new Piece * [8];
			for (int j = 0; j < 8; j++)
				Copy[i][j] = board.square[i][j];
		}

		board.SetPiece(*(board.square[hStart][vStart]->GetColour()), coords.first, coords.second, *(board.square[hStart][vStart]->GetName()), *(board.square[hStart][vStart]->getMoveCount()));
		board.SetPiece(NONE, hStart, vStart, EMPTY, -1);

		/*if (*(board.square[coords.first][coords.second]->GetName()) == KING)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					cout << *(board.square[i][j]->GetName()) << " ";
				}
				cout << endl;
			}
			cout << coords.first << coords.second << endl;
			cout << endl;
		}*/
		auto colour = *(board.square[coords.first][coords.second]->GetColour());
		pair<int, int> kingCoords;
		if (colour == WHITE)
			kingCoords = WhiteKingCoords;
		else
			kingCoords = BlackKingCoords;
		if (*(board.square[coords.first][coords.second]->GetName()) == KING)
			kingCoords = coords;
		bool hasCheck = HasCheck(kingCoords.second, kingCoords.first, colour, 0);
		//cout << hasCheck << endl;

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
				board.square[i][j] = Copy[i][j];
			delete[] Copy[i];
		}
		/*for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << *(board.square[i][j]->GetName()) << " ";
			}
			cout << endl;
		}
		cout << coords.first << coords.second << endl;
		cout << endl;*/
		if (hasCheck)
			PossibleMoves->pop_back();
	}
}

void FindPossibleMovesForKing(vector<pair<int, int>>* PossibleMoves, int vStart, int hStart, Colour colour)
{
	if (Check(vStart, hStart + 1) && *(board.square[hStart + 1][vStart]->GetColour()) != colour) // !HasCheck(vStart, hStart + 1, colour, mode) && 
	{
		PossibleMoves->push_back(make_pair(hStart + 1, vStart));
		KingProtected(make_pair(hStart + 1, vStart), vStart, hStart, PossibleMoves);
	}
	if (Check(vStart, hStart - 1) && *(board.square[hStart - 1][vStart]->GetColour()) != colour) // !HasCheck(vStart, hStart - 1, colour, mode) &&
	{
		PossibleMoves->push_back(make_pair(hStart - 1, vStart));
		KingProtected(make_pair(hStart - 1, vStart), vStart, hStart, PossibleMoves);
	}
	if (Check(vStart - 1, hStart) && *(board.square[hStart][vStart - 1]->GetColour()) != colour) //  !HasCheck(vStart - 1, hStart, colour, mode) && 
	{
		PossibleMoves->push_back(make_pair(hStart, vStart - 1));
		KingProtected(make_pair(hStart, vStart - 1), vStart, hStart, PossibleMoves);
	}
	if (Check(vStart + 1, hStart) && *(board.square[hStart][vStart + 1]->GetColour()) != colour) // !HasCheck(vStart + 1, hStart, colour, mode) && 
	{
		PossibleMoves->push_back(make_pair(hStart, vStart + 1));
		KingProtected(make_pair(hStart, vStart + 1), vStart, hStart, PossibleMoves);
	}
	if (Check(vStart + 1, hStart + 1) && *(board.square[hStart + 1][vStart + 1]->GetColour()) != colour) //!HasCheck(vStart + 1, hStart + 1, colour, mode) && 
	{
		PossibleMoves->push_back(make_pair(hStart + 1, vStart + 1));
		KingProtected(make_pair(hStart + 1, vStart + 1), vStart, hStart, PossibleMoves);
	}
	if (Check(vStart - 1, hStart + 1) && *(board.square[hStart + 1][vStart - 1]->GetColour()) != colour) //!HasCheck(vStart - 1, hStart + 1, colour, mode) && 
	{
		PossibleMoves->push_back(make_pair(hStart + 1, vStart - 1));
		KingProtected(make_pair(hStart + 1, vStart - 1), vStart, hStart, PossibleMoves);
	}
	if (Check(vStart + 1, hStart - 1) && *(board.square[hStart - 1][vStart + 1]->GetColour()) != colour) //!HasCheck(vStart + 1, hStart - 1, colour, mode) && 
	{
		PossibleMoves->push_back(make_pair(hStart - 1, vStart + 1));
		KingProtected(make_pair(hStart - 1, vStart + 1), vStart, hStart, PossibleMoves);
	}
	if (Check(vStart - 1, hStart - 1) && *(board.square[hStart - 1][vStart - 1]->GetColour()) != colour)//HasCheck(vStart - 1, hStart - 1, colour, mode) && 
	{
		PossibleMoves->push_back(make_pair(hStart - 1, vStart - 1));
		KingProtected(make_pair(hStart - 1, vStart - 1), vStart, hStart, PossibleMoves);
	}
	if (*(board.square[hStart][vStart])->getMoveCount() == 0 && !HasCheck(vStart, hStart, colour, true))// исправить
	{
		if (!HasCheck(2, hStart, colour, true))
			MakeCastling(*PossibleMoves, 0, vStart, hStart);
		if (!HasCheck(6, hStart, colour, true))
			MakeCastling(*PossibleMoves, 7, vStart, hStart);
	}
}

void FindPossibleMovesForKnight(vector<pair<int, int>>* PossibleMoves, int vStart, int hStart, Colour colour)
{
	funkKnight(PossibleMoves, vStart - 1, hStart - 2, vStart, hStart, colour, true);
	funkKnight(PossibleMoves, vStart - 1, hStart + 2, vStart, hStart, colour, true);
	funkKnight(PossibleMoves, vStart + 1, hStart - 2, vStart, hStart, colour, true);
	funkKnight(PossibleMoves, vStart + 1, hStart + 2, vStart, hStart, colour, true);
	funkKnight(PossibleMoves, vStart - 2, hStart - 1, vStart, hStart, colour, true);
	funkKnight(PossibleMoves, vStart - 2, hStart + 1, vStart, hStart, colour, true);
	funkKnight(PossibleMoves, vStart + 2, hStart - 1, vStart, hStart, colour, true);
	funkKnight(PossibleMoves, vStart + 2, hStart + 1, vStart, hStart, colour, true);
}

void FindPossibleMovesForRook(vector<pair<int, int>>* PossibleMoves, int vStart, int hStart, Colour colour)
{
	funkRook(PossibleMoves, vStart, 7, vStart, hStart, colour, true); // тут может быть больше 1 клетки
	funkRook(PossibleMoves, vStart, 0, vStart, hStart, colour, true);
	funkRook(PossibleMoves, 0, hStart, vStart, hStart, colour, true);
	funkRook(PossibleMoves, 7, hStart, vStart, hStart, colour, true);
}

void FindPossibleMovesForBishop(vector<pair<int, int>>* PossibleMoves, int vStart, int hStart, Colour colour)
{
	pair<int, int>* A = GetEdge(vStart, hStart);
	for (int i = 0; i < 4; i++)
		if (Check(A[i].second, A[i].first)) // проерка корректности координат 
			funkBishop(PossibleMoves, A[i].second, A[i].first, vStart, hStart, colour, true);
}

void FindPossibleMovesForQueen(vector<pair<int, int>>* PossibleMoves, int vStart, int hStart, Colour colour)
{
	FindPossibleMovesForRook(PossibleMoves, vStart, hStart, colour);
	FindPossibleMovesForBishop(PossibleMoves, vStart, hStart, colour);
}

void FindPossibleMovesForPawn(vector<pair<int, int>>* PossibleMoves, int vStart, int hStart, Colour colour, int MoveCount)
{
	int tmp = 1;
	int side = 4;
	if (colour == BLACK)
	{
		tmp *= -1;
		side = 3;
	}
	bool clear = false;
	if (Check(vStart, hStart + tmp) && *(board.square[hStart + tmp][vStart]->GetColour()) == NONE) //&& *(board.square[hStart + tmp][vStart]->GetName()) != KING)
	{
		PossibleMoves->push_back(make_pair(hStart + tmp, vStart));
		KingProtected(make_pair(hStart + tmp, vStart), vStart, hStart, PossibleMoves);
	}
	if (Check(vStart + tmp, hStart + tmp) && *(board.square[hStart + tmp][vStart + tmp]->GetColour()) != NONE && (*(board.square[hStart + tmp][vStart + tmp]->GetColour())) != colour) //&& *(board.square[hStart + tmp][vStart + tmp]->GetName()) != KING)
	{
		PossibleMoves->push_back(make_pair(hStart + tmp, vStart + tmp));
		KingProtected(make_pair(hStart + tmp, vStart + tmp), vStart, hStart, PossibleMoves);
		
	}
	if (Check(vStart - tmp, hStart + tmp) && *(board.square[hStart + tmp][vStart - tmp]->GetColour()) != NONE && (*(board.square[hStart + tmp][vStart - tmp]->GetColour())) != colour) //&& *(board.square[hStart + tmp][vStart - tmp]->GetName()) != KING)
	{
		PossibleMoves->push_back(make_pair(hStart + tmp, vStart - tmp));
		KingProtected(make_pair(hStart + tmp, vStart - tmp), vStart, hStart, PossibleMoves);
		
	}
	if (MoveCount == 0)
	{
		//cout << *(board.square[hStart][vStart]->getMoveCount()) << endl;
		tmp *= 2;
		if (*(board.square[hStart + tmp][vStart]->GetColour()) == NONE)// && *(board.square[hStart + tmp][vStart]->GetName()) != KING)
		{
			PossibleMoves->push_back(make_pair(hStart + tmp, vStart));
			KingProtected(make_pair(hStart + tmp, vStart), vStart, hStart, PossibleMoves);
		}
	}
	if (PossibleMoves->size() != 0 && side == hStart && Check(vStart + 1, hStart) && *(board.square[hStart][vStart + 1]->GetName()) == PAWN && hasMadeMove.first == hStart && hasMadeMove.second == vStart + 1)
	{

		if (*(board.square[hStart][vStart + 1])->getMoveCount() == 1)
		{
			PossibleMoves->push_back(make_pair(hStart + tmp, vStart + 1));
			*(board.square[hStart][vStart])->isCaptureEnPassant() = make_pair(hStart, vStart + 1);
		}
	}
	else if (PossibleMoves->size() != 0 && side == hStart && Check(vStart - 1, hStart) && *(board.square[hStart][vStart - 1]->GetName()) == PAWN && hasMadeMove.first == hStart && hasMadeMove.second == vStart - 1)
	{
		if (*(board.square[hStart][vStart - 1])->getMoveCount() == 1)
		{
			PossibleMoves->push_back(make_pair(hStart + tmp, vStart - 1));
			*(board.square[hStart][vStart])->isCaptureEnPassant() = make_pair(hStart, vStart - 1);
		}
	}
	else *(board.square[hStart][vStart])->isCaptureEnPassant() = make_pair(-1, -1);

}

vector<pair<int, int>>* MakePossibleMoves(Piece* piece, bool Mode)// режим работы: напрямую с массивом ходов или с его копией: true - напрямую, false - копия
{
	vector<pair<int, int>>* vector1;
	vector<pair<int, int>> vector2;
	if (Mode)
	{
		piece->GetPossibleMoves()->clear();
		vector1 = piece->GetPossibleMoves();
	}
	else
	{
		for (int i = 0; i < piece->GetPossibleMoves()->size(); i++)
			vector2.push_back((*(piece->GetPossibleMoves()))[0]);
		vector1 = &vector2;
			
	}
	Colour* colour = piece->GetColour();
	int* hor = piece->GetHor();
	int* vert = piece->GetVert();
	TypePiece* type = piece->GetName();
	switch (*type)
	{
	case (KING):
		FindPossibleMovesForKing(vector1, *vert, *hor, *colour);
		return vector1;
		break;
	case (QUEEN):
		FindPossibleMovesForQueen(vector1, *vert, *hor, *colour);
		return vector1;
		break;
	case(BISHOP):
		FindPossibleMovesForBishop(vector1, *vert, *hor, *colour);
		return vector1;
		break;
	case(KNIGHT):
		FindPossibleMovesForKnight(vector1, *vert, *hor, *colour);
		return vector1;
		break;
	case(ROOK):
		FindPossibleMovesForRook(vector1, *vert, *hor, *colour);
		return vector1;
		break;
	case(PAWN):
		FindPossibleMovesForPawn(vector1, *vert, *hor, *colour, *(piece->getMoveCount()));
		return vector1;
		break;
	case (EMPTY):
		return vector1;
		break;
	}
}

bool Board::move(int vert, int hor, Colour col, Piece* piece)
{
	Colour* colour = piece->GetColour();
	TypePiece* type = piece->GetName();
	auto PossibleMoves = MakePossibleMoves(piece, 1);
	bool* canMove = piece->GetCanMove();
	auto vertical = piece->GetVert();
	int* horizontal = piece->GetHor();
	int* MoveCount = piece->getMoveCount();
	switch (*type)
	{
	case (KING):
		if (col == NONE && Check(vert, hor) && CanMakeMove(*PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			*MoveCount += 1;
			board.PieceMoving(vert, hor, *vertical, *horizontal, *MoveCount);
			if (abs(*vertical - vert) > 1)
			{
				pair<int, int>* castle = piece->isMackingCastling();
				if ((*castle).first == 7 && *vertical - vert == 2)
					board.PieceMoving(3, *horizontal, 0, *horizontal, *MoveCount);
				else if ((*castle).second == 0 && *vertical - vert == -2)
					board.PieceMoving(5, *horizontal, 7, *horizontal, *MoveCount);
			}
			*horizontal = hor;
			*vertical = vert;
			hasMadeMove = make_pair(*horizontal, *vertical);
			if (*colour == WHITE)
				WhiteKingCoords = make_pair(hor, vert);
			else
				BlackKingCoords = make_pair(hor, vert);
			return true;
		}
		return false;
		break;
	case (QUEEN):
		if (col == NONE && Check(vert, hor) && CanMakeMove(*PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			*MoveCount += 1;
			board.PieceMoving(vert, hor, *vertical, *horizontal, *MoveCount);
			*horizontal = hor;
			*vertical = vert;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
		break;
	case(BISHOP):
		if (col == NONE && Check(vert, hor) && CanMakeMove(*PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			*MoveCount += 1;
			board.PieceMoving(vert, hor, *vertical, *horizontal, *MoveCount);
			*horizontal = hor;
			*vertical = vert;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
		break;
	case(KNIGHT):
		if (col == NONE && Check(vert, hor) && CanMakeMove(*PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			*MoveCount += 1;
			board.PieceMoving(vert, hor, *vertical, *horizontal, *MoveCount);
			*horizontal = hor;
			*vertical = vert;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
		break;
	case(ROOK):
		if (canMove && col == NONE && Check(vert, hor) && CanMakeMove(*PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			*MoveCount += 1;
			board.PieceMoving(vert, hor, *vertical, *horizontal, *MoveCount);
			*horizontal = hor;
			*vertical = vert;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
		break;
	case(PAWN):
		if (col == NONE && Check(vert, hor) && CanMakeMove(*PossibleMoves, *canMove, make_pair(hor, vert)))//-Check -col
		{
			*MoveCount += 1;
			pair<int, int> captureEnPassant = *(board.square[*horizontal][*vertical])->isCaptureEnPassant();
			if (captureEnPassant.first == *horizontal && captureEnPassant.second == vert)
			{
				int sign = 1;
				if (*colour == BLACK)
					sign = -1;
				SetPiece(NONE, *horizontal, vert, EMPTY, -1);
			}
			board.PieceMoving(vert, hor, *vertical, *horizontal, *MoveCount);
			*vertical = vert;
			*horizontal = hor;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
		break;
	case (EMPTY):
		return false;
		break;
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
		if (*colour != col && CanMakeMove(PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			int newHor = hor;
			int newVert = vert;
			*MoveCount += 1;
			board.PieceMoving(vert, hor, *vertical, *horizontal, *MoveCount);
			*horizontal = newHor;
			*vertical = newVert;
			if (*colour == WHITE)
				WhiteKingCoords = make_pair(newHor, newVert);
			else
				BlackKingCoords = make_pair(newHor, newVert);
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
		break;
	case (QUEEN):
		if (vert < *vertical) vsign = -1;
		if (vert == *vertical) vsign = 0;
		if (hor < *horizontal) hsign = -1;
		if (hor == *horizontal) hsign = 0;
		if (*colour != col && CanMakeMove(PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			*MoveCount += 1;
			int newHor = hor;
			int newVert = vert;
			board.PieceMoving(vert, hor, *vertical, *horizontal, *MoveCount);
			*horizontal = newHor;
			*vertical = newVert;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
		break;
	case(BISHOP):
		if (vert < *vertical) vsign = -1;
		if (hor < *horizontal) hsign = -1;
		if (*colour != col && CanMakeMove(PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			int newHor = hor;
			int newVert = vert;
			*MoveCount += 1;
			board.PieceMoving(vert, hor, *vertical, *horizontal, *MoveCount);
			*horizontal = newHor;
			*vertical = newVert;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
		break;
	case(KNIGHT):
		if (*colour != col && CanMakeMove(PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			int newHor = hor;
			int newVert = vert;
			board.PieceMoving(vert, hor, *vertical, *horizontal, *MoveCount);
			*horizontal = newHor;
			*vertical = newVert;
			*MoveCount += 1;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
		break;
	case(ROOK):
		if (vert < *vertical) vsign = -1;
		if (vert == *vertical) vsign = 0;
		if (hor < *horizontal) hsign = -1;
		if (hor == *horizontal) hsign = 0;
		if (*colour != col && CanMakeMove(PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			*MoveCount += 1;
			int newHor = hor;
			int newVert = vert;
			board.PieceMoving(vert, hor, *vertical, *horizontal, *MoveCount);
			*horizontal = newHor;
			*vertical = newVert;	
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
		}
		return false;
		break;
	case(PAWN):
		if (*colour != col && CanMakeMove(PossibleMoves, *canMove, make_pair(hor, vert)))
		{
			*MoveCount += 1;
			int newHor = hor;
			int newVert = vert;
			board.PieceMoving(vert, hor, *vertical, *horizontal, *MoveCount);
			*horizontal = newHor;
			*vertical = newVert;
			hasMadeMove = make_pair(*horizontal, *vertical);
			return true;
			//взятие на проходе
		}
		return false;
		break;
	case (EMPTY):
		return false;
		break;
	}
}

bool Pat(Colour colour)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (board.square[i][j]->GetPossibleMoves()->size() != 0 && *(board.square[i][j]->GetColour()) == colour)
				return false;
	return true;
}

bool Checkmate(Colour colour)
{
	pair<int, int> coordsKing; // мат
	if (colour == BLACK)
		coordsKing = BlackKingCoords;
	else
		coordsKing = WhiteKingCoords;
	if (HasCheck(coordsKing.second, coordsKing.first, colour, false) && Pat(colour))
		return true;
}