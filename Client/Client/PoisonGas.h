#pragma once
#include "Obj.h"

class CPoisonGas : public CObj
{
public:
	explicit CPoisonGas();
	virtual ~CPoisonGas();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fStartX, float fStartY, bool bDirection);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
private:
	bool m_bRenderUI = false;
public:
	static CPoisonGas* Create(float fStartX, float fStartY, bool bDirection);
private:
	virtual void Release();

private:
	bool	m_bOverRange = false;
	bool	m_bLeft = false;
	float	m_fFrameCount = 0.f;
};

