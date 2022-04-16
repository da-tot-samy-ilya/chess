#pragma once
//square[]
#include <iostream>

bool MovingBishop(int vEnd, int hEnd, int vStart, int hStart)
{
	return (abs((vEnd - vStart) == abs(hEnd - hStart)) && (vEnd != vStart));
};
bool PiecesAlongTheWay(char colour, int v1, int h1, int v2, int h2) // замутить рекурсию
{
	
}