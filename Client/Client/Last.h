#pragma once
#include "Scene.h"

class CLast : public CScene
{
public:
	explicit CLast();
	~CLast();

public:
	virtual HRESULT		Initialize();
	virtual INT 		Update(const float& fTimeDelta);
	virtual void		Render(HDC hDC);

public:
	static CLast* Create();

private:
	float m_fTime = 0.f;
	wstring strName;
	//CImage m_pImage;

private:
	virtual void Release();
};

