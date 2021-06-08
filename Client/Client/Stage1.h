#pragma once
#include "Scene.h"

class CStage1 : public CScene
{
public:
	explicit CStage1();
	~CStage1();

public:
	virtual HRESULT		Initialize();
	virtual INT 		Update(const float& fTimeDelta);
	virtual void		Render(HDC hDC);

public:
	static CStage1* Create();

private:
	float m_fTime = 0.f;
	//CImage m_pImage;

private:
	virtual void Release();
};

