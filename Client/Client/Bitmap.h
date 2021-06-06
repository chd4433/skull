#pragma once

class CBitmap
{
public:
	CBitmap();
	~CBitmap();

	// wstring�� ǥ���� �� �ִ� ���� �� ��, �ѱ��� ����

public:
	HDC GetMemDC() { return m_hMemDC; }
	HRESULT LoadBmp(wstring strPath);

private:
	void Release();

public:
	static CBitmap* Create(wstring strPath);

private:
	HDC m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
};

