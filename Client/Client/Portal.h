#pragma once
#include "Obj.h"
class CPortal : public CObj
{
public:
	explicit CPortal();
	virtual ~CPortal();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fStartX, float fStartY);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
private:
	bool m_bRenderUI = false;
	SCENE_ID m_ePreState = SCENE_END;
	SCENE_ID m_eCurrState = SCENE_END;
public:
	static CPortal* Create(float fStartX, float fStartY);
	HRESULT ChangeScene(SCENE_ID eState);

private:
	virtual void Release();
};

