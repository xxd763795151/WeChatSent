// WeChatSend.cpp : 定义控制台应用程序的入口点。
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
	char szWeChat[MAXBYTE] = "微信";
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
		cout << "请输入要发送的消息：";
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
		cout << "输入每次进行轰炸发送的信息条数：";
		cin >> nMaxNum;
		break;
	}
	default:
		break;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleTitleA("微信消息轰炸器");
	
	HWND hWnd = ::FindWindowA("WeChatMainWndForPC", "微信");
	if (!hWnd)
	{
		cout << "not find window..." << endl;
		return ERR;
	}
	while (true)
	{
		cout << "开启微信消息轰炸器..." << endl;
		cout << "1. 输入文字 \t 2.从剪切板读取 \t 3.修改一次发送条数：当前--" << nMaxNum << endl;
		int iChoice = 0;
		cin >> iChoice;
		begin(hWnd, iChoice);
		
	}

	
	system("pause");
	return 0;
}

