#pragma once

class CBitmap;
class CBitmapMgr
{
	DECLARE_SINGLETON(CBitmapMgr)

private:
	CBitmapMgr();
	~CBitmapMgr();

public:
	HDC FindBmp(wstring strKey);
	HRESULT LoadBmp(wstring strKey, wstring strPath);
	HRESULT LoadBmpFromPath(wstring strPath);
	BOOL CheckBmp(wstring strKey);

private:
	map<wstring, CBitmap*> m_mapBmp;

private:
	VOID Release();
};

