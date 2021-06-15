#pragma once
#include "Obj.h"
class CShotedPlayer : public CObj
{
public:
	explicit CShotedPlayer();
	virtual ~CShotedPlayer();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fStartX, float fStartY);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
private:
	bool m_bInterectGrave;
	bool m_bFramemove;
public:
	static CShotedPlayer* Create(float fStartX, float fStartY);
	BOOL GetbGrave() { return m_bInterectGrave; }
	VOID TargetPlayer();

private:
	virtual void Release();
};