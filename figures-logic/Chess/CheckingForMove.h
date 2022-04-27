//#pragma once
//#include "Board.h"
//
//Board* board = CreateBoard();
//bool MovingBishop(int vEnd, int hEnd, int vStart, int hStart)
//{
//	return (abs((vEnd - vStart) == abs(hEnd - hStart)) && (vEnd != vStart));
//};
//bool PiecesAlongTheWayForBishop(int vEnd, int hEnd, int vStart, int hStart)
//{
//	int vsign = 1;
//	int hsign = 1;
//	if (vEnd < vStart) vsign = -1;
//	if (hEnd < hStart) hsign = -1;
//	vStart += vsign;
//	hStart += hsign;
//	for (; abs(vStart - vEnd) > 0; vStart += vsign, hStart += hsign)
//	{
//		if (board->square[hStart][vStart]->GetColour() != 'n')
//			return false;
//	}
//	return true;
//}
//
//bool MovingRook(int vEnd, int hEnd, int vStart, int hStart)
//{
//	return (((vEnd = vStart) && (hEnd != hStart)) || ((vEnd != vStart) && (hEnd == hStart)));
//}
//bool PiecesAlongTheWayForRook(int vEnd, int hEnd, int vStart, int hStart)
//{
//	int sign = 1;
//	int End = vEnd;
//	int Start = vStart;
//	if (vEnd == vStart)
//	{
//		int End = hEnd;
//		int Start = hStart;
//	}
//	if (End < Start) sign = -1;
//	Start += sign;
//	for (; abs(Start - End) > 0; Start += sign)
//	{
//		if (board->square[Start][Start]->GetColour() != 'n')
//			return false;
//	}
//	return true;
//}
//
//bool MovingQueen(int vEnd, int hEnd, int vStart, int hStart)
//{
//	return MovingBishop(vEnd, hEnd, vStart, hStart) || MovingRook(vEnd, hEnd, vStart, hStart);
//}
//bool PiecesAlongTheWayForQueen(int vEnd, int hEnd, int vStart, int hStart)
//{
//	return PiecesAlongTheWayForBishop(vEnd, hEnd, vStart, hStart) || PiecesAlongTheWayForRook(vEnd, hEnd, vStart, hStart);
//}
//bool MovingKing(int vEnd, int hEnd, int vStart, int hStart)
//{
//	if (board->square[hStart][vStart]->getFirstMove() == false && board->square[hStart][vStart]->HasShah(vStart, hStart, board->square[hStart][vStart].GetColour()))
//	{
//		int i;
//		int j;
//		if (vEnd == 2)
//		{
//			i = 0;
//			j = 1;
//		}
//		else if (vEnd == 6)
//		{
//			i = 7;
//			j = -1;
//		}
//		else return (abs(vEnd - vStart) < 2 && abs(hEnd - hStart) < 2 && (abs(hEnd - hStart) != 0 || abs(hEnd - hStart) != 0));
//
//		if (board->square[hStart][i]->getFirstMove() == false)
//		{
//			if (PiecesAlongTheWayForRook(vEnd + j, hEnd, i, hStart))
//			{
//				board->PieceMoving(vEnd + j, hEnd, i, hStart);
//				return true;
//			}
//		}
//		return false;
//	}
//
//}
//
//bool PiecesAlongTheWayForKing(int vEnd, int hEnd, int vStart, int hStart)
//{
//	return PiecesAlongTheWayForQueen(vEnd, hEnd, vStart, hStart);
//}
//bool HasCheck(int vStart, int hStart, char kingColour) //øàõ
//{
//	Piece p;
//	KingLikeRook(p, vStart, 0, vStart, hStart, kingColour);
//	if (p.GetName() != EMPTY)
//	{
//		if (p.cut_down(board->square[hStart][vStart])) return true;
//	}
//	KingLikeRook(p, vStart, 7, vStart, hStart, kingColour);
//	if (p.GetName() != EMPTY)
//	{
//		if (p.cut_down(board->square[hStart][vStart])) return true;
//	}
//	KingLikeRook(p, 0, hStart, vStart, hStart, kingColour);
//	if (p.GetName() != EMPTY)
//	{
//		if (p.cut_down(board->square[hStart][vStart])) return true;
//	}
//	KingLikeRook(p, 7, hStart, vStart, hStart, kingColour);
//	if (p.GetName() != EMPTY)
//	{
//		if (p.cut_down(board->square[hStart][vStart])) return true;
//	}
//
//	std::pair<int, int> Hor = GetHorEdge(vStart, hStart);
//	std::pair<int, int> Vert = GetVertEdge(vStart, hStart);
//
//	KingLikeBishop(p, vStart, leftHor, vStart, hStart, kingColour);
//	if (p.GetName() != EMPTY)
//	{
//		if (p.cut_down(board->square[hStart][vStart])) return true;
//	}
//	KingLikeBishop(p, vStart, rightHor, vStart, hStart, kingColour);
//	if (p.GetName() != EMPTY)
//	{
//		if (p.cut_down(board->square[hStart][vStart])) return true;
//	}
//	KingLikeBishop(p, leftVert, hStart, vStart, hStart, kingColour);
//	if (p.GetName() != EMPTY)
//	{
//		if (p.cut_down(board->square[hStart][vStart])) return true;
//	}
//	KingLikeBishop(p, rightVert, hStart, vStart, hStart, kingColour);
//	if (p.GetName() != EMPTY)
//	{
//		if (p.cut_down(board->square[hStart][vStart])) return true;
//	}
//	if (KingLikeKnight(vStart, hStart, kingColour))
//		return true;
//	return false;
//}
//Piece* KingLikeRook(Piece& p, int vEnd, int hEnd, int vStart, int hStart, char kingColour)
//{
//	int vsign = 1;
//	int hsign = 1;
//	if (vEnd < vStart) vsign = -1;
//	if (hEnd < hStart) hsign = -1;
//	vStart += vsign;
//	hStart += hsign;
//	for (; abs(vStart - vEnd) > 0; vStart += vsign, hStart += hsign)
//	{
//		if (board->square[hStart][vStart]->GetColour() == kingColour)
//			return &p;
//		else return board->square[vStart][vStart];
//	}
//};
//Piece* KingLikeBishop(Piece& p, int vEnd, int hEnd, int vStart, int hStart, char kingColour)
//{
//	int sign = 1;
//	int End = vEnd;
//	int Start = vStart;
//	if (vEnd == vStart)
//	{
//		int End = hEnd;
//		int Start = hStart;
//	}
//	if (End < Start) sign = -1;
//	Start += sign;
//	for (; abs(Start - End) > 0; Start += sign)
//	{
//		if (board->square[Start][Start]->GetColour() == kingColour)
//			return &p;
//		else return board->square[Start][Start];
//	}
//};
//
//std::pair<int, int> GetHorEdge(int vStart, int hStart)
//{
//	int hStart1 = hStart;
//	int hStart2 = hStart;
//	for (; vStart != 0; vStart -= 1, hStart1 += 1, hStart2 -= 1)
//		return std::make_pair(hStart1, hStart2);
//}
//
//std::pair<int, int> GetVertEdge(int vStart, int hStart)
//{
//	int vStart1 = vStart;
//	int vStart2 = vStart;
//	for (; vStart != 0; hStart -= 1, vStart1 += 1, vStart2 -= 1)
//		return std::make_pair(vStart1, vStart2);
//}
//
//bool KingLikeKnight(int vStart, int hStart, char kingColour)
//{
//	if (board->square[hStart + 2][vStart + 1].GetName() == KNIGHT && board->square[hStart + 2][vStart + 1].GetColour() != kingColour && Check(vStart + 2, hStart + 1))
//		return true;
//	if (board->square[hStart + 1][vStart + 2].GetName() == KNIGHT && board->square[hStart + 1][vStart + 2].GetColour() != kingColour && Check(vStart + 1, hStart + 2))
//		return true;
//	if (board->square[hStart - 1][vStart + 2].GetName() == KNIGHT && board->square[hStart - 1][vStart + 2].GetColour() != kingColour && Check(vStart - 1, hStart + 2))
//		return true;
//	if (board->square[hStart - 2][vStart + 1].GetName() == KNIGHT && board->square[hStart - 1][vStart + 2].GetColour() != kingColour && Check(vStart - 1, hStart + 2))
//		return true;
//	if (board->square[hStart - 2][vStart - 1].GetName() == KNIGHT && board->square[hStart - 2][vStart - 1].GetColour() != kingColour && Check(vStart - 2, hStart - 1))
//		return true;
//	if (board->square[hStart - 1][vStart - 2].GetName() == KNIGHT && board->square[hStart - 1][vStart - 2].GetColour() != kingColour && Check(vStart - 1, hStart - 2))
//		return true;
//	if (board->square[hStart + 1][vStart - 2].GetName() == KNIGHT && board->square[hStart + 1][vStart - 2].GetColour() != kingColour && Check(vStart + 1, hStart - 2))
//		return true;
//	if (board->square[hStart + 2][vStart - 1].GetName() == KNIGHT && board->square[hStart + 2][vStart - 1].GetColour() != kingColour && Check(vStart + 2, hStart - 1))
//		return true;
//
//	return false;
//}
//
//bool MovingKnight(int vEnd, int hEnd, int vStart, int hStart)
//{
//	return (vStart + 2 == vEnd && hStart + 1 == hEnd || vStart + 1 == vEnd && hStart + 2 == hEnd ||
//		vStart - 1 == vEnd && hStart + 2 == hEnd || vStart - 2 == vEnd && hStart + 1 == hEnd ||
//		vStart - 2 == vEnd && hStart - 1 == hEnd || vStart - 1 == vEnd && hStart - 2 == hEnd ||
//		vStart + 1 == vEnd && hStart - 2 == hEnd || vStart + 2 == vEnd && hStart - 1 == hEnd);
//}
//
//bool MovingPawn(int vEnd, int hEnd, int vStart, int hStart, bool didMove)
//{
//	return ((!didMove && vStart == vEnd - 2) || (vStart == vEnd - 1));
//}
//bool PiecesAlongTheWayForPawn(int vEnd, int hEnd, int vStart, int hStart)
//{
//	return PiecesAlongTheWayForRook(vEnd, hEnd, vStart, hStart);
//}