#pragma once
#include "Scene.h"

class CTutorialStage : public CScene
{
public:
	explicit CTutorialStage();
	~CTutorialStage();

public:
	virtual HRESULT		Initialize();
	virtual INT 		Update(const float& fTimeDelta);
	virtual VOID		Render(HDC hDC);

public:
	static CTutorialStage* Create();

private:
	float m_fTime = 0.f;
	//CImage m_pImage;

private:
	virtual void Release();
};

