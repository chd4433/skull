#pragma once
#include "Obj.h"

class CDiePopUp : public CObj
{
public:
	explicit CDiePopUp();
	virtual ~CDiePopUp();
public:
	// ±øÅë
	virtual HRESULT Initialize(int Count);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
private:
	bool m_bRenderUI = false;
public:
	static CDiePopUp* Create(int Count);
private:
	virtual void Release();

public:
	DWORD	Popup_Time;
	bool	m_bGetTick = false;
	int		m_iCount = 5;
};

