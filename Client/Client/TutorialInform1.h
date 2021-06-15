#pragma once
#include "Obj.h"

class CTutorialInform1 : public CObj
{
public:
	explicit CTutorialInform1();
	virtual ~CTutorialInform1();
public:
	// ±øÅë
	virtual HRESULT Initialize();
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
private:
	bool m_bRenderUI = false;
public:
	static CTutorialInform1* Create();
private:
	virtual void Release();
};

