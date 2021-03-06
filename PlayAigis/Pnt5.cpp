#include "stdafx.h"
//#include "Pnt5.h"
#include "Tools.h"
#include "Frame.h"
 

CPnt5::CPnt5(POINT pnt)
{
	mp.x = pnt.x;
	mp.y = pnt.y;
	for (size_t i = 0; i < EPD_MAX; i++)
	{
		ac[i] = COLORREF(0x000000);
	}
}

CPnt5::CPnt5(int x, int y)
{
	mp.x = x;
	mp.y = y;
	for (size_t i = 0; i < EPD_MAX; i++)
	{
		ac[i] = COLORREF(0x000000);
	}
}

CPnt5::CPnt5(POINT pnt, COLORREF c0, COLORREF c1, COLORREF c2, COLORREF c3, COLORREF c4)
{
	mp.x = pnt.x;
	mp.y = pnt.y;
	ac[0] = c0;
	ac[1] = c1;
	ac[2] = c2;
	ac[3] = c3;
	ac[4] = c4;
}

CPnt5::CPnt5(int x, int y, COLORREF c0, COLORREF c1, COLORREF c2, COLORREF c3, COLORREF c4)
{
	mp.x = x;
	mp.y = y;
	ac[0] = c0;
	ac[1] = c1;
	ac[2] = c2;
	ac[3] = c3;
	ac[4] = c4;
}

CPnt5::~CPnt5()
{
	mp.x = 0;
	mp.y = 0;
	for (size_t i = 0; i < EPD_MAX; i++)
	{
		ac[i] = COLORREF(0x000000);
	}
}

POINT CPnt5::getPoint(E_POINT_DIRECTION epd)
{
	POINT pnt = mp;
	switch (epd)
	{
	case EPD_MID:
		break;
	case EPD_LEFT:
		pnt.x -= POINT_INTERVAL;
		break;
	case EPD_TOP:
		pnt.y -= POINT_INTERVAL;
		break;
	case EPD_RIGHT:
		pnt.x += POINT_INTERVAL;
		break;
	case EPD_BOTTOM:
		pnt.y += POINT_INTERVAL;
		break;
	default:
		break;
	}
	return pnt;
}

const COLORREF CPnt5::getColor(E_POINT_DIRECTION epd)
{
	return ac[epd];
}

bool CPnt5::find()
{
	CFrame* pFrame = CFrame::getInstance();
	return pFrame->findColor(this);
}

void CPnt5::print()
{
	CFrame* pFrame = CFrame::getInstance();
	pFrame->logColor(this);
}

void CPnt5::click()
{
	CFrame::getInstance()->click(this);
}

void CPnt5::setMidPnt(int x, int y)
{
	mp.x = x;
	mp.y = y;
}

bool CPnt5::isSameColor(COLORREF c1, COLORREF c2)
{
	COLORREF arrDiff[8] = { 0x1, 0x100, 0x10000,  -0x1, -0x100, -0x10000 };
	if (c1 == c2)
		return true;
	for (int i = 0; i < 8; i++)
	{
		if (c1 + arrDiff[i] == c2)
			return true;
	}

	return false;
}

CRolePnt::CRolePnt(CPnt5 pnt5, int tx, int ty)
	: p5(pnt5)
{
	pt.x = tx; 
	pt.y = ty;
}

void CRolePnt::drag()
{
	CFrame::getInstance()->drag(this);
}