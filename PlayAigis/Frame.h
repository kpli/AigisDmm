#pragma once
class CPnt5;
class CRolePnt;
class CFrame
{
public:
	static CFrame* getInstance();

	// 关闭标签
	void closeChrome();

	// 截图
	void saveImage();

	// 找特征
	bool findColor(CPnt5* pnt5);

	// 记录特征
	void logColor(CPnt5* pnt5);
	void logColor();

	// 操作
	void click(CPnt5* pnt5);
	void drag(CRolePnt* pntR);

	// 记录搜索范围
	void setRangeLT();
	void setRangeRB();

	// 获取chrome标题
	int getChromeTitle(LPTSTR lpBuf, int maxLen);
	int getChromeTitle(LPSTR lpBuf, int maxLen);
private:
	HWND chromeHwnd();
	HWND aigisHwnd();
	void generatImgName(LPTSTR lpBuf, int maxLen);
	void setCurSor(POINT pnt);
private:
	CFrame();
	~CFrame();

};

