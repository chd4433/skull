#include "framework.h"
#include "GroundTreeAttack.h"
#include "Player.h"

CGroundTreeAttack::CGroundTreeAttack()
{
}

CGroundTreeAttack::~CGroundTreeAttack()
{
	Release();
}

HRESULT CGroundTreeAttack::Initialize()
{
	CObj::Initialize();
	m_tInfo.fCX = 124.f;
	m_tInfo.fCY = 58.f;
	SetFrame(L"GroundTree_Attack_Motion", 5.f, 8, 1);
	m_bframe = FALSE;
	TargetPlayer();
	iCollisonFrame = 0;
	return NOERROR;
}

INT CGroundTreeAttack::Update(const float& fTimeDelta)
{
	FrameMove(fTimeDelta);
	if (m_tFrame.fX == 0)
		m_bframe = TRUE;
	if (m_bframe)
		return OBJ_DEAD;
	//if (b_ChangeSceneDead)
	//{
	//	return OBJ_DEAD;
	//}
	if (true) // 이걸 그릴지 말지 결정하는 조건
		m_pRenderMgr->AddFront(this);
	
	return 0;
}

VOID CGroundTreeAttack::Render(HDC hDC)
{
	UpdateRect();
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	HDC hMemDC = m_pBmpMgr->FindBmp(m_tFrame.strFrameKey);
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY+iCollisonFrame,
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CGroundTreeAttack* CGroundTreeAttack::Create()
{
	CGroundTreeAttack* pInstance = new CGroundTreeAttack;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}

VOID CGroundTreeAttack::TargetPlayer()
{
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();
	m_tInfo.fX = PlayerRect.right - (PlayerRect.right - PlayerRect.left)/2;
	m_tInfo.fY = PlayerRect.bottom - (PlayerRect.bottom - PlayerRect.top) / 2;
}


void CGroundTreeAttack::Release()
{
}
