#pragma once

#include "Obj.h"

class CCollisionMgr
{
	DECLARE_SINGLETON(CCollisionMgr)
public:
	CCollisionMgr() = default;
	~CCollisionMgr();

public:
	static bool Check_IntersectRect(CObj* pDst, CObj* pSrc);
	static bool Check_ObjRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY);
	static bool Check_Rect(RECT tDst, RECT tSrc, float* pMoveX, float* pMoveY);
	static bool Check_Sphere(CObj* pDst, CObj* pSrc);
	bool CollisionPlayertoMonster(list<CObj*> Dst, list<CObj*> Src);
public:

	HRESULT LoadCollisionFromPath(wstring strPath);
	HRESULT AddCollision(RECT* pRect);
	list<RECT*>& GetlistCollision() { return m_lstCollision; }
	void Release();

public:
	list<RECT*>	m_lstCollision;
};
