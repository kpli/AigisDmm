#include "stdafx.h"
#include "Ctrl.h"
#include "Frame.h"
#include "Tools.h"
#include "Logic.h"

bool CCtrl::s_bEffect = true;

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



