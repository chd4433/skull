#pragma once

class CBitmap
{
public:
	CBitmap();
	~CBitmap();

	// wstring이 표현할 수 있는 문자 더 많, 한국어 가능

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

