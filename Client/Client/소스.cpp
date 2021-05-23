#include<Windows.h>
#include <tchar.h>
#include "math.h" 
//#include"resource.h"

HINSTANCE g_hInst;
float fx, fy;            // ½ÎÀÎ °î¼±
const float a = 160;    // ÁøÆø
HDC hDC;
HWND hWnd;
RECT rect;


LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 6-1";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlalog_Proc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, PSTR szCmdLine, int iCmdShow)
{
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hinstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hinstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassExW(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 0, 0, 800, 800, NULL, (HMENU)NULL, hinstance, NULL);
	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		GetClientRect(hWnd, &rect);
		break;
	case WM_LBUTTONDOWN: //--- ¸¶¿ì½º Å¬¸¯ÇÏ¸é ´ëÈ­»óÀÚ ¶ç¿ì±â
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dlalog_Proc);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		MoveToEx(hDC, rect.left, rect.bottom / 2, NULL);
		LineTo(hDC, rect.right, rect.bottom / 2);
		MoveToEx(hDC, rect.right / 2, rect.top, NULL);
		LineTo(hDC, rect.right / 2, rect.bottom);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

