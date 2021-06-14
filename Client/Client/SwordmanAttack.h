#pragma once
#include "Obj.h"

class CSwordmanAttack : public CObj
{
public:
	explicit CSwordmanAttack();
	virtual ~CSwordmanAttack();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fCurrX, float fCurrY, int motion, bool isLeft);
	virtual INT Update(const float& fTimeDelta);
	VOID Render(HDC hDC);
public:
	static CSwordmanAttack* Create(float fCurrX, float fCurrY, int motion, bool isLeft);
private:
	virtual void Release();
	BOOL m_bframe;

public:
	int		m_iMotion;
};

