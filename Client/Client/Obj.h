#pragma once

class CObjMgr;
class CKeyMgr;
class CBitmapMgr;
class CRenderMgr;
class CObj
{
public:
	explicit CObj();
	virtual ~CObj();

public:
	VOID SetInfoXleft() { m_tInfo.fX -= 5; }
	VOID SetInfoXright() { m_tInfo.fX += 5; }
	INFO GetInfo() { return m_tInfo; }
public:
	// ±øÅë
	virtual HRESULT Initialize();
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);

protected:
	virtual void Release();
	void UpdateRect();
	void SetFrame(wstring strKey, float fSpeed, float fCntX, float fCntY, float fX = 0.f, float fY = 0.f);
	void FrameMove(const float& fTimeDelta);

protected:
	INFO m_tInfo;
	RECT m_tRect;
	FRAME m_tFrame;

protected:
	CObjMgr* m_pObjMgr = nullptr;
	CKeyMgr* m_pKeyMgr = nullptr;
	CBitmapMgr* m_pBmpMgr = nullptr;
	CRenderMgr* m_pRenderMgr = nullptr;
};

