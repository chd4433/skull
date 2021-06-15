#pragma once
#include "Obj.h"

class CPlayerState : public CObj
{
public:
	explicit CPlayerState();
	virtual ~CPlayerState();
public:
	// ±øÅë
	virtual HRESULT Initialize(int playerType);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
private:
	bool m_bRenderUI = false;
public:
	static CPlayerState* Create(int playerType);
private:
	virtual void Release();

public:
	DWORD	PlayerState_Timer;
	bool	m_bGetTick = false;
	int		m_iplayerType;
};

