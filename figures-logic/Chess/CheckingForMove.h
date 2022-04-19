#pragma once
#include "Board.h"

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
		if (square[hStart][vStart]->GetColour() != 'n')
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
		if (square[Start][Start]->GetColour() != 'n')
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
	if (square[vStart][hStart]->getFirstMove() == false)
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
		else break;

		if (square[i][hStart]->getFirstMove() == false)
		{
			if (PiecesAlongTheWayForRook(vEnd + j, hEnd, i, hStart))
			{
				PieceMoving(vEnd + j, hEnd, i, hStart);
				return true;
			}
		}
		else return false;
	}
	else return (abs(vEnd - vStart) < 2 && abs(hEnd - hStart) < 2 && (abs(hEnd - hStart) != 0 || abs(hEnd - hStart) != 0));
}
bool PiecesAlongTheWayForKing(int vEnd, int hEnd, int vStart, int hStart)
{
	return PiecesAlongTheWayForQueen(vEnd, hEnd, vStart, hStart);
}
bool HasChecking(int vStart, int hStart)
{
	
}

bool MovingKnight(int vEnd, int hEnd, int vStart, int hStart)
{
	return (vStart + 2 == vEnd && hStart + 1 == hEnd || vStart + 1 == vEnd && hStart + 2 == hEnd ||
		vStart - 1 == vEnd && hStart + 2 == hEnd || vStart - 2 == vEnd && hStart + 1 == hEnd||
		vStart - 2 == vEnd && hStart - 1 == hEnd || vStart - 1 == vEnd && hStart - 2 == hEnd ||
		vStart + 1 == vEnd && hStart - 2 == hEnd|| vStart + 2 == vEnd && hStart - 1 == hEnd);
}

bool MovingPawn(int vEnd, int hEnd, int vStart, int hStart, bool didMove)
{
	return ((!didMove && vStart == vEnd - 2) || (vStart == vEnd- 1));
}
bool PiecesAlongTheWayForPawn(int vEnd, int hEnd, int vStart, int hStart)
{
	return PiecesAlongTheWayForRook(vEnd, hEnd, vStart, hStart);
}