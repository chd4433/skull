#pragma once
#include "Obj.h"

class CCloseAttack2 : public CObj
{
public:
	explicit CCloseAttack2();
	virtual ~CCloseAttack2();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fStartX, float fStartY);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
public:
	static CCloseAttack2* Create(float fStartX, float fStartY);
private:
	virtual void Release();
	BOOL m_bframe;
};

