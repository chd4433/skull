#include "framework.h"
#include "ShotedPlayer.h"

CShotedPlayer::CShotedPlayer()
{
}

CShotedPlayer::~CShotedPlayer()
{
	Release();
}

HRESULT CShotedPlayer::Initialize(float fStartX, float fStartY)
{
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	SetFrame(L"ShotedPlayer", 15.f, 5, 1);
	return NOERROR;
}

INT CShotedPlayer::Update(const float& fTimeDelta)
{
	TargetPlayer();
	FrameMove(fTimeDelta);
	if (m_tFrame.fX == 0)
		return OBJ_DEAD;
	if (true) // 이걸 그릴지 말지 결정하는 조건
		m_pRenderMgr->AddFront(this);

	return 0;
}

VOID CShotedPlayer::Render(HDC hDC)
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
VOID CShotedPlayer::TargetPlayer()
{
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();
	m_tInfo.fX = PlayerRect.right - (PlayerRect.right - PlayerRect.left) / 2;
	m_tInfo.fY = PlayerRect.bottom - (PlayerRect.bottom - PlayerRect.top) / 2;
}

CShotedPlayer* CShotedPlayer::Create(float fStartX, float fStartY)
{
	CShotedPlayer* pInstance = new CShotedPlayer;
	if (FAILED(pInstance->Initialize(fStartX,fStartY)))
		SafeDelete(pInstance);
	return pInstance;
}

void CShotedPlayer::Release()
{
}
