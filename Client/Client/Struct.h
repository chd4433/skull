#pragma once

typedef struct tagInfo
{
	float fX;				// ��ġ  �߽�
	float fY;
	float fCX;			// ũ �� (��¥ �� �Ѱ� ũ��)
	float fCY;
}INFO;

typedef struct tagFrame
{
	wstring strFrameKey = L"";
	float fSpeed = 0.f;						// �׸� � �ӵ��� ��������
	float fX = 0.f;								// ���� �׸�  X �ε���
	float fY = 0.f;								// ���� �׸� Y �ε���
	float fCntX = 0.f;							// X�� � �ֳ� ���η�
	float fCntY = 0.f;							// Y�� � �ֳ� ���η�
}FRAME;