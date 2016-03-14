#include "stdafx.h"
#include "Logic.h"
#include "Ctrl.h"
#include "Frame.h"
#include "Tools.h"
#include <process.h>

#define LOOP_BEGIN	size_t bt = GetTickCount();	while (CCtrl::canPlay() && canWait() && validTitle()) {
#define LOOP_END(sec)	DetectTimeout(bt, sec);}

title_state CLogic::s_titleState = ts_null;
bool CLogic::s_bWaitFor = true;
int CLogic::s_iCardStar = 0;
CLogic::CLogic()
{
}


CLogic::~CLogic()
{

}

CLogic* CLogic::getInstance()
{
	static CLogic ret;
	return &ret;
}

void CLogic::startPlay()
{
	uintptr_t hStdOut = _beginthread(ThreadPlaying, 0, NULL);
}

void CLogic::startTest()
{
	uintptr_t hStdOut = _beginthread(ThreadTest, 0, NULL);
}

void CLogic::ThreadPlaying(void *)
{
	cout << "::START::" << endl;
	while (CCtrl::canPlay())
	{
 		getInstance()->startRegist();
 		getInstance()->waitTime(10);	// 等待注册
		
		getInstance()->FirstRondomCard();
		getInstance()->SecondRondomCard();

		if (CCtrl::canPlay())
		{
			CFrame::getInstance()->closeChrome();
			for (int i = 0; i < 10; i++)
				Sleep(100);
		}
	}
	cout << "\r\n::STOP::" << endl;
	_endthread();
}

void CLogic::startRegist()
{
	const CHAR* pURL = CCtrl::getURL();
	CLogic::s_titleState = ts_null;
	CLogic::s_bWaitFor = true;
	ShellExecuteA(NULL, 
		("open"), 
		("chrome.exe"), 
		pURL,
		(""), 
		SW_SHOW);
	cout << "R";
}

void CLogic::playStory1()
{
	cout << 1;
	waitRole_bySpeedup(&CStcVal::s_GameSpeed1, &CStcVal::s_ST1_Role1);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed1, &CStcVal::s_ST1_Role2);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed1, &CStcVal::s_ST1_Role3);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed1, &CStcVal::s_ST1_Role4);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed1, &CStcVal::s_ST1_Role5);
	waitOK_bySpeedup(&CStcVal::s_GameSpeed1);
}

void CLogic::playStory2()
{
	cout << 2;
	waitRole_bySpeedup(&CStcVal::s_GameSpeed2, &CStcVal::s_ST2_Role1);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed2, &CStcVal::s_ST2_Role2);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed2, &CStcVal::s_ST2_Role3);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed2, &CStcVal::s_ST2_Role4);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed2, &CStcVal::s_ST2_Role5);
	waitOK_bySpeedup(&CStcVal::s_GameSpeed2);
}

void CLogic::playStory3()
{
	cout << 3;
	waitRole_bySpeedup(&CStcVal::s_GameSpeed3, &CStcVal::s_ST3_Role1);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed3, &CStcVal::s_ST3_Role2);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed3, &CStcVal::s_ST3_Role3);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed3, &CStcVal::s_ST3_Role4);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed3, &CStcVal::s_ST3_Role5);
	waitOK_bySpeedup(&CStcVal::s_GameSpeed3);
}

void CLogic::waitIcon_nothing()
{
	cout << ".";
	waitPnt_clickPnt(nullptr, &CStcVal::s_GameIcon);
}

void CLogic::waitEntry_clickOK()
{
	waitPnt_clickPnt(&CStcVal::s_GameBtnOK, &CStcVal::s_GameStory);
}

void CLogic::waitEntry_clickBack()
{
	waitPnt_clickPnt(&CStcVal::s_GameBtnBack, &CStcVal::s_GameStory);
}

void CLogic::waitBack_clickOK()
{
	waitPnt_clickPnt(&CStcVal::s_GameBtnOK, &CStcVal::s_GameBtnBack);
}

void CLogic::waitBound_clickOK()
{
	waitPnt_clickPnt(&CStcVal::s_GameBtnOK, &CStcVal::s_Bounding1, false);
	waitPnt_clickPnt(&CStcVal::s_Bounding1, &CStcVal::s_Bounding2);
	waitPnt_clickPnt(nullptr, &CStcVal::s_Bounding3);
	waitPnt_clickPnt(nullptr, &CStcVal::s_Bounding4);
}

void CLogic::waitCard_clickOK()
{
	cout << "^";
	waitPnt_clickPnt(&CStcVal::s_GameBtnOK, &CStcVal::s_Random1, false);
	waitPnt_clickPnt(nullptr, &CStcVal::s_Random2, false);
	waitPnt_clickPnt(&CStcVal::s_Random2, &CStcVal::s_Random3);
	waitPnt_clickPnt(nullptr, &CStcVal::s_Random4);
}
void CLogic::waitCard_clickOK2()
{
	cout << "^";
	waitPnt_clickPnt(&CStcVal::s_GameBtnOK, &CStcVal::s_GameBtnBack);
	waitPnt_clickPnt(nullptr, &CStcVal::s_Random2, false);
	waitPnt_clickPnt(&CStcVal::s_Random2, &CStcVal::s_Random3);
	waitPnt_clickPnt(nullptr, &CStcVal::s_Random4);
}


void CLogic::waitPnt_clickPnt(CPnt5* pClick, CPnt5* pWait, bool bfirst)
{
	LOOP_BEGIN
		if (pClick)
			pClick->click();
		if (pWait->find())
		{
			if (bfirst)
			{
				LOOP_BEGIN
					if (!pWait->find())
					{
						break;
					}
					else
					{
						Sleep(200);
						pWait->click();
						Sleep(200);
					}
				LOOP_END(TIMEOUT_MAX_SECONDS)
			}
			else
			{
				Sleep(200);
				pWait->click();
				Sleep(200);
			}
			break;
		}
	LOOP_END(TIMEOUT_MAX_SECONDS)
}

void CLogic::waitRole_bySpeedup(CPnt5* pntSpeed, CRolePnt* role, bool bfirst)
{
	LOOP_BEGIN
		clickSpeedUp(pntSpeed);
		if (role->p5.find())
		{
			if (bfirst)
			{
				LOOP_BEGIN
					if (!role->p5.find())
					{
						break;
					}
					else
					{
						role->drag();
						Sleep(200);
					}
				LOOP_END(TIMEOUT_MAX_SECONDS)
			}
			else
			{
				role->drag();
				Sleep(200);
			}
			break;
		}
	LOOP_END(TIMEOUT_MAX_SECONDS)
}


void CLogic::waitOK_bySpeedup(CPnt5* pntSpeed)
{
	LOOP_BEGIN
		clickSpeedUp(pntSpeed);
		if (CStcVal::s_GameBtnOK.find())
		{
			Sleep(200);
			CStcVal::s_GameBtnOK.click();
			break;
		}
	LOOP_END(TIMEOUT_MAX_SECONDS)
}

void CLogic::clickSpeedUp(CPnt5* pntSpeed)
{
	if (!pntSpeed)
	{
		return;
	}
	if (!pntSpeed->find())
	{
		pntSpeed->click();
	}
}

void CLogic::waitCard()
{
	s_iCardStar = 0;
	LOOP_BEGIN
		Sleep(20);
		if (CStcVal::s_CardSilver.find())
			s_iCardStar = 1;
		if (CStcVal::s_CardGold.find())
			s_iCardStar = 2;
		if (CStcVal::s_CardWhite.find())
			s_iCardStar = 3;
		if (CStcVal::s_CardBlack.find())
			s_iCardStar = 4;
		if (s_iCardStar > 0)
		{
			cout << "; ";
			waitTime(s_iCardStar);
			if (s_iCardStar > 3)
			{
				SYSTEMTIME sysTime;
				GetLocalTime(&sysTime);
				char buffer[MAXCHAR] = { 0 };
				sprintf_s(buffer, (": %04d-%02d-%02d %02d:%02d:%02d !!!GOLD!!! "), sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
				cout << "\r\n" << ((s_iCardStar == 4) ? "__BLACK__" : "__WHITE__") << buffer << endl;
			}
			break;
		}
	LOOP_END(TIMEOUT_MAX_SECONDS)
}

void CLogic::waitTime(size_t nseconds)
{
	LOOP_BEGIN
		Sleep(100);
		size_t dt = GetTickCount() - bt;
		if (dt >= nseconds*1000)
		{
			break;
		}
	}
}

void CLogic::DetectTimeout(size_t bt, size_t iSecs)
{
	size_t dt = GetTickCount() - bt;
	if (dt >= iSecs * 1000)
	{
		CLogic::s_bWaitFor = false;		// 结束本次首抽，进行下一轮
		cout << "*" ;
	}
}


bool CLogic::canWait()
{
	return CLogic::s_bWaitFor;
}

bool CLogic::validTitle()
{
	if(ts_null == s_titleState)
	{
		TCHAR bufferTitle[MAXCHAR] = { 0 };
		int nLen = CFrame::getInstance()->getChromeTitle(bufferTitle, MAXCHAR);

		if (_tcscmp(bufferTitle, _T("empty")) == 0)
		{
			s_titleState = ts_empty;
		}
		for (int i = 1; i < nLen; i++)
		{
			if (bufferTitle[i] == '@')
			{
				s_titleState = ts_valid;
				break;
			}
		}
	}
	return (s_titleState != ts_empty);
}


void CLogic::selectUnit()
{
	waitPnt_clickPnt(&CStcVal::s_GameBtnBack, &CStcVal::s_GameUnit1, false);
	waitPnt_clickPnt(nullptr, &CStcVal::s_GameUnit2, false);
	//waitPnt_clickPnt(&CStcVal::s_GameUnit2, &CStcVal::s_GameUnit3);
	waitPnt_clickPnt(nullptr, &CStcVal::s_GameUnit3);
	waitPnt_clickPnt(nullptr, &CStcVal::s_GameUnit4);
	waitTime(1);
	CTools::getInstance()->findRidder();
	waitPnt_clickPnt(nullptr, &CStcVal::s_GameUnit5);
}


void CLogic::playStory4()
{
	cout << 4;
	waitRole_bySpeedup(&CStcVal::s_GameSpeed4, &CStcVal::s_ST4_Role1);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed4, &CStcVal::s_ST4_Role2);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed4, &CStcVal::s_ST4_Role3);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed4, &CStcVal::s_ST4_Role4);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed4, &CStcVal::s_ST4_Role5);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed4, &CStcVal::s_ST4_Role6);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed4, &CStcVal::s_ST4_Role7);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed4, &CStcVal::s_ST4_Role8);
	waitOK_bySpeedup(&CStcVal::s_GameSpeed4);
}

void CLogic::playStory5()
{
	cout << 5;
	waitRole_bySpeedup(&CStcVal::s_GameSpeed5, &CStcVal::s_ST5_Role1);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed5, &CStcVal::s_ST5_Role2);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed5, &CStcVal::s_ST5_Role3);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed5, &CStcVal::s_ST5_Role4);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed5, &CStcVal::s_ST5_Role5);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed5, &CStcVal::s_ST5_Role6);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed5, &CStcVal::s_ST5_Role7);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed5, &CStcVal::s_ST5_Role8);
	waitOK_bySpeedup(&CStcVal::s_GameSpeed5);
}

void CLogic::playStory6()
{
	cout << 6;
	waitRole_bySpeedup(&CStcVal::s_GameSpeed6, &CStcVal::s_ST6_Role1);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed6, &CStcVal::s_ST6_Role2);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed6, &CStcVal::s_ST6_Role3);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed6, &CStcVal::s_ST6_Role4);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed6, &CStcVal::s_ST6_Role5);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed6, &CStcVal::s_ST6_Role6);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed6, &CStcVal::s_ST6_Role7);
	waitOK_bySpeedup(&CStcVal::s_GameSpeed6);
}

void CLogic::playStory7()
{
	cout << 7;
	waitRole_bySpeedup(&CStcVal::s_GameSpeed7, &CStcVal::s_ST7_Role1);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed7, &CStcVal::s_ST7_Role2);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed7, &CStcVal::s_ST7_Role3);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed7, &CStcVal::s_ST7_Role4);
	waitRole_bySpeedup(&CStcVal::s_GameSpeed7, &CStcVal::s_ST7_Role5);
	waitOK_bySpeedup(&CStcVal::s_GameSpeed7);
}

void CLogic::ThreadTest(void *)
{
	cout << "::TEST_START::" << endl;
	while (CCtrl::canPlay())
	{
		s_iCardStar = 4;
		CLogic::s_titleState = ts_null;
		CLogic::s_bWaitFor = true;
		getInstance()->SecondRondomCard();

	}
	cout << "\r\n::TEST_STOP::" << endl;
	_endthread();
}

void CLogic::selectStory4567(CPnt5* pStoryEntry, bool bMustScroll)
{
	waitEntry_clickBack();
	Sleep(300);
	waitPnt_clickPnt(nullptr, &CStcVal::s_SelectStory0_1);
	Sleep(300);
	if(bMustScroll)
		waitPnt_clickPnt(&CStcVal::s_scrollCtrl, pStoryEntry);
	else
		waitPnt_clickPnt(nullptr, pStoryEntry);
	Sleep(300);
	waitPnt_clickPnt(nullptr, &CStcVal::s_SelectStory0_3);
	Sleep(300);
	waitPnt_clickPnt(nullptr, &CStcVal::s_SelectStory0_4);
}

void CLogic::FirstRondomCard()
{
	getInstance()->waitIcon_nothing();
	getInstance()->playStory1();
	getInstance()->waitEntry_clickOK();
	getInstance()->playStory2();
	getInstance()->waitBound_clickOK();
	getInstance()->waitEntry_clickBack();
	getInstance()->playStory3();
	getInstance()->waitCard_clickOK();
	getInstance()->waitCard();	// 等待抽卡完成
	if (s_iCardStar > 3 )
		CFrame::getInstance()->saveImage();
}

void CLogic::SecondRondomCard()
{
	//不进行二抽，不值钱
	if (s_iCardStar < 4)
	{
		return;
	}
	selectUnit();
	selectStory4567(&CStcVal::s_SelectStory4_2);
	playStory4();
	
	waitPnt_clickPnt(&CStcVal::s_GameBtnOK, &CStcVal::s_Random1, false);
	selectStory4567(&CStcVal::s_SelectStory5_2);
	playStory5();
	
	waitBack_clickOK();
	selectStory4567(&CStcVal::s_SelectStory6_2, true);
	playStory6();

	waitBack_clickOK();
	selectStory4567(&CStcVal::s_SelectStory7_2, true);
	playStory7();

	waitCard_clickOK2();
	waitCard();	// 等待抽卡完成
	CFrame::getInstance()->saveImage();
}

