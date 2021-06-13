#pragma once
#include "Obj.h"

class CThrow : public CObj
{
public:
	explicit CThrow();
	virtual ~CThrow();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fStartX, float fStartY, bool bDirection);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
private:
	bool m_bRenderUI = false;
public:
	static CThrow* Create(float fStartX, float fStartY, bool bDirection);
private:
	virtual void Release();

private:
	bool	m_bOverRange = false;
	bool	m_bLeft = false;
	float	m_fDistance = 0.f;
};

