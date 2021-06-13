#pragma once
#include "Scene.h"

class CStage2 : public CScene
{
public:
	explicit CStage2();
	~CStage2();

public:
	virtual HRESULT		Initialize();
	virtual INT 		Update(const float& fTimeDelta);
	virtual void		Render(HDC hDC);

public:
	static CStage2* Create();

private:
	float m_fTime = 0.f;
	//CImage m_pImage;

private:
	virtual void Release();
};

