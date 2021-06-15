#pragma once
#include "Obj.h"
class CMovingTree : public CObj
{
public:
	enum STATE { ATTACK, WALK, HIT, DEAD };
public:
	explicit CMovingTree();
	virtual ~CMovingTree();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fStartX, float fStartY);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
public:
	static CMovingTree* Create(float fStartX, float fStartY);
	HRESULT ChangeState(STATE eState);
	BOOL CheckWalk();
	BOOL CheckAttack();
	void SetRect();

private:
	STATE m_ePreState = DEAD;
	STATE m_eCurrState = DEAD;
private:
	virtual void Release();

private:
	bool m_bRight;
	RECT rectMovingTree;
	DWORD	Attack_Time;
	DWORD	AttackMotion_Time;
	bool m_bGetTick;
	bool m_bMotionGetTick;
	bool m_bAttackMotion;
	bool m_bDead;
	int iAttDamageBool;
};



