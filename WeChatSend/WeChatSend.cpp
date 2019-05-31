// WeChatSend.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

#define ERR -1
#define NUM 30

int nMaxNum = NUM;

void setClip(const char* pMsg)
{
	OpenClipboard(0);
	EmptyClipboard();

	int nSize = strlen(pMsg) + 1;
	HGLOBAL hMem = ::GlobalAlloc(GHND, nSize);
	byte* pData = (byte*)::GlobalLock(hMem);
	memset(pData, 0, nSize);
	memcpy(pData, pMsg, nSize-1);
	pData[nSize - 1] = '\0';
	::GlobalUnlock(hMem);
	::SetClipboardData(CF_TEXT, hMem);
	::CloseClipboard();
	::GlobalFree(hMem);

}

BOOL CALLBACK SingleEnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	char szClassName[MAXBYTE] = { 0 };
	char szWindowsName[MAXBYTE] = { 0 };
	char szWeChat[MAXBYTE] = "΢��";
	char szBlank[MAXBYTE] = "";
	bool static bFirst = true;
	int static iNum = 0;
	::GetClassNameA(hWnd, szClassName, MAXBYTE - 1);
	if (strcmp(szClassName, "WeChatMainWndForPC") == 0)
	{
		::GetWindowTextA(hWnd, szWindowsName, MAXBYTE - 1);
		if (strcmp(szWindowsName, szWeChat) == 0 && strcmp(szWindowsName, szBlank)!=0)
		{
			if (bFirst)
			{
				bFirst = !bFirst;
				Sleep(3000);
			}
			//PostMessageA(hWnd, WM_PASTE, 0, 0);
			//SendMessageA(hWnd, WM_PASTE, 0, 0);
			//DWORD dwError = GetLastError();
			//SendMessageA(hWnd, WM_PASTE, 0, 0);
			//SendMessageA(hWnd, WM_CLOSE, 0, 0);
			//SendMessageA(hWnd, WM_KEYDOWN, VK_RETURN, 0);
			/*SendMessageA(hWnd, WM_KEYDOWN, VK_CONTROL, 0);
			SendMessageA(hWnd, WM_KEYDOWN, 86, 0);
			SendMessageA(hWnd, WM_KEYUP, 86, 0);*/

			keybd_event(0x11, 0, 0, 0);// press ctrl
			keybd_event(0x56, 0, 0, 0); // press v
			keybd_event(0x56, 0, 2, 0); //release v
			keybd_event(0x11, 0, 2, 0); //release ctrl
			keybd_event(0x0D, 0, 0, 0); //release ctrl
			keybd_event(0x0D, 0, 2, 0); //release ctrl
			//SendMessageA(hWnd, WM_KEYDOWN, VK_RETURN, 0);
			iNum++;
			if (iNum >= nMaxNum)
			{
				iNum = 0;
				bFirst = !bFirst;
				return FALSE;
			}
		}

	}
	return TRUE;
}

void send(HWND hWnd)
{
	while (true)
	{
		BOOL bRun = EnumWindows(SingleEnumWindowsProc, NULL);
		if (!bRun)
		{
			break;
		}
	}
}


void begin(HWND hWnd, int iChoice)
{
	
	switch (iChoice)
	{
	case 1:
	{
		cout << "������Ҫ���͵���Ϣ��";
		string strMsg;
		cin >> strMsg;
		setClip(strMsg.c_str());
		send(hWnd);
		break;
	}
		
	case 2:
	{
		send(hWnd);
		break;
	}
	case 3:
	{
		cout << "����ÿ�ν��к�ը���͵���Ϣ������";
		cin >> nMaxNum;
		break;
	}
	default:
		break;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleTitleA("΢����Ϣ��ը��");
	
	HWND hWnd = ::FindWindowA("WeChatMainWndForPC", "΢��");
	if (!hWnd)
	{
		cout << "not find window..." << endl;
		return ERR;
	}
	while (true)
	{
		cout << "����΢����Ϣ��ը��..." << endl;
		cout << "1. �������� \t 2.�Ӽ��а��ȡ \t 3.�޸�һ�η�����������ǰ--" << nMaxNum << endl;
		int iChoice = 0;
		cin >> iChoice;
		begin(hWnd, iChoice);
		
	}

	
	system("pause");
	return 0;
}

