#pragma once
#include "Obj.h"

class CCloseAttack1 : public CObj
{
public:
	explicit CCloseAttack1();
	virtual ~CCloseAttack1();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fStartX, float fStartY);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
public:
	static CCloseAttack1* Create(float fStartX, float fStartY);
private:
	virtual void Release();
	BOOL m_bframe;
};

