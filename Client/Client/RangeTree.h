#pragma once
#include "Obj.h"
class CRangeTree : public CObj
{
public:
	enum STATE { IDLE, ATTACK, HIT,DEAD };
public:
	explicit CRangeTree();
	virtual ~CRangeTree();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fStartX, float fStartY);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
public:
	static CRangeTree* Create(float fStartX, float fStartY);
	HRESULT ChangeState(STATE eState);
	BOOL CheckIdle();
	BOOL CheckAttack();
	void SetRect();

private:
	STATE m_ePreState = DEAD;
	STATE m_eCurrState = DEAD;
private:
	virtual void Release();

private:
	bool m_bRight;
	RECT rectGroundTree;
	DWORD	Attack_Time;
	DWORD	AttackMotion_Time;
	bool m_bGetTick;
	bool m_bMotionGetTick;
	bool m_bDead;
};

