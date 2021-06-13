#include "framework.h"
#include "ObjMgr.h"
#include "Obj.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	for (int i = 0; i < OBJID::OBJ_END; ++i)
	{
		for_each(m_ObjLst[i].begin(), m_ObjLst[i].end(), SafeDelete<CObj*>);
		m_ObjLst[i].clear();
	}
}

CObj* CObjMgr::Get_SingleObjLst(OBJID eID)
{
	if(m_ObjLst[eID].empty())
		return nullptr;
	return m_ObjLst[eID].front(); 
}

HRESULT CObjMgr::Update(const float& fTimeDelta)
{
	for (int i = 0; i < OBJID::OBJ_END; ++i)
	{
		OBJITER iter_begin = m_ObjLst[i].begin();
		OBJITER iter_end = m_ObjLst[i].end();

		for (; iter_begin != iter_end; )
		{
			// 뒤졌을때 지우기
			if (OBJ_DEAD == (*iter_begin)->Update(fTimeDelta))
			{
				SafeDelete(*iter_begin);
				iter_begin = m_ObjLst[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}

	return NOERROR;
}

HRESULT CObjMgr::Add(OBJID eID, CObj* pObj)
{
	if (nullptr == pObj)
		return E_FAIL;

	m_ObjLst[eID].push_back(pObj);

	return NOERROR;
}

HRESULT CObjMgr::Delete(OBJID eID)
{
	for_each(m_ObjLst[eID].begin(), m_ObjLst[eID].end(), SafeDelete<CObj*>);
	m_ObjLst[eID].clear();

	return S_OK;
}

HRESULT CObjMgr::Reset()
{
	for (int i = 0; i < OBJID::OBJ_END; ++i)
	{
		for_each(m_ObjLst[i].begin(), m_ObjLst[i].end(), SafeDelete<CObj*>);
		m_ObjLst[i].clear();
	}

	return NOERROR;
}
