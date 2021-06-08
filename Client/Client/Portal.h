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
public:
	static CPortal* Create(float fStartX, float fStartY);

private:
	virtual void Release();
};

