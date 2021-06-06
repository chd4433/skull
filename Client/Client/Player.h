#pragma once
#include "Obj.h"
#include "Enum.h"

class CPlayer : public CObj
{
public:
	enum STATE { IDLE, RUN, DASH, JUMP, FALL, ATTACK, END };

public:
	explicit CPlayer();
	virtual ~CPlayer();

public:
	SCENE_ID Get_Scene() { return CurrScene; }
	VOID Set_Scene(SCENE_ID ChangeScene) { CurrScene=ChangeScene; }
public:
	// ±øÅë
	virtual HRESULT Initialize();
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);

private:
	HRESULT ChangeState(STATE eState);

private:
	STATE m_ePreState = END;
	STATE m_eCurrState = END;
	SCENE_ID CurrScene;
	
private:
	virtual void Release();

public:
	static CPlayer* Create();

public:
	bool	m_bCharacter1;
	bool	m_bLeft;
	bool	m_bJump = false;
	bool	m_bDoubleJump = false;
	bool	m_bFall = false;
	bool	m_bDash = false;
	bool	m_bGravity = false;
	float	m_fDashLen = 0.f;
	float	m_fJumpHeight = 0.f;
	float	m_fGravityAccel = 0.f;
	float	m_fAttackCount = 0.f;
};

