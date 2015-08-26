#include "stdafx.h"
#include "Tools.h"
#include "Frame.h"
#include "ToPy.h"


CTools::CTools()
{
	initDir();
}


CTools::~CTools()
{
}

CTools* CTools::getInstance()
{
	static CTools ret;
	return &ret;
}

void CTools::initDir()
{
	DWORD dwAttr = GetFileAttributesA(SCREEN_SAVE_DIR);
	if (dwAttr == 0xFFFFFFFF)
	{
		CreateDirectoryA(SCREEN_SAVE_DIR, NULL);
	}
}

void CTools::saveImage()
{
	HWND hwnd = CFrame::getInstance()->aigisHwnd();
	if (!hwnd)
	{
		return;
	}

	std::string strName = generatImgName();
	saveBmp(hwnd, strName.c_str());
}

void CTools::saveBmp(HWND hwnd, LPCSTR file)
{
	HDC hdc = GetWindowDC(hwnd);
	HDC hMemDC_Tmp = CreateCompatibleDC(hdc);							//创建与桌面窗口DC相适应的内存TMP
	HBITMAP hbitm_tmp = CreateCompatibleBitmap(hdc, FRAME_SIZE);	//创建相适应的位图
	SelectObject(hMemDC_Tmp, hbitm_tmp);
	BitBlt(hMemDC_Tmp, COORD_ZERO, FRAME_SIZE, hdc, FRAME_BEGIN, SRCCOPY);
	CHAR szBuf[MAXCHAR];
	strcpy_s(szBuf, SCREEN_SAVE_DIR);
	strcpy_s(szBuf, file);
	flushBmp(hbitm_tmp, szBuf);
	DeleteObject(hbitm_tmp);
	DeleteDC(hMemDC_Tmp);
	ReleaseDC(hwnd, hdc);
}

BOOL CTools::flushBmp(HBITMAP hbitmap, LPCSTR filename, int nColor)
{
	BITMAP Bitmap ;
	HDC	hDC = nullptr;
	DWORD dwPaletteSize = 0, dwBmBitsSize, dwDIBSize, dwWritten;
	BITMAPFILEHEADER bmfHdr;
	BITMAPINFOHEADER bi;
	LPBITMAPINFOHEADER lpbi = nullptr;
	HANDLE fh, hDib, hPal, hOldPal = nullptr;

	if (nColor <= 8)
		dwPaletteSize = (1 << nColor)   *sizeof(RGBQUAD);
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = nColor;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;
	dwBmBitsSize = ((Bitmap.bmWidth  *   nColor + 31) / 32 * 4)*Bitmap.bmHeight;
	//为位图分配内存
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;
	//设置调色板
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}
	// 获取该调色板下新的像素值
	GetDIBits(hDC, hbitmap, 0, Bitmap.bmHeight,
		(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize,
		(BITMAPINFO   *)lpbi, DIB_RGB_COLORS);
	if (hOldPal)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}

	fh = CreateFileA(filename, GENERIC_WRITE,
		0,//not   be   shared   
		NULL,   //cannot   be   inherited   
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
		NULL);

	if (fh == INVALID_HANDLE_VALUE)
		return   FALSE;
	//设置位图文件头
	bmfHdr.bfType = 0x4D42;     //   "BM"   
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)
		+ (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

	//write   file   header   
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);

	//write   bmp   data   
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);

	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	DeleteObject(hbitmap);
	return TRUE;
}

void CTools::printMouseColor()
{

}

void CTools::printSystemTime()
{
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	char buffer[MAXCHAR] = { 0 };
	sprintf_s(buffer, ("SYSTEM TIME: %04d-%02d-%02d %02d:%02d:%02d"), sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	cout << buffer << endl;
}

void CTools::searchColor()
{
	for (int xi = CStcVal::s_rcRange.left; xi <= CStcVal::s_rcRange.right; xi++)
	{
		for (int yi = CStcVal::s_rcRange.top; yi <= CStcVal::s_rcRange.bottom; yi++)
		{
			CPnt5 pntFind(xi, yi, CStcVal::s_arrColor[0], CStcVal::s_arrColor[1], CStcVal::s_arrColor[2], CStcVal::s_arrColor[3], CStcVal::s_arrColor[4]);
			if (pntFind.find())
			{
				cout << "POS: " << dec << xi << ", " << yi << endl;
				return;
			}
		}
	}
}

bool CTools::findRidder()
{
	POINT p5Orgin = CStcVal::s_pnt5Rider.getPoint(EPD_MID);
	for (size_t x = 0; x < FORM_ELEMENT_NUMMAX; x++)
	{
		int iRetX = p5Orgin.x + x*FORM_ELEMENT_SIZE;
		for (size_t y = 0; y < FORM_ELEMENT_NUMMAX; y++)
		{
			int iRetY = p5Orgin.y + y*FORM_ELEMENT_SIZE;
			CPnt5 p5TMP(CStcVal::s_pnt5Rider);
			p5TMP.setMidPnt(iRetX, iRetY);
			if (p5TMP.find())
			{
				//cout << "FOUND RIDDER: (" << dec << x << "," << y << ") (" << iRetX << "," << iRetY << ")" << endl;
				p5TMP.click();
				return true;
			}
		}
	}
	return false;
}


std::string CTools::generatImgName()
{
	// for time
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	CHAR bufferName[MAXCHAR] = { 0 };
	sprintf_s(bufferName, ("%04d%02d%02d_%02d%02d_"), sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute);
	std::string strFile = SCREEN_SAVE_DIR;
	strFile.append(bufferName);
	strFile.append(CToPy::getInstance()->getMail());
	strFile.append(".bmp");
	return strFile;
}


