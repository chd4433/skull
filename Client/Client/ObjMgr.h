#pragma once

class CObj;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)

private:
	CObjMgr();
	~CObjMgr();

public:
	CObj* Get_Player() { return m_ObjLst[PLAYER].front(); }	// 플레이어만
	OBJLIST& Get_ObjLst(OBJID eID) {	return m_ObjLst[eID];}


public:
	HRESULT	Update(const float& fTimeDelta);

public:
	HRESULT	Add(OBJID eID, CObj* pObj);
	HRESULT	Delete(OBJID eID);
	HRESULT	Reset();

private:
	OBJLIST m_ObjLst[OBJID::OBJ_END];
};

