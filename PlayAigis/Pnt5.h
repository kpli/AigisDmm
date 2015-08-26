#pragma once 

class CPnt5
{
public:
	CPnt5(POINT pnt);
	CPnt5(int x, int y);
	CPnt5(POINT pnt, COLORREF c0, COLORREF c1, COLORREF c2, COLORREF c3, COLORREF c4);
	CPnt5(int x, int y, COLORREF c0, COLORREF c1, COLORREF c2, COLORREF c3, COLORREF c4);
	CPnt5(int x, int y, COLORREF c0, COLORREF c1, COLORREF c2, COLORREF c3, COLORREF c4, int tx, int ty);
	~CPnt5();

	POINT getPoint(E_POINT_DIRECTION epd);
	const COLORREF getColor(E_POINT_DIRECTION epd);

	void setMidPnt(int x, int y);

	bool find();
	void click();
	void print();


private:
	POINT mp;				// 中心点
	COLORREF ac[EPD_MAX];	// 特征色
	POINT tp;				// 角色上场目标点
};

class CRolePnt
{
public:
	CPnt5 p5;
	POINT pt;

public:
	CRolePnt(CPnt5 pnt5, int tx, int ty);
	void drag();
};

