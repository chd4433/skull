#include "framework.h"
#include "PlayerHPBar.h"
#include "Player.h"

CPlayerHPBar::CPlayerHPBar()
{
}

CPlayerHPBar::~CPlayerHPBar()
{
	Release();
}

HRESULT CPlayerHPBar::Initialize(int playerHP)
{
	CObj::Initialize();
	m_tInfo.fX = 100;
	m_tInfo.fY = 573;
	m_tInfo.fCX = 1.f;
	m_tInfo.fCY = 9.f;

	m_iPlayerHP = playerHP;
	SetFrame(L"P_HealthBar", 10.f, 1, 0);

	return NOERROR;
}

INT CPlayerHPBar::Update(const float& fTimeDelta)
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();//CPlayer::Create()->GetRectPlayer();

	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();

	m_tInfo.fX = 100 - iScrollX;
	FrameMove(fTimeDelta);

	// 0.1초 마다 삭제
	if (!m_bGetTick)
	{
		HpBar_Timer = GetTickCount();
		m_bGetTick = !m_bGetTick;
	}
	if (HpBar_Timer + 100 < GetTickCount())
	{
		m_bGetTick = !m_bGetTick;
		return OBJ_DEAD;
	}

	m_pRenderMgr->AddBack(this);
	return 0;
}

VOID CPlayerHPBar::Render(HDC hDC)
{
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	UpdateRect();
	HDC hMemDC = m_pBmpMgr->FindBmp(L"P_HealthBar");
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top,//이거 스크롤 값에 맞게 고쳐야함
		m_tInfo.fCX * (int)(149 * ((float)m_iPlayerHP / 500.f)), m_tInfo.fCY * 2,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표.
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CPlayerHPBar* CPlayerHPBar::Create(int playerHP)
{
	CPlayerHPBar* pInstance = new CPlayerHPBar;
	if (FAILED(pInstance->Initialize(playerHP)))
		SafeDelete(pInstance);
	return pInstance;
}

void CPlayerHPBar::Release()
{
}
