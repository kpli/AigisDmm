#pragma once
class CPnt5;
class CRolePnt;
class CFrame
{
public:
	static CFrame* getInstance();

	// �رձ�ǩ
	void closeChrome();

	// ������
	bool findColor(CPnt5* pnt5);

	// ��¼����
	void logColor(CPnt5* pnt5);
	void logColor();

	// ����
	void click(CPnt5* pnt5);
	void drag(CRolePnt* pntR);

	// ��¼������Χ
	void setRangeLT();
	void setRangeRB();

	// ��ȡHWND
	HWND aigisHwnd();
private:
	HWND chromeHwnd();
	void setCurSor(POINT pnt);
private:
	CFrame();
	~CFrame();

};

