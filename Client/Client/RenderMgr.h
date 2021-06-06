#pragma once

class CObj;
class CRenderMgr
{
	DECLARE_SINGLETON(CRenderMgr)

private:
	CRenderMgr();
	~CRenderMgr();

public:
	VOID Render(HDC hdc);

public:
	HRESULT	Clear();
	HRESULT	AddBack(CObj* pObj);
	HRESULT	AddFront(CObj* pObj);

private:
	OBJLIST		m_RenderLst;
};

