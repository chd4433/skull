#pragma once

class CSceneMgr;
class CBitmapMgr;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	HRESULT Initialize();
	INT Update(const float& fTimeDelta);
	VOID Render();

private:
	HDC m_hDC;

private:
	HDC m_hMemDC;
	HDC m_hBackDC;

private:
	CObjMgr* m_pObjMgr = nullptr;
	CKeyMgr* m_pKeyMgr = nullptr;
	CBitmapMgr* m_pBmpMgr = nullptr;
	CSceneMgr* m_pSceneMgr = nullptr;
	CCollisionMgr* m_pCollisionMgr = nullptr;

public:
	static CMainGame* Create();
	VOID Release();
};

