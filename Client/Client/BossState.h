#pragma once
#include "Obj.h"

class CBossState : public CObj
{
public:
	explicit CBossState();
	virtual ~CBossState();
public:
	// ±øÅë
	virtual HRESULT Initialize();
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
private:
	bool m_bRenderUI = false;
public:
	static CBossState* Create();
private:
	virtual void Release();

public:
	DWORD	BossState_Timer;
	bool	m_bGetTick = false;
};

