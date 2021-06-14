#pragma once
#include "Obj.h"
class CBoss : public CObj
{
public:
	enum STATE { IDLE, ATTACK1, ATTACK2, DASH, HIT, DEAD }; 
public:
	explicit CBoss();
	virtual ~CBoss();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fStartX, float fStartY);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
public:
	static CBoss* Create(float fStartX, float fStartY);
	HRESULT ChangeState(STATE eState);
	BOOL CheckDash();
	BOOL CheckAttackA();
	void SetRect();
	int RandAttack();

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
	bool m_bAttackMotion;
	bool m_bDead;
};

