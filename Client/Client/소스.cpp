#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"

#pragma comment(lib, "msimg32.lib")

#define BitmapLen 70
#define Camera_W 800
#define Camera_H 600

HINSTANCE g_hinst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"TermProject";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hinst = hinstance;

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
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(
		lpszClass,
		lpszWindowName,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		0,
		200,
		800,
		600,
		NULL,
		NULL,
		hinstance,
		NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc, memdc;
	HDC mem1dc, mem2dc;
	PAINTSTRUCT ps;
	static RECT rectView;
	TCHAR lpOut[100];//test

	static HBITMAP hBit;
	HBITMAP oldBit1, oldBit2;

	BITMAP bmp;
	// Map
	static HBITMAP map_back;
	static int map_Width, map_Height;

	// Camera
	static int camera_xPos, camera_yPos;

	// Player
	static BOOL isSwordman;				// TRUE: swordman, FALSE: alchemist
	static int player_condition;		// 0: stand, 1: walk, 2: dash, 3: jump, 4: fall, 5: attack1, 6: attack2, 7: attack3, 8: jump attack, 9: skil1, 10:skil2
	static int player_animationCount;
	static int player_xPos, player_yPos;
	static BOOL isMoveLeft, isDash, isJump, isLand, isAttack;
	static int jumpH;
	static int attackMotion;
	// Swordman
	static HBITMAP bitmap_swordman, bitmap_swordman_L;
	static int swordman_Width, swordman_Height;
	// Alchemist
	static HBITMAP bitmap_alchemist, bitmap_alchemist_L;

	switch (iMsg) {
	case WM_CREATE:
		GetClientRect(hwnd, &rectView);
		// Map
		map_back = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_MAP_BACK));
		GetObject(map_back, sizeof(BITMAP), &bmp);
		map_Width = bmp.bmWidth, map_Height = bmp.bmHeight;

		// Player
		isSwordman = TRUE;
		player_condition = 0;	// stand
		player_animationCount = 0;
		player_xPos = 100, player_yPos = 400;
		isMoveLeft = isDash = isJump = isLand = isAttack = FALSE;
		jumpH = 0;
		attackMotion = 0;

		// Swordman
		bitmap_swordman = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_CHAR_SWORDMAN));
		bitmap_swordman_L = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_CHAR_SWORDMAN_L));
		GetObject(bitmap_swordman, sizeof(BITMAP), &bmp);
		swordman_Width = bmp.bmWidth, swordman_Height = bmp.bmHeight;
		// Alchemist
		bitmap_alchemist = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_CHAR_ALCHEMIST));
		bitmap_alchemist_L = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_CHAR_ALCHEMIST_L));

		// Camera
		camera_xPos = 0, camera_yPos = 200;

		SetTimer(hwnd, 1, 100, NULL);
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			if (!isDash && !isJump && !isLand && !isAttack) {
				if (player_condition != 1) {
					isMoveLeft = TRUE;
					player_condition = 1;
				}
				if (player_xPos - 5 >= rectView.left)
					player_xPos -= 5;
			}
			break;
		case VK_RIGHT:
			if (!isDash && !isJump && !isLand && !isAttack) {
				if (player_condition != 1) {
					isMoveLeft = FALSE;
					player_condition = 1;
				}
				if (player_xPos + BitmapLen - 5 <= rectView.right)
					player_xPos += 5;
			}
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam) {
			// 이동
		case VK_LEFT:
			if (!isDash && !isJump && !isLand && !isAttack) {
				if (player_condition == 1)
					player_condition = 0;
			}
			break;
		case VK_RIGHT:
			if (!isDash && !isJump && !isLand && !isAttack) {
				if (player_condition == 1)
					player_condition = 0;
			}
			break;
			// 머리 바꾸기
		case VK_SPACE:
			if (isSwordman)
				isSwordman = FALSE;
			else
				isSwordman = TRUE;
			break;
		}
		break;
	case WM_CHAR:
		switch (wParam) {
		case 'z':		// Dash
		case 'Z':
			if (!isDash && !isJump && !isLand && !isAttack) {
				isDash = TRUE;
				if (isMoveLeft)
					player_xPos -= 50;
				else
					player_xPos += 50;

				player_condition = 2;
				player_animationCount = 0;
			}
			break;
		case 'x':		// Attack
		case 'X':
			if (!isDash && !isJump && !isLand && !isAttack) {
				isAttack = TRUE;
				if (isSwordman) {
					srand(time(NULL) * player_xPos * player_yPos);
					attackMotion = rand() % 2 + 1;
					player_condition = 5 + attackMotion;
				}
				else {
					attackMotion = 0;
					player_condition = 5;
				}
				player_animationCount = 0;
			}
			break;
		case 'c':		// Jump
		case 'C':
			if (!isDash && !isJump && !isLand && !isAttack) {
				isJump = TRUE;
				player_condition = 3;
				player_animationCount = 0;
			}
			break;
		case 'q':
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_TIMER:
		hdc = GetDC(hwnd);
		if (hBit == NULL)
			hBit = CreateCompatibleBitmap(hdc, 1920, 800);
		mem1dc = CreateCompatibleDC(hdc);			// mem1dc 는 hdc와 호환
		mem2dc = CreateCompatibleDC(mem1dc);		// memdc2 는 mem1dc와 호환

		oldBit1 = (HBITMAP)SelectObject(mem1dc, hBit);
		// 배경
		oldBit2 = (HBITMAP)SelectObject(mem2dc, map_back);
		BitBlt(mem1dc, 0, 0, Camera_W, Camera_H, mem2dc, camera_xPos, camera_yPos, SRCCOPY);

		// 카메라
		if (player_xPos - 100 <= 0)
			camera_xPos = 0;
		else if (player_xPos + 700 >= map_Width)
			camera_xPos = map_Width - 800;
		else
			camera_xPos = player_xPos - 100;
		// 플레이어
		if (isJump) {
			if (jumpH < 40) {
				player_yPos -= 40;
				jumpH += 40;
			}
			else if (jumpH < 60) {
				player_yPos -= 20;
				jumpH += 20;
			}
			else {
				player_yPos -= 10;
				jumpH += 10;
			}
			if (jumpH == 80) {
				isJump = FALSE;
				isLand = TRUE;
				player_condition = 4;
			}
		}
		if (isLand) {
			player_yPos += 40;
			jumpH -= 40;
			if (jumpH == 0) {
				isLand = FALSE;
				player_condition = 0;
				player_animationCount = 0;
			}
		}

		player_animationCount++;
		switch (player_condition) {
		case 0:		// stand
			if (isSwordman) {
				if (player_animationCount >= 4)
					player_animationCount = 0;
			}
			else {
				if (player_animationCount >= 6)
					player_animationCount = 0;
			}
			break;
		case 1:		// walk
			if (isSwordman) {
				if (player_animationCount >= 8)
					player_animationCount = 0;
			}
			else {
				if (player_animationCount >= 6)
					player_animationCount = 0;
			}
			break;
		case 2:		// dash
			if (isSwordman) {
				if (player_animationCount >= 4) {
					isDash = FALSE;
					player_condition = 0;
					player_animationCount = 0;
				}
			}
			else {
				if (player_animationCount >= 7) {
					isDash = FALSE;
					player_condition = 0;
					player_animationCount = 0;
				}
			}
			break;
		case 3:		// jump
			if (player_animationCount >= 1)
				player_animationCount = 0;
			break;
		case 4:		// land
			if (player_animationCount >= 2)
				player_animationCount = 0;
			break;
		case 5:		// attack1
			if (isSwordman) {
				if (player_animationCount >= 5) {
					isAttack = FALSE;
					player_condition = 0;
					player_animationCount = 0;
				}
			}
			else {
				if (player_animationCount >= 8) {
					isAttack = FALSE;
					player_condition = 0;
					player_animationCount = 0;
				}
			}
			break;
		case 6:
			if (player_animationCount >= 5) {
				isAttack = FALSE;
				player_condition = 0;
				player_animationCount = 0;
			}
			break;
		case 7:
			if (player_animationCount >= 6) {
				isAttack = FALSE;
				player_condition = 0;
				player_animationCount = 0;
			}
			break;
		}

		if (isSwordman) {
			if (isMoveLeft)
				oldBit2 = (HBITMAP)SelectObject(mem2dc, bitmap_swordman_L);
			else
				oldBit2 = (HBITMAP)SelectObject(mem2dc, bitmap_swordman);
		}
		else {
			if (isMoveLeft)
				oldBit2 = (HBITMAP)SelectObject(mem2dc, bitmap_alchemist_L);
			else
				oldBit2 = (HBITMAP)SelectObject(mem2dc, bitmap_alchemist);
		}
		TransparentBlt(mem1dc, player_xPos, player_yPos, BitmapLen, BitmapLen,
			mem2dc, BitmapLen * player_animationCount, BitmapLen * player_condition, BitmapLen, BitmapLen, RGB(255, 0, 255));

		SetBkMode(mem1dc, TRANSPARENT);

		SelectObject(mem2dc, oldBit2);
		DeleteDC(mem2dc);
		SelectObject(mem1dc, oldBit1);
		DeleteDC(mem1dc);

		InvalidateRgn(hwnd, NULL, false);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		mem1dc = CreateCompatibleDC(hdc);

		oldBit1 = (HBITMAP)SelectObject(mem1dc, hBit);
		BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, mem1dc, 0, 0, SRCCOPY);
		//BitBlt(hdc, 0, 0, Camera_W, Camera_H, mem1dc, camera_xPos, camera_yPos, SRCCOPY);

		SelectObject(mem1dc, oldBit1);
		DeleteDC(mem1dc);

		wsprintf(lpOut, L"P:(%d,%d) C:(%d,%d) RW:%d RH:%d, CW:%d, CH:%d", player_xPos, player_yPos, camera_xPos, camera_yPos, rectView.right, rectView.bottom, Camera_W, Camera_H);
		TextOut(hdc, 100, 500, lpOut, lstrlen(lpOut));

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}