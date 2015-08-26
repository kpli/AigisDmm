#pragma once
class CTools
{
public:
	static CTools* getInstance();

	// ��ͼ
	void saveImage();

	void printMouseColor();
	void printSystemTime();

	// �����������������
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


