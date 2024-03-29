#pragma once

class CObjMgr;
class CKeyMgr;
class CBitmapMgr;
class CRenderMgr;
class CCollisionMgr;
class CSceneMgr;

class CObj
{
public:
	explicit CObj();
	virtual ~CObj();

public:
	VOID SetInfoXleft() { m_tInfo.fX -= 5; }
	VOID SetInfoXright() { m_tInfo.fX += 5; }
	INFO GetInfo() { return m_tInfo; }
	RECT& GetRect() { return m_tRect; }
	RECT& GetSmallRect() { return m_tSmallRect; }
	BOOL GetbChangeScene() { return b_ChangeSceneDead; }
	void SetbChangeScene() { b_ChangeSceneDead = TRUE; }
	BOOL GetbChangeSceneClose() { return b_ChangeDeadCloseAtt; }
	void SetbChangeSceneClose() { b_ChangeDeadCloseAtt = TRUE; }
	BOOL GetbPatration() { return b_Patration; }
	void SetbPatration(bool a) { b_Patration = a; }
	BOOL GetFirstCollison() { return b_Patration; } //?
	BOOL GetbPatrationAtt() { return b_ChangePatrationAtt; }
	void SetbPatrationAtt() { b_ChangePatrationAtt = TRUE; }
public:
	// ����
	virtual HRESULT Initialize();
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
	VOID SetObjScene(SCENE_ID ChangeScene) { CurrScenes = ChangeScene; }

protected:
	virtual void Release();
	void UpdateRect();
	void SetFrame(wstring strKey, float fSpeed, float fCntX, float fCntY, float fX = 0.f, float fY = 0.f);
	void FrameMove(const float& fTimeDelta);
	void SetInfo(float fCntX, float fCntY);
	void Update_Collision();
	BOOL GetbGrave() { return m_bInterectGrave; }


protected:
	INFO m_tInfo;
	RECT m_tRect;
	FRAME m_tFrame;
	SCENE_ID CurrScenes;
	RECT m_tSmallRect;

	bool m_bInterectGrave;
	bool b_ChangeSceneDead;
	bool b_ChangeDeadCloseAtt;
	bool b_Patration;
	bool b_ChangePatrationAtt;
	int iMonsterHp;
	int iPlayerHp;
	bool bFirstCollisoion;

protected:
	CObjMgr* m_pObjMgr = nullptr;
	CKeyMgr* m_pKeyMgr = nullptr;
	CBitmapMgr* m_pBmpMgr = nullptr;
	CRenderMgr* m_pRenderMgr = nullptr;
	CCollisionMgr* m_pCollisionMgr = nullptr;
	CSceneMgr* m_pSCenceMgr = nullptr;
};

