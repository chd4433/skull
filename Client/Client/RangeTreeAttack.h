#pragma once
#include "Obj.h"

class CRangeTreeAttack : public CObj
{
public:
	explicit CRangeTreeAttack();
	virtual ~CRangeTreeAttack();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fStartX, float fStartY);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
public:
	static CRangeTreeAttack* Create(float fStartX, float fStartY);
private:
	virtual void Release();
	BOOL m_bframe;
};

