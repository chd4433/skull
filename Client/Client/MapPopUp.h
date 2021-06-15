#pragma once
#include "Obj.h"

class CMapPopUp : public CObj
{
public:
	explicit CMapPopUp();
	virtual ~CMapPopUp();
public:
	// ±øÅë
	virtual HRESULT Initialize(SCENE_ID curr);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
private:
	bool m_bRenderUI = false;
public:
	static CMapPopUp* Create(SCENE_ID curr);
private:
	virtual void Release();

public:
	DWORD	 BossState_Timer;
	SCENE_ID current;
	bool	 m_bGetTick = false;
};

