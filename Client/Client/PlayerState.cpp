#include "framework.h"
#include "PlayerState.h"
#include "Player.h"

CPlayerState::CPlayerState()
{
}

CPlayerState::~CPlayerState()
{
	Release();
}

HRESULT CPlayerState::Initialize(int playerType)
{
	CObj::Initialize();
	m_tInfo.fX = 125;
	m_tInfo.fY = 550;
	m_tInfo.fCX = 250.f;
	m_tInfo.fCY = 100.f;
	m_iplayerType = playerType;
	switch (m_iplayerType) {
	case 0:		// swordman only
		SetFrame(L"Sonly_State", 10.f, 1, 0);
		break;
	case 1:		// Swordman
		SetFrame(L"S_State", 10.f, 1, 0);
		break;
	case 2:		// Alchemist
		SetFrame(L"A_State", 10.f, 1, 0);
	}

	return NOERROR;
}

INT CPlayerState::Update(const float& fTimeDelta)
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();//CPlayer::Create()->GetRectPlayer();

	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();

	m_tInfo.fX = 125 - iScrollX;
	FrameMove(fTimeDelta);
	// 0.1초 마다 삭제
	if (!m_bGetTick)
	{
		PlayerState_Timer = GetTickCount();
		m_bGetTick = !m_bGetTick;
	}
	if (PlayerState_Timer + 100 < GetTickCount())
	{
		m_bGetTick = !m_bGetTick;
		return OBJ_DEAD;
	}

	m_pRenderMgr->AddBack(this);
	return 0;
}

VOID CPlayerState::Render(HDC hDC)
{
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	UpdateRect();
	HDC hMemDC = m_pBmpMgr->FindBmp(L"Sonly_State");;
	switch (m_iplayerType) {
	case 0:		// swordman only
		hMemDC = m_pBmpMgr->FindBmp(L"Sonly_State");
		break;
	case 1:		// Swordman
		hMemDC = m_pBmpMgr->FindBmp(L"S_State");
		break;
	case 2:		// Alchemist
		hMemDC = m_pBmpMgr->FindBmp(L"A_State");
	}
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top,//이거 스크롤 값에 맞게 고쳐야함
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CPlayerState* CPlayerState::Create(int playerType)
{
	CPlayerState* pInstance = new CPlayerState;
	if (FAILED(pInstance->Initialize(playerType)))
		SafeDelete(pInstance);
	return pInstance;
}

void CPlayerState::Release()
{
}
