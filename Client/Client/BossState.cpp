#include "framework.h"
#include "BossState.h"
#include "Player.h"

CBossState::CBossState()
{
}

CBossState::~CBossState()
{
	Release();
}

HRESULT CBossState::Initialize()
{
	CObj::Initialize();
	m_tInfo.fX = 400;
	m_tInfo.fY = 50;
	m_tInfo.fCX = 550.f;
	m_tInfo.fCY = 80.f;

	SetFrame(L"Boss_State", 10.f, 1, 0);

	return NOERROR;
}

INT CBossState::Update(const float& fTimeDelta)
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();//CPlayer::Create()->GetRectPlayer();

	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();

	m_tInfo.fX = 400 - iScrollX;
	FrameMove(fTimeDelta);
	// 0.1초 마다 삭제
	if (!m_bGetTick)
	{
		BossState_Timer = GetTickCount();
		m_bGetTick = !m_bGetTick;
	}
	if (BossState_Timer + 100 < GetTickCount())
	{
		m_bGetTick = !m_bGetTick;
		return OBJ_DEAD;
	}

	m_pRenderMgr->AddBack(this);
	return 0;
}

VOID CBossState::Render(HDC hDC)
{
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	UpdateRect();
	HDC hMemDC = m_pBmpMgr->FindBmp(L"Boss_State");
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top,//이거 스크롤 값에 맞게 고쳐야함
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CBossState* CBossState::Create()
{
	CBossState* pInstance = new CBossState;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}

void CBossState::Release()
{
}
