#include "framework.h"
#include "MovingTreeAttack.h"

CMovingTreeAttack::CMovingTreeAttack()
{
}

CMovingTreeAttack::~CMovingTreeAttack()
{
	Release();
}

HRESULT CMovingTreeAttack::Initialize(float fStartX, float fStartY)
{
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	SetInfo(56.f, 66.f);
	m_bframe = FALSE;
	SetFrame(L"MovingTree_HitR", 10.f, 5, 1);
	return NOERROR;
}

INT CMovingTreeAttack::Update(const float& fTimeDelta)
{
	UpdateRect();
	FrameMove(fTimeDelta);
	if (m_tFrame.fX == 0)
		m_bframe = TRUE;
	if (m_bframe)
		return OBJ_DEAD;
	if (b_ChangeDeadCloseAtt)
		return OBJ_DEAD;
	return 0;
}

VOID CMovingTreeAttack::Render(HDC hDC)
{
	UpdateRect();
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	HDC hMemDC = m_pBmpMgr->FindBmp(m_tFrame.strFrameKey);
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CMovingTreeAttack* CMovingTreeAttack::Create(float fStartX, float fStartY)
{
	CMovingTreeAttack* pInstance = new CMovingTreeAttack;
	if (FAILED(pInstance->Initialize(fStartX, fStartY)))
		SafeDelete(pInstance);
	return pInstance;
}

void CMovingTreeAttack::Release()
{
}
