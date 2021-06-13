#pragma once
#include "Obj.h"

class CEnergyball : public CObj
{
public:
	explicit CEnergyball();
	virtual ~CEnergyball();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fStartX, float fStartY, bool bDirection);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
private:
	bool m_bRenderUI = false;
public:
	static CEnergyball* Create(float fStartX, float fStartY, bool bDirection);
private:
	virtual void Release();

private:
	bool	m_bOverRange = false;
	bool	m_bLeft = false;
	float	m_fDistance = 0.f;
};

