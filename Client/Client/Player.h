#pragma once
#include "Obj.h"
#include "Enum.h"

class CPlayer : public CObj
{
public:
	enum STATE { IDLE, CHANGE, RUN, DASH, JUMP, FALL, ATTACK, SKILL, HIT,END };

public:
	explicit CPlayer();
	virtual ~CPlayer();

public:
	VOID Setbool(bool Bool) { bScrollrock = Bool; }
public:
	SCENE_ID Get_Scene() { return CurrScene; }
	VOID Set_Scene(SCENE_ID ChangeScene) { CurrScene = ChangeScene; }
	VOID SetRectPlayer(float fCX, float fCY);
	RECT GetRectPlayer() { return rectPlayer; }
public:
	// ±øÅë
	virtual HRESULT Initialize();
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);

private:
	HRESULT ChangeState(STATE eState);
	VOID	Update_Collision();
private:
	STATE m_ePreState = END;
	STATE m_eCurrState = END;
	SCENE_ID CurrScene;

private:
	virtual void Release();

public:
	static CPlayer* Create();
private:
	bool bScrollrock = false;
	RECT rectPlayer;

public:
	bool	m_bCharacter1;
	bool	m_bLeft;
	bool	m_bJump = false;
	bool	m_bDoubleJump = false;
	bool	m_bFall = false;
	bool	m_bDash = false;
	bool	m_bGravity = false;
	bool	m_bChangeCharacter = false;
	bool	m_bUsedSkill1 = false;
	bool	m_bBossFight = false;
	float	m_fChangeCount = 0.f;
	float	m_fMoveLen = 0.f;
	float	m_fDashLen = 0.f;
	float	m_fDashCount = 0.f;
	float	m_fJumpHeight = 0.f;
	float	m_fGravityAccel = 0.f;
	float	m_fAttackCount = 0.f;
	float	m_fSkillDelay = 0.f;
	int		m_iSwordAttackMotion = 0;
	int iAttDamageBool = 0;

public:
	float	m_fMapCount = 0.f;
};

