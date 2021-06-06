#pragma once
#include "Obj.h"
#include "Enum.h"

class CThrow : public CObj
{
public:
	enum STATE { IDLE, END };

public:
	explicit CThrow();
	virtual ~CThrow();

public:
	SCENE_ID Get_Scene() { return CurrScene; }
	VOID Set_Scene(SCENE_ID ChangeScene) { CurrScene = ChangeScene; }
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
	static CThrow* Create();
};

