#pragma once
#include "Obj.h"

class CGroundTreeAttack : public CObj
{
public:
	explicit CGroundTreeAttack();
	virtual ~CGroundTreeAttack();
public:
	// ±øÅë
	virtual HRESULT Initialize();
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
public:
	static CGroundTreeAttack* Create();
	VOID TargetPlayer();
private:
	virtual void Release();
	BOOL m_bframe;
};

