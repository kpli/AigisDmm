#include "stdafx.h"
#include "Ctrl.h"
#include "Frame.h"
#include "Tools.h"
#include "Logic.h"

bool CCtrl::s_bEffect = true;
CHAR CCtrl::s_gameurl[MAX_PATH] = { 0 };

#define GET_COLOR_DEBUG_MODE	0

CCtrl::CCtrl()
{
#if GET_COLOR_DEBUG_MODE
	cout << "Alt+F1 GET COLOR" << endl;
	cout << "Alt+(F7|F8) (SEARCH RANGE X|Y)" << endl;
#endif
	cout << "Alt+(F2|F10|F12) (TEST|START|STOP)" << endl;
}


CCtrl::~CCtrl()
{
}

void CCtrl::initHotKey()
{
	if (!RegisterHotKey(NULL, VK_F10, MOD_ALT | MOD_NOREPEAT, VK_F10))
		cout << "RegisterHotKey error, key: " << hex << VK_F10 << endl;
	if (!RegisterHotKey(NULL, VK_F12, MOD_ALT | MOD_NOREPEAT, VK_F12))
		cout << "RegisterHotKey error, key: " << hex << VK_F12 << endl;

#if GET_COLOR_DEBUG_MODE
	RegisterHotKey(NULL, VK_F1, MOD_ALT | MOD_NOREPEAT, VK_F1);
	RegisterHotKey(NULL, VK_F7, MOD_ALT | MOD_NOREPEAT, VK_F7);
	RegisterHotKey(NULL, VK_F8, MOD_ALT | MOD_NOREPEAT, VK_F8);
#endif
	RegisterHotKey(NULL, VK_F2, MOD_ALT | MOD_NOREPEAT, VK_F2);

	MSG msg = {0};  
	while (GetMessage(&msg, NULL, 0, 0) != 0)  
	{  
		if (msg.message == WM_HOTKEY)  
		{ 
			WORD wPressed = HIWORD(msg.lParam);
			switch (wPressed)
			{
			case VK_F10:
				start();
				break;
			case VK_F12:
				stop();
				break;
			case VK_F2:
				//CTools::getInstance()->findRidder();
				//CTools::getInstance()->searchColor();
				test();
				break;
#if GET_COLOR_DEBUG_MODE
			case VK_F1:
				CFrame::getInstance()->logColor();
				break;
			case VK_F7:
				CFrame::getInstance()->setRangeLT();
				break;
			case VK_F8:
				CFrame::getInstance()->setRangeRB();
				break;
#endif
			default:
				break;
			}
		}  
	}   

	UnregisterHotKey(NULL, VK_F10);
	UnregisterHotKey(NULL, VK_F12);
#if GET_COLOR_DEBUG_MODE
	UnregisterHotKey(NULL, VK_F1);
	UnregisterHotKey(NULL, VK_F7);
	UnregisterHotKey(NULL, VK_F8);
#endif
	UnregisterHotKey(NULL, VK_F2);
}

void CCtrl::start()
{
	CCtrl::s_bEffect = true;
	CLogic::getInstance()->startPlay();
}

void CCtrl::stop()
{
	CCtrl::s_bEffect = false;
}

bool CCtrl::canPlay()
{
	return CCtrl::s_bEffect;
}

void CCtrl::test()
{
	CCtrl::s_bEffect = true;
	CLogic::getInstance()->startTest();
}

const CHAR* CCtrl::getURL()
{
	if (s_gameurl[0] != '\0')
	{
		return s_gameurl;
	}

	TCHAR szModuleFileName[MAX_PATH]; // 全路径名
	TCHAR drive[_MAX_DRIVE];  // 盘符名称，比如说C盘啊，D盘啊
	TCHAR dir[_MAX_DIR]; // 目录
	TCHAR fname[_MAX_FNAME];  // 进程名字
	TCHAR ext[_MAX_EXT]; //后缀，一般为exe或者是dll
	if (NULL == GetModuleFileName(NULL, szModuleFileName, MAX_PATH)) //获得当前进程的文件路径
		return s_gameurl;
	_tsplitpath_s(szModuleFileName, drive, dir, fname, ext);  //分割该路径，得到盘符，目录，文件名，后缀名

	TCHAR szPath[MAX_PATH];
	_tcscpy_s(szPath, drive);
	_tcscat_s(szPath, dir);
	_tcscat_s(szPath, _T("game_url.txt"));

	HANDLE hFile;
	hFile = CreateFileW(szPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwReads;
	ReadFile(hFile, s_gameurl, MAX_PATH, &dwReads, NULL);
	CloseHandle(hFile);
	s_gameurl[dwReads] = 0;


	return s_gameurl;
}



