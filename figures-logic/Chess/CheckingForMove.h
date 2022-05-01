#pragma once
#include "Board.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
Board* CreateBoard()
{
	Board board;
	return &board;
}

Board* board = CreateBoard();


bool MovingBishop(int vEnd, int hEnd, int vStart, int hStart) //�� �����
{
	return (abs((vEnd - vStart) == abs(hEnd - hStart)) && (vEnd != vStart));
};
bool PiecesAlongTheWayForBishop(int vEnd, int hEnd, int vStart, int hStart) // ���� �����
{
	int vsign = 1;
	int hsign = 1;
	if (vEnd < vStart) vsign = -1;
	if (hEnd < hStart) hsign = -1;
	vStart += vsign;
	hStart += hsign;
	for (; abs(vStart - vEnd) > 0; vStart += vsign, hStart += hsign)
	{
		if (board->square[hStart][vStart]->GetColour() != 'n')
			return false;
	}
	return true;
}

bool MovingRook(int vEnd, int hEnd, int vStart, int hStart) // �����
{
	return (((vEnd = vStart) && (hEnd != hStart)) || ((vEnd != vStart) && (hEnd == hStart)));
}
bool PiecesAlongTheWayForRook(int vEnd, int hEnd, int vStart, int hStart) // ��, ���� ������ � MovingKing
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
		if (board->square[Start][Start]->GetColour() != 'n')
			return false;
	}
	return true;
}

bool MovingQueen(int vEnd, int hEnd, int vStart, int hStart) // �� �����
{
	return MovingBishop(vEnd, hEnd, vStart, hStart) || MovingRook(vEnd, hEnd, vStart, hStart);
}
bool PiecesAlongTheWayForQueen(int vEnd, int hEnd, int vStart, int hStart) // ��� PiecesAlongTheWayForKing
{
	return PiecesAlongTheWayForBishop(vEnd, hEnd, vStart, hStart) || PiecesAlongTheWayForRook(vEnd, hEnd, vStart, hStart);
}

bool CanCut(pair<int, int> coords, Piece* CheckingPiece)
{
	if (coords.first != -1)
	{
		return board->square[coords.first][coords.second]->cut_down(*CheckingPiece);
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

bool HasCheck(int vStart, int hStart, char kingColour) //���
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

bool MovingKing(int vEnd, int hEnd, int vStart, int hStart) // ��
{
	if (board->square[hStart][vStart]->getFirstMove() == false && HasCheck(vStart, hStart, board->square[hStart][vStart]->GetColour()))
	{
		int i;
		int j;
		if (vEnd == 2)
		{
			i = 0;
			j = 1;
		}
		else if (vEnd == 6)
		{
			i = 7;
			j = -1;
		}
		else return (abs(vEnd - vStart) < 2 && abs(hEnd - hStart) < 2 && (abs(hEnd - hStart) != 0 || abs(hEnd - hStart) != 0));

		if (board->square[hStart][i]->getFirstMove() == false)
		{
			if (PiecesAlongTheWayForRook(vEnd + j, hEnd, i, hStart))
			{
				board->PieceMoving(vEnd + j, hEnd, i, hStart);
				return true;
			}
		}
		return false;
	}
 
}
bool PiecesAlongTheWayForKing(int vEnd, int hEnd, int vStart, int hStart) // ��
{
	return PiecesAlongTheWayForQueen(vEnd, hEnd, vStart, hStart);
}

bool MovingKnight(int vEnd, int hEnd, int vStart, int hStart)
{
	return (vStart + 2 == vEnd && hStart + 1 == hEnd || vStart + 1 == vEnd && hStart + 2 == hEnd ||
			vStart - 1 == vEnd && hStart + 2 == hEnd || vStart - 2 == vEnd && hStart + 1 == hEnd ||
			vStart - 2 == vEnd && hStart - 1 == hEnd || vStart - 1 == vEnd && hStart - 2 == hEnd ||
			vStart + 1 == vEnd && hStart - 2 == hEnd || vStart + 2 == vEnd && hStart - 1 == hEnd);
}

bool MovingPawn(int vEnd, int hEnd, int vStart, int hStart, bool didMove)
{
	return ((!didMove && vStart == vEnd - 2) || (vStart == vEnd - 1));
}
bool PiecesAlongTheWayForPawn(int vEnd, int hEnd, int vStart, int hStart)
{
	return PiecesAlongTheWayForRook(vEnd, hEnd, vStart, hStart);
}

void FindPossibleMovesForPawn(vector<pair<int, int>>& PossibleMoves, int vStart, int hStart, char colour, bool didMove)
{
	int tmp = 1;
	if (didMove == false)
		tmp = 2;
	funkRook(PossibleMoves, vStart, vStart+tmp, vStart, hStart, colour);
	FindPossibleMovesForBishop(PossibleMoves, vStart+1, hStart+1, colour);
	FindPossibleMovesForBishop(PossibleMoves, vStart-1, hStart+1, colour);

}