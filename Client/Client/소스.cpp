#include<Windows.h>
#include <tchar.h>
#include "math.h" 
//#include"resource.h"

HINSTANCE g_hInst;
float fx, fy;            // 싸인 곡선
const float a = 160;    // 진폭
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
	case WM_LBUTTONDOWN: //--- 마우스 클릭하면 대화상자 띄우기
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

BOOL CALLBACK Dlalog_Proc(HWND  hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int iNum = 0;
	switch (iMessage) {
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_RADIO1:
			hDC = GetDC(hWnd);
			for (int i = -(rect.right / 2); i < rect.right / 2; i++)
			{
				fx = (float)i;
				fy = (float)sin(i * 3.141592 / 180.0) * a;
				SetPixel(hDC, (int)fx + rect.right / 2, (int)fy + rect.bottom / 2, RGB(0, 0, 0));
			}
			ReleaseDC(hWnd, hDC);
			break;
		case IDC_RADIO2:
			hDC = GetDC(hWnd);
			for (int i = -(rect.right / 2); i < rect.right / 2; i++)
			{
				iNum = i;
				fx = (float)iNum;
				//if ((abs(i) % 360 <= 180))
				//{
				//	if (abs(i) %180 <= 90)
				//	{
				//		i = -i;
				//	}
				//	else
				//	{
				//		i = -i + (i - 90);
				//	}
				//}
				//else
				//{
				//	if (abs(i) % 180 <= 90)
				//	{
				//		i = -i;
				//	}
				//	else
				//	{
				//		i = -i + (i - 90);
				//	}
				//}
				//if(iNum)
				fy = (float)i;
				SetPixel(hDC, (int)fx + rect.right / 2, (int)fy + rect.bottom / 2, RGB(0, 0, 0));
			}
			ReleaseDC(hWnd, hDC);
			break;
		case IDC_RADIO3:
			break;
		case IDC_RADIO4:
			break;
		case IDC_BUTTON1:
			break;
		case IDC_BUTTON2:
			break;
		case IDC_BUTTON3:
			break;
		case IDC_BUTTON4:
			break;
		case IDC_BUTTON5:
			break;
		case IDC_CHECK1:
			break;
		case IDC_CHECK2:
			break;
		case IDC_CHECK3:
			break;
		case IDC_CHECK4:
			break;
		case IDOK: //--- 버튼
			MessageBox(hDlg, L"test", L"test, ", MB_OK);
			break;
		case IDCANCEL: //--- 버튼
			EndDialog(hDlg, 0);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	}
	return 0;
}
