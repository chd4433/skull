#pragma once
#include "Scene.h"

class CSceneLogo : public CScene
{
public:
	explicit CSceneLogo();
	virtual ~CSceneLogo();

public:
	// ±øÅë
	virtual HRESULT Initialize();
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);

private:
	virtual void Release();

public:
	static CSceneLogo* Create();
};

