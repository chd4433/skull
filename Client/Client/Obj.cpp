#include "framework.h"
#include "Obj.h"

CObj::CObj()
{
}

CObj::~CObj()
{
}

HRESULT CObj::Initialize()
{
	m_pObjMgr = CObjMgr::GetInstance();
	m_pKeyMgr = CKeyMgr::GetInstance();
	m_pBmpMgr = CBitmapMgr::GetInstance();
	m_pRenderMgr = CRenderMgr::GetInstance();
	m_pCollisionMgr = CCollisionMgr::GetInstance();
	m_pSCenceMgr = CSceneMgr::GetInstance();

	return NOERROR;
}

INT CObj::Update(const float& fTimeDelta)
{
	return 0;
}

VOID CObj::Render(HDC hDC)
{
}

void CObj::Release()
{
}

void CObj::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fX - m_tInfo.fCX * 0.5f);
	m_tRect.top = LONG(m_tInfo.fY - m_tInfo.fCY * 0.5f);
	m_tRect.right = LONG(m_tInfo.fX + m_tInfo.fCX * 0.5f);
	m_tRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY * 0.5f);
}

void CObj::SetFrame(wstring strKey, float fSpeed, float fCntX, float fCntY, float fX, float fY)
{
	m_tFrame.strFrameKey = strKey;
	m_tFrame.fSpeed = fSpeed;
	m_tFrame.fCntX = fCntX;
	m_tFrame.fCntY = fCntY;
	m_tFrame.fX = fX;
	m_tFrame.fY = fY;
}

void CObj::FrameMove(const float& fTimeDelta)
{
	m_tFrame.fX += fTimeDelta * m_tFrame.fSpeed;		// ÂÒÁÂÁÂÀÛ float¸¦ int·Î Àß¶ó
	if (int(m_tFrame.fX) >= int(m_tFrame.fCntX))
	{
		m_tFrame.fX = 0.f;
		if (int(m_tFrame.fX) >= int(m_tFrame.fCntX))
			m_tFrame.fX = 0.f;
	}
}

void CObj::SetInfo(float fCntX, float fCntY)
{
	m_tInfo.fCX = fCntX;
	m_tInfo.fCY = fCntY;
}

VOID CObj::Update_Collision()
{
	switch (CurrScenes)
	{
	case SCENE_LOGO:
		break;
	case SCENE_TUTORIAL:
		m_pCollisionMgr->LoadCollisionFromPath(L"../Binary/Map1Collision.txt");
		break;
	case SCENE_STAGE1:
		m_pCollisionMgr->LoadCollisionFromPath(L"../Binary/Map2Collision.txt");
		break;
	case SCENE_STAGE2:
		m_pCollisionMgr->LoadCollisionFromPath(L"../Binary/Map3Collision.txt");
		break;
	case SCENE_GAMEOVER:
		break;
	case SCENE_END:
		break;
	default:
		break;
	}

}