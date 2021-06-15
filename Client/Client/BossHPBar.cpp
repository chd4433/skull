#include "framework.h"
#include "BossHPBar.h"
#include "Player.h"

CBossHPBar::CBossHPBar()
{
}

CBossHPBar::~CBossHPBar()
{
	Release();
}

HRESULT CBossHPBar::Initialize(int bossHP)
{
	CObj::Initialize();
	m_tInfo.fX = 130;
	m_tInfo.fY = 60;
	m_tInfo.fCX = 1.f;
	m_tInfo.fCY = 9.f;

	m_ibossHP = bossHP;
	SetFrame(L"B_HealthBar", 10.f, 1, 0);

	return NOERROR;
}

INT CBossHPBar::Update(const float& fTimeDelta)
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();//CPlayer::Create()->GetRectPlayer();

	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();

	m_tInfo.fX = 130 - iScrollX;
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

VOID CBossHPBar::Render(HDC hDC)
{
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	UpdateRect();
	HDC hMemDC = m_pBmpMgr->FindBmp(L"B_HealthBar");
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top,//이거 스크롤 값에 맞게 고쳐야함
		m_tInfo.fCX * (int)(540 * ((float)m_ibossHP / 3000.f)), m_tInfo.fCY * 2,// 보스체력 바뀌면 3000.f 수정하면됨
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표.
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CBossHPBar* CBossHPBar::Create(int bossHP)
{
	CBossHPBar* pInstance = new CBossHPBar;
	if (FAILED(pInstance->Initialize(bossHP)))
		SafeDelete(pInstance);
	return pInstance;
}

void CBossHPBar::Release()
{
}
