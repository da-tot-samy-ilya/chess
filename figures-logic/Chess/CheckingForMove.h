#pragma once
#include "Board.h"
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
bool HasCheck(int vStart, int hStart, char kingColour) //шах
{
	Piece p;
	/*
	* std::pair<int, int> coord;
	KingLikeRook(coord, vStart, 0, vStart, hStart, kingColour);
	if (coord.first != -1)
	{
		if (p.cut_down(board->square[hStart][vStart])) return true;
	}
	*/
	KingLikeRook(p, vStart, 0, vStart, hStart, kingColour);
	if (p.GetName() != EMPTY)
	{
		if (p.cut_down(board->square[hStart][vStart])) return true;
	}
	KingLikeRook(p, vStart, 7, vStart, hStart, kingColour);
	if (p.GetName() != EMPTY)
	{
		if (p.cut_down(board->square[hStart][vStart])) return true;
	}
	KingLikeRook(p, 0, hStart, vStart, hStart, kingColour);
	if (p.GetName() != EMPTY)
	{
		if (p.cut_down(board->square[hStart][vStart])) return true;
	}
	KingLikeRook(p, 7, hStart, vStart, hStart, kingColour);
	if (p.GetName() != EMPTY)
	{
		if (p.cut_down(board->square[hStart][vStart])) return true;
	}
	
	std::pair<int, int> Up = GetEdge(vStart, hStart, 7);
	std::pair<int, int> Down = GetEdge(vStart, hStart, 0);

	KingLikeBishop(p, Down.first, 0, vStart, hStart, kingColour);
	if (p.GetName() != EMPTY)
	{
		if (p.cut_down(board->square[hStart][vStart])) return true;
	}
	KingLikeBishop(p, Down.second, 0, vStart, hStart, kingColour);
	if (p.GetName() != EMPTY)
	{
		if (p.cut_down(board->square[hStart][vStart])) return true;
	}
	KingLikeBishop(p, Up.first, 7, vStart, hStart, kingColour);
	if (p.GetName() != EMPTY)
	{
		if (p.cut_down(board->square[hStart][vStart])) return true;
	}
	KingLikeBishop(p, Up.second, 7, vStart, hStart, kingColour);
	if (p.GetName() != EMPTY)
	{
		if (p.cut_down(board->square[hStart][vStart])) return true;
	}
	if (KingLikeKnight(vStart, hStart, kingColour))
		return true;
	return false;
}
Piece* KingLikeRook(Piece& p, int vEnd, int hEnd, int vStart, int hStart, char kingColour)
{
	int vsign = 1;
	int hsign = 1;
	if (vEnd < vStart) vsign = -1;
	if (hEnd < hStart) hsign = -1;
	vStart += vsign;
	hStart += hsign;
	for (; abs(vStart - vEnd) > 0; vStart += vsign, hStart += hsign)
	{
		if (board->square[hStart][vStart]->GetColour() == kingColour)
			return &p;
		else return board->square[vStart][vStart];
	}
};
Piece* KingLikeBishop(Piece& p, int vEnd, int hEnd, int vStart, int hStart, char kingColour)
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
		if (board->square[Start][Start]->GetColour() == kingColour)
			return &p;
		else return board->square[Start][Start];
	}
};

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
	if (board->square[hStart + 2][vStart + 1].GetName() == KNIGHT && board->square[hStart + 2][vStart + 1].GetColour() != kingColour && Check(vStart + 2, hStart + 1))
		return true;
	if (board->square[hStart + 1][vStart + 2].GetName() == KNIGHT && board->square[hStart + 1][vStart + 2].GetColour() != kingColour && Check(vStart + 1, hStart + 2))
		return true;
	if (board->square[hStart - 1][vStart + 2].GetName() == KNIGHT && board->square[hStart - 1][vStart + 2].GetColour() != kingColour && Check(vStart - 1, hStart + 2))
		return true;
	if (board->square[hStart - 2][vStart + 1].GetName() == KNIGHT && board->square[hStart - 1][vStart + 2].GetColour() != kingColour && Check(vStart - 1, hStart + 2))
		return true;
	if (board->square[hStart - 2][vStart - 1].GetName() == KNIGHT && board->square[hStart - 2][vStart - 1].GetColour() != kingColour && Check(vStart - 2, hStart - 1))
		return true;
	if (board->square[hStart - 1][vStart - 2].GetName() == KNIGHT && board->square[hStart - 1][vStart - 2].GetColour() != kingColour && Check(vStart - 1, hStart - 2))
		return true;
	if (board->square[hStart + 1][vStart - 2].GetName() == KNIGHT && board->square[hStart + 1][vStart - 2].GetColour() != kingColour && Check(vStart + 1, hStart - 2))
		return true;
	if (board->square[hStart + 2][vStart - 1].GetName() == KNIGHT && board->square[hStart + 2][vStart - 1].GetColour() != kingColour && Check(vStart + 2, hStart - 1))
		return true;

	return false;
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