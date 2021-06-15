#pragma once
#include "Obj.h"

class CMovingTreeAttack : public CObj
{
public:
	explicit CMovingTreeAttack();
	virtual ~CMovingTreeAttack();
public:
	// ����
	virtual HRESULT Initialize(float fStartX, float fStartY);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
public:
	static CMovingTreeAttack* Create(float fStartX, float fStartY);
private:
	virtual void Release();
	BOOL m_bframe;
};

