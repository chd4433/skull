#include "framework.h"
#include "CollisionMgr.h"
#include "Obj.h"
IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::~CCollisionMgr()
{
	Release();
}

bool CCollisionMgr::Check_IntersectRect(CObj* pDst, CObj* pSrc)
{
	RECT rc = {};
	// IntersectRect: 사각형 충돌을 판별하는 함수. 두 사각형이 충돌 됬을 때 TRUE 반환.
	// IntersectRect(겹친 영역을 기록할 사각형, 충돌 사각형1, 충돌 사각형2);

	const RECT& dstRect = pDst->GetRect();
	const RECT& srcRect = pSrc->GetRect();

	if (IntersectRect(&rc, &dstRect, &srcRect))
		return true;


	return false;
}

bool CCollisionMgr::Check_ObjRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY)
{
	// 두 사각형의 가로, 세로 축 반지름의 합을 구한다.
	float fSumRadX = (pDst->GetInfo().fCX + pSrc->GetInfo().fCX) * 0.5f;
	float fSumRadY = (pDst->GetInfo().fCY + pSrc->GetInfo().fCY) * 0.5f;

	// 두 사각형의 가로, 세로 중점의 거리를 구한다.
	// fabs(X): X의 절대 값을 구하는 함수. <cmath>에서 제공. 
	float fDistX = fabs(pDst->GetInfo().fX - pSrc->GetInfo().fX);
	float fDistY = fabs(pDst->GetInfo().fY - pSrc->GetInfo().fY);

	// 가로 축 반지름 합이 가로 축 거리보다 클 때와
	// 세로 축 반지름 합이 세로 축 거리보다 클 때
	if (fSumRadX > fDistX && fSumRadY > fDistY)
	{
		// 두 사각형이 겹쳤을 때 파고든 길이도 구한다.
		*pMoveX = fSumRadX - fDistX;
		*pMoveY = fSumRadY - fDistY;

		return true;
	}

	return false;
}

bool CCollisionMgr::Check_Rect(RECT tDst, RECT tSrc, float* pMoveX, float* pMoveY)
{
	INFO tDstInfo = {};
	INFO tSrcInfo = {};

	tDstInfo.fCX = float(tDst.right - tDst.left);
	tDstInfo.fCY = float(tDst.bottom - tDst.top);
	tDstInfo.fX = (float)tDst.left + (tDstInfo.fCX * 0.5f);
	tDstInfo.fY = (float)tDst.top + (tDstInfo.fCY * 0.5f);

	tSrcInfo.fCX = float(tSrc.right - tSrc.left);
	tSrcInfo.fCY = float(tSrc.bottom - tSrc.top);
	tSrcInfo.fX = (float)tSrc.left + (tSrcInfo.fCX * 0.5f);
	tSrcInfo.fY = (float)tSrc.top + (tSrcInfo.fCX * 0.5f);

	// 두 사각형의 가로, 세로 축 반지름의 합을 구한다.
	float fSumRadX = (tDstInfo.fCX + tSrcInfo.fCX) * 0.5f;
	float fSumRadY = (tDstInfo.fCX + tSrcInfo.fCX) * 0.5f;

	// 두 사각형의 가로, 세로 중점의 거리를 구한다.
	// fabs(X): X의 절대 값을 구하는 함수. <cmath>에서 제공. 
	float fDistX = fabs(tDstInfo.fX - tSrcInfo.fX);
	float fDistY = fabs(tDstInfo.fY - tSrcInfo.fY);

	// 가로 축 반지름 합이 가로 축 거리보다 클 때와
	// 세로 축 반지름 합이 세로 축 거리보다 클 때
	if (fSumRadX > fDistX && fSumRadY > fDistY)
	{
		// 두 사각형이 겹쳤을 때 파고든 길이도 구한다.
		*pMoveX = fSumRadX - fDistX;
		*pMoveY = fSumRadY - fDistY;

		return true;
	}

	return false;
}

bool CCollisionMgr::Check_Sphere(CObj* pDst, CObj* pSrc)
{
	// 원충돌

	// 두 원의 반지름 합을 구한다.
	float fSumRad = (pDst->GetInfo().fCX + pSrc->GetInfo().fCX) * 0.5f;
	 
	// 두 원의 거리를 구한다. 피타고라스를 이용.
	float w = pDst->GetInfo().fX - pSrc->GetInfo().fX;
	float h = pDst->GetInfo().fY - pSrc->GetInfo().fY; 

	// sqrtf(X): X에 대한 제곱근을 구해주는 함수.
	float fDist = sqrtf(w * w + h * h);

	return (fSumRad >= fDist);
}


HRESULT CCollisionMgr::LoadCollisionFromPath(wstring strPath)
{
	//std::locale::global(std::locale("Korean"));
#ifdef _UNICODE
	wifstream fin;
#else
	wifstream fin;
#endif // _UNICODE

	fin.open(strPath);

	if (fin.fail())
		return E_FAIL;;
	RECT rectCollision = {};

	while (true)
	{
		RECT* pRect = new RECT;
		if (fin.eof())
			break;

		fin >> pRect->left >> pRect->top >> pRect->right >> pRect ->bottom;
		//pRect = &rectCollision;
		if (FAILED(AddCollision(pRect)))
			return E_FAIL;
	}

	fin.close();

	return NOERROR;
}

HRESULT CCollisionMgr::AddCollision(RECT* pRect)
{
	if (pRect == nullptr)
		return E_FAIL;

	m_lstCollision.emplace_back(pRect);

	return NOERROR;
}

bool CCollisionMgr::CollisionDstToSrc(list<CObj*> Dst, list<CObj*> Src)
{
	RECT temp = {};
	if (!Dst.empty())
	{
		for (auto& pPlayerAtt : Dst)
		{
			for (auto& pMonster : Src)
			{
				if (IntersectRect(&temp, &(pPlayerAtt->GetSmallRect()), &(pMonster->GetSmallRect())))
				{
					pMonster->SetbChangeScene();
					pPlayerAtt->SetbChangeScene();
					//SafeDelete(pPlayerAtt);
					return TRUE;
				}

			}
		}
	}
	return TRUE;
}

bool CCollisionMgr::CollisionDstToSrcClose(list<CObj*> Dst, list<CObj*> Src)
{
	RECT temp = {};
	if (!Dst.empty())
	{
		for (auto& pPlayerAtt : Dst)
		{
			for (auto& pMonster : Src)
			{
				if (IntersectRect(&temp, &(pPlayerAtt->GetSmallRect()), &(pMonster->GetSmallRect())))
				{
					pMonster->SetbChangeSceneClose();
					pPlayerAtt->SetbChangeSceneClose();
					//SafeDelete(pPlayerAtt);
					return TRUE;
				}

			}
		}
	}
	return TRUE;
}


void CCollisionMgr::Release()
{
	for (RECT* pColl : m_lstCollision)
		delete pColl;
		//SafeDelete(pColl);
	m_lstCollision.clear();
}