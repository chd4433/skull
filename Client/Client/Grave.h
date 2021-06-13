#pragma once
#include "Obj.h"
class CGrave : public CObj
{
public:
	explicit CGrave();
	virtual ~CGrave();
public:
	// ±øÅë
	virtual HRESULT Initialize(float fStartX, float fStartY);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
private:
	bool m_bInterectGrave;
	bool m_bFramemove;
public:
	static CGrave* Create(float fStartX, float fStartY);
	BOOL GetbGrave() { return m_bInterectGrave; }

private:
	virtual void Release();
};