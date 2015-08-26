// PlayAigis.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Ctrl.h"

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hMutex = CreateMutex(NULL, FALSE, _T("PlayAigis"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hMutex);
		return FALSE;
	}

	CCtrl ctrl;
	ctrl.initHotKey();

	CloseHandle(hMutex);
	return 0;
}

