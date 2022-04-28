#pragma once
#include "Board.h"
using namespace std;
Board* CreateBoard()
{
	Board board;
	return &board;
}

Board* board = CreateBoard();


bool MovingBishop(int vEnd, int hEnd, int vStart, int hStart)
{
	return (abs((vEnd - vStart) == abs(hEnd - hStart)) && (vEnd != vStart));
};
bool PiecesAlongTheWayForBishop(int vEnd, int hEnd, int vStart, int hStart)
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

bool MovingRook(int vEnd, int hEnd, int vStart, int hStart)
{
	return (((vEnd = vStart) && (hEnd != hStart)) || ((vEnd != vStart) && (hEnd == hStart)));
}
bool PiecesAlongTheWayForRook(int vEnd, int hEnd, int vStart, int hStart)
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

bool MovingQueen(int vEnd, int hEnd, int vStart, int hStart)
{
	return MovingBishop(vEnd, hEnd, vStart, hStart) || MovingRook(vEnd, hEnd, vStart, hStart);
}
bool PiecesAlongTheWayForQueen(int vEnd, int hEnd, int vStart, int hStart)
{
	return PiecesAlongTheWayForBishop(vEnd, hEnd, vStart, hStart) || PiecesAlongTheWayForRook(vEnd, hEnd, vStart, hStart);
}

bool CanCut(pair<int, int> coord, Piece* CheckingPiece)
{
	if (coord.first != -1)
	{
		return board->square[coord.first][coord.second]->cut_down(*CheckingPiece);
	}
}


pair<int, int> KingLikeRook(std::pair<int, int> coord, int vEnd, int hEnd, int vStart, int hStart, char kingColour)
{
	int vsign = 1;
	int hsign = 1;
	if (vEnd < vStart) vsign = -1;
	if (hEnd < hStart) hsign = -1;
	vStart += vsign;
	hStart += hsign;
	for (; abs(vStart - vEnd) > 0; vStart += vsign, hStart += hsign)
	{
		if (board->square[hStart][vStart]->GetColour() == kingColour || board->square[hStart][vStart]->GetName() == EMPTY)
		{
			coord.first = -1;
			coord.second = -1;
			return coord;
		}
		else
		{
			coord.first = hStart;
			coord.second = vStart;
			return coord;
		}
	}
}
pair<int, int> KingLikeBishop(std::pair<int, int> coord, int vEnd, int hEnd, int vStart, int hStart, char kingColour)
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
		if (board->square[Start][Start]->GetColour() == kingColour || board->square[hStart][vStart]->GetName() == EMPTY)
		{
			coord.first = -1;
			coord.second = -1;
			return coord;
		}
		else
		{
			coord.first = hStart;
			coord.second = vStart;
			return coord;
		}
	}
}

std::pair<int, int> GetEdge(int vStart, int hStart, int hor)
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

bool HasCheck(int vStart, int hStart, char kingColour) //øàõ
{
	std::pair<int, int> coord(-1, -1);
	Piece* CheckingPiece = board->square[hStart][vStart];

	pair<int, int> coord1 = KingLikeRook(coord, vStart, 7, vStart, hStart, kingColour);
	pair<int, int> coord2 = KingLikeRook(coord, vStart, 0, vStart, hStart, kingColour);
	pair<int, int> coord3 = KingLikeRook(coord, 0, hStart, vStart, hStart, kingColour);
	pair<int, int> coord4 = KingLikeRook(coord, 7, hStart, vStart, hStart, kingColour);

	std::pair<int, int> Up = GetEdge(vStart, hStart, 7);
	std::pair<int, int> Down = GetEdge(vStart, hStart, 0);

	pair<int, int> coord5 = KingLikeBishop(coord, Down.first, 0, vStart, hStart, kingColour);
	pair<int, int> coord6 = KingLikeBishop(coord, Down.second, 0, vStart, hStart, kingColour);
	pair<int, int> coord7 = KingLikeBishop(coord, Up.first, 7, vStart, hStart, kingColour);
	pair<int, int> coord8 = KingLikeBishop(coord, Up.second, 7, vStart, hStart, kingColour);

	if (CanCut(coord1, CheckingPiece) || CanCut(coord2, CheckingPiece) || CanCut(coord3, CheckingPiece)
		|| CanCut(coord4, CheckingPiece) || CanCut(coord5, CheckingPiece) || CanCut(coord6, CheckingPiece)
		|| CanCut(coord7, CheckingPiece) || CanCut(coord8, CheckingPiece) || KingLikeKnight(vStart, hStart, kingColour)) return true;

	return false;
}

bool MovingKing(int vEnd, int hEnd, int vStart, int hStart)
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

bool PiecesAlongTheWayForKing(int vEnd, int hEnd, int vStart, int hStart)
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