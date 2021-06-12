#pragma once
#include "Obj.h"

class CGroundTreeAttack : public CObj
{
public:
	CGroundTreeAttack();
	~CGroundTreeAttack();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fStartX, float fStartY);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
private:
	virtual void Release();
};

