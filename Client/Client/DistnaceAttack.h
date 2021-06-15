#pragma once
#include "Obj.h"

class CDistnaceAttack : public CObj
{
public:
	explicit CDistnaceAttack();
	virtual ~CDistnaceAttack();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fStartX, float fStartY, BOOL bRight);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
public:
	static CDistnaceAttack* Create(float fStartX, float fStartY, BOOL bRight);
private:
	virtual void Release();
	BOOL m_bframe;
	BOOL m_bRight;
};

