#pragma once

class CObjMgr;
class CKeyMgr;
class CBitmapMgr;
class CRenderMgr;
class CSceneMgr;
class CScrollManager;

class CScene
{
public:
	explicit CScene();
	virtual ~CScene();

public:
	// ±øÅë
	virtual HRESULT Initialize();
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);

protected:
	virtual void Release();

protected:
	CObjMgr* m_pObjMgr = nullptr;
	CKeyMgr* m_pKeyMgr = nullptr;
	CBitmapMgr* m_pBmpMgr = nullptr;
	CRenderMgr* m_pRenderMgr = nullptr;
	CSceneMgr* m_pSCenceMgr = nullptr;
	CScrollManager* m_pScrollMgr = nullptr;
};

