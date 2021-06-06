#include "framework.h"
#include "RenderMgr.h"
#include "Obj.h"

IMPLEMENT_SINGLETON(CRenderMgr)

CRenderMgr::CRenderMgr()
{
}

CRenderMgr::~CRenderMgr()
{
	if (!m_RenderLst.empty())
		m_RenderLst.clear();
}

VOID CRenderMgr::Render(HDC hdc)
{
	OBJITER iter_begin = m_RenderLst.begin();
	OBJITER iter_end = m_RenderLst.end();

	for (; iter_begin != iter_end; ++iter_begin)
		(*iter_begin)->Render(hdc);

	m_RenderLst.clear();
}

HRESULT CRenderMgr::Clear()
{
	if (!m_RenderLst.empty())
		m_RenderLst.clear();

	return NOERROR;
}

HRESULT CRenderMgr::AddBack(CObj* pObj)
{
	if (pObj == nullptr)
		return E_FAIL;

	m_RenderLst.emplace_front(pObj);

	return NOERROR;
}

HRESULT CRenderMgr::AddFront(CObj* pObj)
{
	if (pObj == nullptr)
		return E_FAIL;

	m_RenderLst.emplace_back(pObj);

	return NOERROR;
}
