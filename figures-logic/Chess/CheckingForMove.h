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
	return (((vEnd = vStart) && (hEnd != hStart)) || ((vEnd != vStart) && (hEnd == hStart));
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
	return MovingBishop(vEnd, hEnd, vStart, hStart) || MovingQueen(vEnd, hEnd, vStart, hStart);
}
bool PiecesAlongTheWayForQueen(int vEnd, int hEnd, int vStart, int hStart)
{
	return PiecesAlongTheWayForBishop(vEnd, hEnd, vStart, hStart) || PiecesAlongTheWayForQueen(vEnd, hEnd, vStart, hStart);
}

bool MovingKing(int vEnd, int hEnd, int vStart, int hStart)
{

}