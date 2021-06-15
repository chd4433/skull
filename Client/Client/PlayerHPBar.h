#pragma once
#include "Obj.h"

class CPlayerHPBar : public CObj
{
public:
	explicit CPlayerHPBar();
	virtual ~CPlayerHPBar();
public:
	// ±øÅë
	virtual HRESULT Initialize(int playerHP);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
private:
	bool m_bRenderUI = false;
public:
	static CPlayerHPBar* Create(int playerHP);
private:
	virtual void Release();

public:
	DWORD	HpBar_Timer;
	bool	m_bGetTick = false;
	int		m_iPlayerHP;
};

