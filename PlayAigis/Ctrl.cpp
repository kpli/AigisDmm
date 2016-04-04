#include "stdafx.h"
#include "Ctrl.h"
#include "Frame.h"
#include "Tools.h"
#include "Logic.h"

bool CCtrl::s_bEffect = true;
CHAR CCtrl::s_gameurl1[MAX_PATH] = { 0 };
CHAR CCtrl::s_gameurl2[MAX_PATH] = { 0 };


CCtrl::CCtrl()
{
#ifdef AIGIS_TOOL
	cout << "Alt+F1 GET COLOR" << endl;
	cout << "Alt+F2 FIND COLOR" << endl;
	cout << "Alt+(F7|F8) (SEARCH RANGE X|Y)" << endl;
	cout << "Alt+(F10|F12) (TEST|STOP)" << endl;
#endif // AIGIS_TOOL
#ifdef AIGIS_RUSH
	cout << "AUTO RUSH FOR BLACK CARDS:" << endl;
#endif
#ifdef AIGIS_SEC
	cout << "AUTO PLAY FOR SECOND RANDOM:" << endl;
#endif
}


CCtrl::~CCtrl()
{
}

void CCtrl::initHotKey()
{
#ifdef AIGIS_RUSH
	start();
#endif
#ifdef AIGIS_SEC
	start();
#endif
#ifdef AIGIS_TOOL
	if (!RegisterHotKey(NULL, VK_F10, MOD_ALT | MOD_NOREPEAT, VK_F10))
		cout << "RegisterHotKey error, key: " << hex << VK_F10 << endl;
	if (!RegisterHotKey(NULL, VK_F12, MOD_ALT | MOD_NOREPEAT, VK_F12))
		cout << "RegisterHotKey error, key: " << hex << VK_F12 << endl;

	RegisterHotKey(NULL, VK_F1, MOD_ALT | MOD_NOREPEAT, VK_F1);
	RegisterHotKey(NULL, VK_F7, MOD_ALT | MOD_NOREPEAT, VK_F7);
	RegisterHotKey(NULL, VK_F8, MOD_ALT | MOD_NOREPEAT, VK_F8);
	RegisterHotKey(NULL, VK_F2, MOD_ALT | MOD_NOREPEAT, VK_F2);

	MSG msg = {0};  
	while (GetMessage(&msg, NULL, 0, 0) != 0)  
	{  
		if (msg.message == WM_HOTKEY)  
		{ 
			WORD wPressed = HIWORD(msg.lParam);
			switch (wPressed)
			{
			case VK_F1:
				CFrame::getInstance()->logColor();
				break;
			case VK_F2:
				CTools::getInstance()->searchColor();
				break;
			case VK_F7:
				CFrame::getInstance()->setRangeLT();
				break;
			case VK_F8:
				CFrame::getInstance()->setRangeRB();
				break;
			case VK_F10:
				test();
				break;
			case VK_F12:
				stop();
				break;
			default:
				break;
			}
		}  
	}   

	UnregisterHotKey(NULL, VK_F10);
	UnregisterHotKey(NULL, VK_F12);
	UnregisterHotKey(NULL, VK_F1);
	UnregisterHotKey(NULL, VK_F7);
	UnregisterHotKey(NULL, VK_F8);
	UnregisterHotKey(NULL, VK_F2);
#else
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		Sleep(1000);
	}
#endif // AIGIS_TOOL
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

const CHAR* CCtrl::getURL1()
{
	if (s_gameurl1[0] != '\0')
	{
		return s_gameurl1;
	}

	TCHAR szModuleFileName[MAX_PATH]; // 全路径名
	TCHAR drive[_MAX_DRIVE];  // 盘符名称，比如说C盘啊，D盘啊
	TCHAR dir[_MAX_DIR]; // 目录
	TCHAR fname[_MAX_FNAME];  // 进程名字
	TCHAR ext[_MAX_EXT]; //后缀，一般为exe或者是dll
	if (NULL == GetModuleFileName(NULL, szModuleFileName, MAX_PATH)) //获得当前进程的文件路径
		return s_gameurl1;
	_tsplitpath_s(szModuleFileName, drive, dir, fname, ext);  //分割该路径，得到盘符，目录，文件名，后缀名

	TCHAR szPath[MAX_PATH];
	_tcscpy_s(szPath, drive);
	_tcscat_s(szPath, dir);
	_tcscat_s(szPath, _T("game_url1.txt"));

	HANDLE hFile;
	hFile = CreateFileW(szPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwReads;
	ReadFile(hFile, s_gameurl1, MAX_PATH, &dwReads, NULL);
	CloseHandle(hFile);
	s_gameurl1[dwReads] = 0;


	return s_gameurl1;
}

const CHAR* CCtrl::getURL2()
{
	if (s_gameurl2[0] != '\0')
	{
		return s_gameurl2;
	}

	TCHAR szModuleFileName[MAX_PATH]; // 全路径名
	TCHAR drive[_MAX_DRIVE];  // 盘符名称，比如说C盘啊，D盘啊
	TCHAR dir[_MAX_DIR]; // 目录
	TCHAR fname[_MAX_FNAME];  // 进程名字
	TCHAR ext[_MAX_EXT]; //后缀，一般为exe或者是dll
	if (NULL == GetModuleFileName(NULL, szModuleFileName, MAX_PATH)) //获得当前进程的文件路径
		return s_gameurl2;
	_tsplitpath_s(szModuleFileName, drive, dir, fname, ext);  //分割该路径，得到盘符，目录，文件名，后缀名

	TCHAR szPath[MAX_PATH];
	_tcscpy_s(szPath, drive);
	_tcscat_s(szPath, dir);
	_tcscat_s(szPath, _T("game_url2.txt"));

	HANDLE hFile;
	hFile = CreateFileW(szPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwReads;
	ReadFile(hFile, s_gameurl2, MAX_PATH, &dwReads, NULL);
	CloseHandle(hFile);
	s_gameurl2[dwReads] = 0;


	return s_gameurl2;
}



