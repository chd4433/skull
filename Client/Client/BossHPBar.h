#pragma once
#include "Obj.h"

class CBossHPBar : public CObj
{
public:
	explicit CBossHPBar();
	virtual ~CBossHPBar();
public:
	// ±øÅë
	virtual HRESULT Initialize(int bossHP);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
private:
	bool m_bRenderUI = false;
public:
	static CBossHPBar* Create(int bossHP);
private:
	virtual void Release();

public:
	DWORD	HpBar_Timer;
	bool	m_bGetTick = false;
	int		m_ibossHP = 0;;
};

