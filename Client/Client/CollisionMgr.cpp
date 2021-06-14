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
	// IntersectRect: �簢�� �浹�� �Ǻ��ϴ� �Լ�. �� �簢���� �浹 ���� �� TRUE ��ȯ.
	// IntersectRect(��ģ ������ ����� �簢��, �浹 �簢��1, �浹 �簢��2);

	const RECT& dstRect = pDst->GetRect();
	const RECT& srcRect = pSrc->GetRect();

	if (IntersectRect(&rc, &dstRect, &srcRect))
		return true;


	return false;
}

bool CCollisionMgr::Check_ObjRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY)
{
	// �� �簢���� ����, ���� �� �������� ���� ���Ѵ�.
	float fSumRadX = (pDst->GetInfo().fCX + pSrc->GetInfo().fCX) * 0.5f;
	float fSumRadY = (pDst->GetInfo().fCY + pSrc->GetInfo().fCY) * 0.5f;

	// �� �簢���� ����, ���� ������ �Ÿ��� ���Ѵ�.
	// fabs(X): X�� ���� ���� ���ϴ� �Լ�. <cmath>���� ����. 
	float fDistX = fabs(pDst->GetInfo().fX - pSrc->GetInfo().fX);
	float fDistY = fabs(pDst->GetInfo().fY - pSrc->GetInfo().fY);

	// ���� �� ������ ���� ���� �� �Ÿ����� Ŭ ����
	// ���� �� ������ ���� ���� �� �Ÿ����� Ŭ ��
	if (fSumRadX > fDistX && fSumRadY > fDistY)
	{
		// �� �簢���� ������ �� �İ�� ���̵� ���Ѵ�.
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

	// �� �簢���� ����, ���� �� �������� ���� ���Ѵ�.
	float fSumRadX = (tDstInfo.fCX + tSrcInfo.fCX) * 0.5f;
	float fSumRadY = (tDstInfo.fCX + tSrcInfo.fCX) * 0.5f;

	// �� �簢���� ����, ���� ������ �Ÿ��� ���Ѵ�.
	// fabs(X): X�� ���� ���� ���ϴ� �Լ�. <cmath>���� ����. 
	float fDistX = fabs(tDstInfo.fX - tSrcInfo.fX);
	float fDistY = fabs(tDstInfo.fY - tSrcInfo.fY);

	// ���� �� ������ ���� ���� �� �Ÿ����� Ŭ ����
	// ���� �� ������ ���� ���� �� �Ÿ����� Ŭ ��
	if (fSumRadX > fDistX && fSumRadY > fDistY)
	{
		// �� �簢���� ������ �� �İ�� ���̵� ���Ѵ�.
		*pMoveX = fSumRadX - fDistX;
		*pMoveY = fSumRadY - fDistY;

		return true;
	}

	return false;
}

bool CCollisionMgr::Check_Sphere(CObj* pDst, CObj* pSrc)
{
	// ���浹

	// �� ���� ������ ���� ���Ѵ�.
	float fSumRad = (pDst->GetInfo().fCX + pSrc->GetInfo().fCX) * 0.5f;
	 
	// �� ���� �Ÿ��� ���Ѵ�. ��Ÿ��󽺸� �̿�.
	float w = pDst->GetInfo().fX - pSrc->GetInfo().fX;
	float h = pDst->GetInfo().fY - pSrc->GetInfo().fY; 

	// sqrtf(X): X�� ���� �������� �����ִ� �Լ�.
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