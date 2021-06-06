#pragma once

typedef struct tagInfo
{
	float fX;				// 위치  중심
	float fY;
	float fCX;			// 크 기 (진짜 딱 한개 크기)
	float fCY;
}INFO;

typedef struct tagFrame
{
	wstring strFrameKey = L"";
	float fSpeed = 0.f;						// 그림 어떤 속도로 돌릴건지
	float fX = 0.f;								// 현재 그림  X 인덱스
	float fY = 0.f;								// 현재 그림 Y 인덱스
	float fCntX = 0.f;							// X로 몇개 있나 가로로
	float fCntY = 0.f;							// Y로 몇개 있나 세로로
}FRAME;