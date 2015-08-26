#pragma once
class CTools
{
public:
	static CTools* getInstance();

	// 截图
	void saveImage();

	void printMouseColor();
	void printSystemTime();

	// 查找特征，输出坐标
	void searchColor();
	bool findRidder();
private:
	CTools();
	~CTools();

	void initDir();
	void saveBmp(HWND hwnd, LPCSTR name);
	BOOL flushBmp(HBITMAP hbitmap, LPCSTR name, int nColor = 8);
	std::string generatImgName();
};


