#pragma once
#pragma once
#include "Obj.h"

class CSwordmanSkill : public CObj
{
public:
	explicit CSwordmanSkill();
	virtual ~CSwordmanSkill();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fCurrX, float fCurrY, bool isLeft);
	virtual INT Update(const float& fTimeDelta);
	VOID Render(HDC hDC);
public:
	static CSwordmanSkill* Create(float fCurrX, float fCurrY, bool isLeft);
private:
	virtual void Release();
	BOOL m_bframe;

public:
	bool	m_bLeft;
	float	m_fDashLen;
};

